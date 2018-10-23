#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	int cnt;
	int dir;
}Node;

int N, K, M;
Node map[2][101][101];
int result;
int dx[5] = {0,-1,1,0,0};
int dy[5] = {0, 0,0,-1,1 };

void init() {
	N = 0; K = 0; M = 0;
	result = 0;
	for (int k = 0; k < 2; k++)
	{
		for (int i = 0; i < 101; i++)
		{
			for (int j = 0; j < 101; j++)
			{
				map[k][i][j] = { 0,0 };
			}
		}
	}
}

int changeDir(int dir) {
	switch (dir)
	{
	case 1:
		return 2;
	case 2:
		return 1;
	case 3:
		return 4;
	case 4:
		return 3;
	default:
		break;
	}
	return 0;
}

int findMaxDir(int x, int y) {
	int maxCnt = -1; int maxDir;
	for (int d = 1; d <=4; d++)
	{
		int nx = x + dx[d];
		int ny = y + dy[d];
		if (nx < 0 || ny < 0 || nx >= N || ny >= N) {
			continue;
		}
		if (map[0][nx][ny].cnt != 0) {
			int nDir = map[0][nx][ny].dir;
			int nx2 = nx + dx[nDir];
			int ny2 = ny + dy[nDir];
			if (nx2 == x && ny2 == y && map[0][nx][ny].cnt > maxCnt) {
				maxCnt = map[0][nx][ny].cnt;
				maxDir = map[0][nx][ny].dir;
			}
		}
	}
	return maxDir;
}

void moveMap() {
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			map[0][i][j] = { 0,0 };
			map[0][i][j] = map[1][i][j];
			map[1][i][j] = { 0,0 };
		}
	}
}

void cntBiosNum() {
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (map[0][i][j].cnt != 0) {
				result += map[0][i][j].cnt;
			}
		}
	}
}

void solve() {
	for (int m = 1; m <= M; m++)
	{
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				if (map[0][i][j].cnt != 0) {
					int cnt = map[0][i][j].cnt;
					int dir = map[0][i][j].dir;

					int nx = i + dx[dir];
					int ny = j + dy[dir];
					
					//약품 구역
					if (nx == 0 || ny == 0 || nx == N - 1 || ny == N - 1) {
						dir = changeDir(dir);
						map[1][nx][ny] = { cnt / 2, dir };
					}
					//다른 미생물이 차지하고 있음
					else if (map[1][nx][ny].cnt != 0) {
						map[1][nx][ny].cnt += cnt;
						//새로운 위치의 사방향에 max cnt를 가진 미생물의 dir을 가져옴
						dir = findMaxDir(nx, ny);
						map[1][nx][ny].dir = dir;
					}
					//아무것도 없음
					else if (map[1][nx][ny].cnt == 0) {
						map[1][nx][ny] = { cnt, dir };
					}
				}
			}
		}
		moveMap();
	}
	cntBiosNum();
}

int main() {
	int TC;
	freopen("input.txt", "r", stdin);
	scanf("%d", &TC);
	for (int t = 1; t <= TC; t++)
	{
		init();
		scanf("%d %d %d", &N, &M, &K);
		for (int k = 0; k < K; k++)
		{
			int x, y, cnt, dir;
			scanf("%d %d %d %d", &x, &y, &cnt, &dir);
			map[0][x][y] = { cnt, dir };
		}
		solve();
		printf("#%d %d\n", t, result);
	}
	return 0;
}