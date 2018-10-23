#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	int time;
	int power;
	int state;
}Node;

Node map[2][700][700];
int N, M, K;
int result;
int dx[4] = { -1,0,1,0 };
int dy[4] = { 0,1,0,-1 };

void init() {
	N = 0, M = 0, K = 0;
	result = 0;
	for (int k = 0; k < 2; k++)
	{
		for (int i = 0; i < 700; i++)
		{
			for (int j = 0; j < 700; j++)
			{
				map[k][i][j] = { 0,0,0 };
			}
		}
	}
	
}
void cntResult(int curMap) {

	for (int i = 0; i < 700; i++)
	{
		for (int j = 0; j < 700; j++)
		{
			if (map[curMap][i][j].state == 1 || map[curMap][i][j].state == 2) {
				result++;
			}
		}
	}
}
void solve() {

	int curMap = 0;
	for (int k = 0; k <= K; k++)
	{
		for (int i = 0; i < 700; i++)
		{
			for (int j = 0; j < 700; j++)
			{
				if (map[curMap][i][j].state != 0) {
					//ºñÈ°¼º»óÅÂ
					if (map[curMap][i][j].state == 1) {
						if (map[curMap][i][j].time < map[curMap][i][j].power) {
							map[1 - curMap][i][j].time++;
							map[1 - curMap][i][j].power = map[curMap][i][j].power;
							map[1 - curMap][i][j].state = map[curMap][i][j].state;
						}
						else if (map[curMap][i][j].time == map[curMap][i][j].power) {
							map[1 - curMap][i][j].time = map[curMap][i][j].time;
							map[1 - curMap][i][j].power = map[curMap][i][j].power;
							map[1 - curMap][i][j].state = 2;
						}
					}
					//È°¼º
					else if (map[curMap][i][j].state == 2) {
						if (map[curMap][i][j].time == 0) {
							map[1- curMap][i][j].state = 3;
						}
						else {
							int p = map[curMap][i][j].power;
							for (int d = 0; d < 4; d++)
							{
								int nx = i + dx[d];
								int ny = j + dy[d];
								//ºó°ø°£
								if (map[1-curMap][nx][ny].state == 0) {
									map[1-curMap][nx][ny] = { 0,p,1 };
								}
								//ºó°ø°£ÀÌ ¾Æ´Ô
								else if (map[1-curMap][nx][ny].state == 1) {
									if (map[1-curMap][nx][ny].power < map[curMap][i][j].power) {
										map[1- curMap][nx][ny] = { 0,p,1 };
									}
								}
							}
							map[1 - curMap][i][j].time--;
							map[1 - curMap][i][j].power = map[curMap][i][j].power;
							map[1 - curMap][i][j].state = map[curMap][i][j].state;
						}
					}
					//Á×Àº »óÅÂ
					else if (map[curMap][i][j].state == 3) {
						map[1 - curMap][i][j].state = 3;
					}
				}
			}
		}
		curMap = 1 - curMap;
	}

	cntResult(curMap);
}

int main() {
	int TC;
	freopen("input.txt", "r", stdin);
	scanf("%d", &TC);
	for (int t = 1; t <= TC; t++)
	{
		init();
		scanf("%d %d %d", &N, &M, &K);
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < M; j++)
			{
				int power;
				scanf("%d", &power);
				if (power != 0) {
					map[0][i + 300][j + 300] = { 0,power,1 };
					map[1][i + 300][j + 300] = { 0,power,1 };
				}
			}
		}
		solve();
		printf("#%d %d\n", t, result);
	}
	return 0;
}