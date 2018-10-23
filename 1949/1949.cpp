#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int N; int K;
int map[9][9];
int visited[9][9];
int dx[4] = { -1,0,1,0 };
int dy[4] = { 0,1,0,-1 };
int MAX;

void init() {
	N = 0; K = 0;
	MAX = 0;
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			map[i][j] = 0;
			visited[i][j] = 0;
		}
	}
}


void dfs(int x, int y, int height, int dist, int flag, int vk) {
	visited[x][y] = 1;

	if (dist > MAX) {
		MAX = dist;
	}

	for (int d = 0; d < 4; d++)
	{
		int nx = x + dx[d];
		int ny = y + dy[d];
		if (nx < 0 || ny < 0 || nx >= N || ny >= N) {
			continue;
		}
		if (map[nx][ny] < height && visited[nx][ny] == 0) {
			dfs(nx, ny, map[nx][ny], dist + 1, flag, vk);
		}
		else if (map[nx][ny] - height < vk && flag == false && visited[nx][ny]==0) {
			dfs(nx, ny, map[nx][ny] - vk, dist + 1, true, vk);
		}
	}

	visited[x][y] = 0;
}
void findMaxXY() {
	int max = -1;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (map[i][j] > max) {
				max = map[i][j];
			}
		}
	}

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (map[i][j] == max) {
				for (int k = 1; k <= K; k++)
				{
					dfs(i, j, max, 1, false, k);
				}
			}
		}
	}
}

int main() {
	freopen("input.txt", "r", stdin);
	int tc = 0;
	scanf("%d", &tc);
	for (int k = 0; k < tc; k++)
	{
		init();
		scanf("%d %d", &N, &K);
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				scanf("%d", &map[i][j]);
			}
		}

		findMaxXY();

		printf("#%d %d\n", k + 1, MAX);
	
	}
	return 0;
}