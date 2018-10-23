#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

int map[50][50];
int N;
int sum;

void init() {
	N = 0; sum = 0;
	for (int i = 0; i < 50; i++)
	{
		for (int j = 0; j < 50; j++)
		{
			map[i][j] = 0;
		}
	}
}

int main() {
	int TC;
	freopen("input.txt", "r", stdin);
	scanf("%d", &TC);
	for (int tc = 0; tc < TC; tc++)
	{
		init();
		scanf("%d", &N);
		for (int i = 0; i < N; i++)
		{
			char temp[51];
			scanf("%s", temp);
			for (int j = 0; j < N; j++)
			{
				if (temp[j] != NULL) {
					map[i][j] = temp[j] - '0';
				}
			}
		}

		for (int i = 0; i < N; i++)
		{
			if (i <= (N / 2)) {
				for (int j = N / 2 - i; j <= N / 2 + i; j++)
				{
					sum += map[i][j];
				}
			}
			else {
				for (int j = N / 2 - (N - i -1); j <= N / 2 + (N - i-1); j++)
				{
					sum += map[i][j];
				}
			}

		}
		printf("#%d %d\n", tc + 1, sum);
	}
	return 0;
}