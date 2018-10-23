#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

int N, M;
int homeCnt;
int cost;
int max;
int map[21][21];

void init() {
	N = 0, M = 0; homeCnt = 0; cost = 0; max = 0;
	for (int i = 0; i<N; i++) {
		for (int j = 0; j<N; j++) {
			map[i][j] = 0;
		}
	}
}




void checkRange(int x, int y) {
	int K = 0;
	for (int k = 0; k <= N; k++)
	{
		K = 2 * k + 1; //1,3,5,7....범위 확인 크기
		int costK = k + 1;
		cost = costK * costK + (costK - 1)*(costK - 1);
		homeCnt = 0;
		for (int i = (-1) * k; i <= k ; i++)
		{
			if (i<=0) {
				for (int j = (-1) * (i + k); j <= (i + k); j++)
				{
					int nx = x + i;
					int ny = y + j;
					//printf("(%d, %d)", nx, ny);
					if (nx < 0 || ny < 0 || nx >= N || ny >= N) {
						continue;
					}
					else {
						if (map[nx][ny] == 1) {
							homeCnt++;
						}
					}
					
				}
			}
			else {
				for (int j = (-1) * (k-i); j <= (k-i); j++)
				{
					int nx = x + i;
					int ny = y + j;
					//printf("(%d, %d)", nx, ny);
					if (nx < 0 || ny < 0 || nx >= N || ny >= N) {
						continue;
					}
					else {
						if (map[nx][ny] == 1) {
							homeCnt++;
						}
					}
				}
			}
			//printf("\n");
		}

		if (cost<homeCnt*M) {
			if (max<homeCnt) {
				max = homeCnt;
			}
		}
	}
}

int main() {
	int TC;
	freopen("input.txt","r",stdin);
	scanf("%d", &TC);
	for (int tc = 0; tc<TC; tc++) {
		init();
		scanf("%d %d", &N, &M);
		for (int i = 0; i<N; i++) {
			for (int j = 0; j<N; j++) {
				scanf("%d", &map[i][j]);
			}
		}
		
		for (int i = 0; i<N; i++) {
			for (int j = 0; j<N; j++) {
				checkRange(i, j);
			}
		}
		
		printf("#%d %d\n", tc + 1, max);


	}
}