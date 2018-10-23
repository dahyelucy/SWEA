#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

int map[25][25];

int main() {
	int N;
	int dir = 1;
	int numCnt = 1;
	int x = 0, y = -1;
	int tempN;

	scanf("%d", &N);
	tempN = N;
	while (true) {
		if (numCnt == N * N + 1) {
			break;
		}
		for (int i = 1; i <= tempN; i++)
		{
			y = y + dir;
			map[x][y] = numCnt;
			numCnt++;
		}
		tempN--;
		for (int i = 1; i <= tempN; i++) {
			x += dir;
			map[x][y] = numCnt;
			numCnt++;
		}
		dir *= -1;
	}

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			printf("%d ", map[i][j]);
		}
		printf("\n");
	}
	return 0;

}
