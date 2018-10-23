#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#define MAX 2001

typedef struct node {
	int dir;
	int energy;
	int atomCnt;
}node;

int N;
node map[2][MAX][MAX];

int energeSum;
//상, 하, 좌, 우
int dx[4] = {-1, 1, 0, 0};
int dy[4] = { 0,0,-1,1 };

void init() {
	N = 0; energeSum = 0;
	for (int k = 0; k < 2; k++)
	{
		for (int i = 0; i < MAX; i++)
		{
			for (int j = 0; j < MAX; j++)
			{
				map[k][i][j] = { 0,0,0 };
			}
		}
	}
}

bool allOutOfMap() {
	for (int i = 0; i < MAX; i++)
	{
		for (int j = 0; j < MAX; j++)
		{
			if (map[0][i][j].atomCnt != 0) {
				return false;
			}
		}
	}
	return true;
}

int checkUpsideDir(int dir) {
	switch (dir)
	{
	case 0:
		return 1;
	case 1:
		return 0;
	case 2:
		return 3;
	case 3:
		return 2;
	default:
		return -1;
	}
}
void solve() {
	while (allOutOfMap() == false) {
		for (int i = 0; i < MAX; i++)
		{
			for (int j = 0; j < MAX; j++)
			{
				if (map[0][i][j].atomCnt != 0) {
					int dir = map[0][i][j].dir;
					int nx = i + dx[dir];
					int ny = j + dy[dir];

					if (nx < 0 || ny < 0 || nx >= MAX || ny >= MAX) {
						map[0][i][j] = { 0,0,0 };
						continue;
					}
					//다음 이동 위치가 빈 공간일 때
					else if (map[1][nx][ny].atomCnt == 0) {
						map[1][nx][ny].atomCnt = 1;
						map[1][nx][ny].dir = map[0][i][j].dir;
						map[1][nx][ny].energy = map[0][i][j].energy;
					}
					//다음 이동 위치에 다른 원소가 있을 때 다음 위치에 모아놓기 => 충돌
					else if (map[1][nx][ny].atomCnt != 0) {
						map[1][nx][ny].atomCnt++;
						map[1][nx][ny].dir = 99;
						map[1][nx][ny].energy += map[0][i][j].energy;
					}
					//가는 경로 바로 앞에 원소가 있을 때 => 충돌
					else if (map[0][nx][ny].atomCnt != 0 && map[0][nx][ny].dir == checkUpsideDir(dir)) {
						map[1][nx][ny].atomCnt = map[0][i][j].atomCnt + map[0][nx][ny].atomCnt;
						map[1][nx][ny].dir = 99;
						map[1][nx][ny].energy = map[0][i][j].energy + map[0][nx][ny].energy;
						map[0][nx][ny] = { 0,0,0 };
					}
				}
			}
		}

		//충돌난 에너지 더해주기
		for (int i = 0; i < MAX; i++)
		{
			for (int j = 0; j < MAX; j++)
			{
				//충돌이 일어난 경우
				if (map[1][i][j].atomCnt >= 2) {
					energeSum += map[1][i][j].energy;
					map[1][i][j] = { 0,0,0 };
				}
			}
		}

		//맵 이동하기
		for (int i = 0; i < MAX; i++)
		{
			for (int j = 0; j < MAX; j++)
			{
				map[0][i][j] = { 0,0,0 };
				map[0][i][j] = map[1][i][j];
				map[1][i][j] = { 0,0,0 };
			}
		}
	}
}
int abs(int x) {
	return x >= 0 ? x : x * (-1);
}
void mappingMap(int x, int y, int dir, int energy) {
	int arrx, arry;
	if (x >= 0) {
		arry = 1000 + x;
	}
	else {
		arry = 1000 + x;
	}

	if (y >= 0) {
		arrx = 1000 - y;
	}
	else {
		arrx = 1000 + abs(y);
	}
	map[0][arrx][arry].atomCnt = 1;
	map[0][arrx][arry].dir = dir;
	map[0][arrx][arry].energy = energy;
}

int main() {
	int TC;
	freopen("input.txt", "r", stdin);
	scanf("%d", &TC);
	for (int tc = 1; tc <= TC; tc++)
	{
		init();
		scanf("%d", &N);
		for (int i = 0; i < N; i++)
		{
			int x, y, dir, energy;
			scanf("%d %d %d %d", &x, &y, &dir, &energy);
			mappingMap(x, y, dir, energy);
		}

		solve();

		printf("#%d %d\n", tc, energeSum);
	}
	return 0;
}