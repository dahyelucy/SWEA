#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

int N, W, H;
int map[16][13];
int copy[16][13];
int visited[16][13];
int selected[4];
int minRemain;
int dx[4] = {-1, 0, 1, 0};
int dy[4] = { 0,1,0,-1 };

void init();
void makeSelected(int depth);
void makeBomb(int x, int y);
void calcRemains();
void searchMap();
void makeArrangeMap();
void makeMaptoOrigin();

void init() {
	N = 0; W = 0; H = 0;
	minRemain = 2123456789;
	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 13; j++)
		{
			map[i][j] = 0;
			copy[i][j] = 0;
			visited[i][j] = 0;
		}
	}
	for (int i = 0; i < 4; i++)
	{
		selected[i] = 0;
	}
}

void makeSelected(int depth) {
	if (depth == N) {
		searchMap();
		makeMaptoOrigin();
		return;
	}

	for (int i = 0; i < W; i++)
	{
		selected[depth] = i;
		makeSelected(depth + 1);
	}
}

void makeBomb(int x, int y) {
	int searchDepth = map[x][y] - 1;

	if (searchDepth == 0) {
		map[x][y] = 0;
	}
	else {
		map[x][y] = 0;
		for (int k = 0; k < 4; k++)
		{
			for (int i = 1; i <= searchDepth; i++)
			{
				int nx = x + dx[k] * i;
				int ny = y + dy[k] * i;
				if (nx < 0 || ny < 0 || nx >= H || ny >= W) {
					continue;
				}
				if (map[nx][ny] != 0) {
					makeBomb(nx, ny);
				}
			}
		}
	}

}

void makeArrangeMap() {
	for (int j = 0; j < W; j++)
	{
		for (int i = 0; i < H; i++)
		{
			if (map[i][j] != 0) {
				int k = i;
				while (map[k][j] != 0) {
					k++;
				}
				if (k >= H)
					break;
				for (int temp = k - 1; temp >= i; temp--)
				{
					map[temp + 1][j] = map[temp][j];
					map[temp][j] = 0;
				}
			}
		}
	}
}

void calcRemains() {
	int cnt = 0;
	for (int i = 0; i < H; i++)
	{
		for (int j = 0; j < W; j++)
		{
			if (map[i][j] != 0) {
				cnt++;
			}
		}
	}

	if (cnt < minRemain)
		minRemain = cnt;
}

void searchMap() {
	for (int k = 0; k < N; k++)
	{
		int j = selected[k];
		for (int i = 0; i < H; i++)
		{
			if (map[i][j] != 0) {
				makeBomb(i, j);
				break;
			}
		}

		makeArrangeMap();
	}

	calcRemains();
}

void makeMaptoOrigin() {
	for (int i = 0; i < H; i++)
	{
		for (int j = 0; j < W; j++)
		{
			map[i][j] = copy[i][j];
		}
	}
}


void solve() {
	makeSelected(0);
}

int main() {
	int TC;
	freopen("input.txt", "r", stdin);
	scanf("%d", &TC);
	for (int tc = 1; tc <= TC; tc++)
	{
		init();
		scanf("%d %d %d", &N, &W, &H);
		for (int i = 0; i < H; i++)
		{
			for (int j = 0; j < W; j++)
			{
				scanf("%d", &map[i][j]);
				copy[i][j] = map[i][j];
			}
		}
		solve();

		printf("#%d %d\n", tc, minRemain);
	}

	return 0;
}