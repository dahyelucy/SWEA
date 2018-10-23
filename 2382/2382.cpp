#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#define MAX 101

typedef struct node {
	int exist; //0 : 빈공간 1 : 약품 2 : 미생물
	int dir; // 0 상 1 우 2 하 3 좌 , 5 약품이나 빈공간의 방향
	int cnt; // 1 이상인 경우 미생물
	int maxcnt;
}node;

node map[2][MAX][MAX];
int N, M, K;
int dx[5] = {0, -1, 1, 0, 0};
int dy[5] = {0, 0, 0, -1, 1 };

void init() {
	N = 0, M = 0, K = 0;
	for (int k = 0; k < 2; k++)
	{
		for (int i = 0; i < MAX; i++)
		{
			for (int j = 0; j < MAX; j++)
			{
				map[k][i][j].exist = 0;
				map[k][i][j].dir = 0;
				map[k][i][j].cnt = 0;
				map[k][i][j].maxcnt = 0;
			}
		}
	}
}

int changeDir(int d) {
	int ans;
	switch (d)
	{
	case 1:
		ans = 2;
		break;
	case 2:
		ans = 1;
		break;
	case 3:
		ans = 4;
		break;
	case 4:
		ans = 3;
		break;
	default:
		break;
	}

	return ans;
}

void moveArray() {
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			map[0][i][j] = { 0, 0, 0, 0 };
			map[0][i][j] = map[1][i][j];
			map[1][i][j] = { 0, 0, 0, 0 };
		}
	}
}


void printArray() {
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			printf("(exist : %d, dir : %d, cnt : %d) ", map[0][i][j].exist, map[0][i][j].dir, map[0][i][j].cnt);
		}
		printf("\n");
	}
	printf("\n\n");
}


void solve() {
	for (int k = 1; k <= M; k++)
	{
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				//현재 미생물 군집인 경우
				if (map[0][i][j].exist == 2) {
					int d = map[0][i][j].dir;
					int nx = i + dx[d];
					int ny = j + dy[d];
					//약품인 경우
					if (nx == 0 || ny == 0 || nx == N - 1 || ny == N - 1) {
						map[1][nx][ny].exist = 2;
						map[1][nx][ny].dir = changeDir(map[0][i][j].dir);
						map[1][nx][ny].cnt = map[0][i][j].cnt / 2;
					}
					//빈 공간인 경우 -> move
					else if (map[1][nx][ny].exist == 0) {
						map[1][nx][ny].exist = 2;
						map[1][nx][ny].dir = map[0][i][j].dir;
						map[1][nx][ny].cnt = map[0][i][j].cnt;
						map[1][nx][ny].maxcnt = map[0][i][j].cnt;
					}
					//다른 미생물 군집인 경우
					else if (map[1][nx][ny].exist == 2) {
						map[1][nx][ny].cnt += map[0][i][j].cnt;

						if (map[0][i][j].cnt > map[1][nx][ny].maxcnt) {
							map[1][nx][ny].dir = map[0][i][j].dir;
							map[1][nx][ny].maxcnt = map[0][i][j].cnt;
						}
					}
				}
			}
		}
		moveArray();
		//printArray();
	}
}

int calcMicroorganism() {
	int ans = 0;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (map[0][i][j].exist == 2) {
				ans += map[0][i][j].cnt;
			}
		}
	}
	return ans;
}
int main() {
	int TC;
	freopen("input.txt", "r", stdin);
	scanf("%d", &TC);

	for (int tc = 1; tc <= TC; tc++)
	{
		init();
		scanf("%d %d %d", &N, &M, &K);
		for (int k = 0; k < K; k++)
		{
			int x, y, cnt, dir;
			scanf("%d %d %d %d", &x, &y, &cnt, &dir);
			map[0][x][y].exist = 2;
			map[0][x][y].dir = dir;
			map[0][x][y].cnt = cnt;
			map[0][x][y].maxcnt = cnt;
		}
		//printArray();
		solve();
		printf("#%d %d\n", tc, calcMicroorganism());
	}
	return 0;
}