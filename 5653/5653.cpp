#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

int map[350][350];
int N, M, K;
int dx[4] = {-1,0,1,0};
int dy[4] = {0,1,0,-1};

typedef struct Node{
	int status;
	int cellPower;
	int hp;
}Node;

Node MAP[2][350][350];

void init() {

}

void solve() {

	for (int k = 0; k < K; k++)
	{
		for (int i = 0; i < N+K; i++)
		{
			for (int j = 0; j < M+K; j++)
			{
				if (MAP[0][i][j].status == 1) {
					MAP[0][i][j].hp++;
				}
				else if (MAP[0][i][j].hp == MAP[0][i][j].cellPower) {
					MAP[0][i][j].status = 2; // 분화 시작
					MAP[0][i][j].hp--;
					for (int d = 0; d < 4; d++)
					{
						int nx = i + dx[d];
						int ny = j + dy[d];
						if (nx < 0 || ny < 0 || nx >= 350 || ny >= 350) {
							continue;
						}
						//빈 공간
						if (MAP[0][nx][ny].status == 0) {
							if (MAP[1][nx][ny].cellPower == 0) {
								MAP[1][nx][ny].status = 1;//비활성상태
								MAP[1][nx][ny].cellPower = MAP[0][i][j].cellPower;
								MAP[1][nx][ny].hp = 0;
							}
							else {
								if (MAP[1][nx][ny].cellPower >= MAP[0][i][j].cellPower) {
									continue;
								}
								else {
									MAP[1][nx][ny].cellPower = MAP[0][i][j].cellPower;
								}
							}

						}
					}

				}
				else if (MAP[0][i][j].status == 2 && MAP[0][i][j].hp == 0) {
					MAP[0][i][j].status = 3;// 죽은 상태 
				}
			}
		}

		for (int i = 0; i < N + K; i++)
		{
			for (int j = 0; j < M + K; j++)
			{
				MAP[1][i][j] = MAP[0][i][j];
			}
		}


	}

}
int main() {
	int TC;
	freopen("input.txt", "r", stdin);
	for (int t = 0; t < TC; t++)
	{
		scanf("%d %d %d", &N, &M, &K);

		for (int i = 0; i < N + K; i++)
		{
			for (int j = 0; j < M + K; j++)
			{
				MAP[0][i][j].cellPower = 0;
				MAP[0][i][j].hp = 0;
				MAP[0][i][j].status = 0;
			}
		}

		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < M; j++)
			{
				int temp = 0;
				scanf("%d", &temp);
				MAP[0][i + N / 2][j + M / 2].cellPower = temp;
				MAP[1][i + N / 2][j + M / 2].cellPower = temp;
				if (temp > 0) {
					MAP[0][i + N / 2][j + M / 2].status = 1;
					MAP[1][i + N / 2][j + M / 2].status = 1;
				}
			}
		}

		solve();
	}
	return 0;
}