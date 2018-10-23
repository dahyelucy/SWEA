#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

int T, N;
int map[20][20];
int visited[101];
int max, cnt;

void initVisited() {
	for (int i = 0; i < 101; i++)
	{
		visited[i] = 0;
	}
}

void init() {
	
	N = 0;
	max = 0; cnt = 0;

	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			map[i][j] = 0;
		}
	}

	initVisited();
}

void solve() {
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			for (int a = 1; a <= N; a++)
			{
				for (int b = 1; b <= N; b++)
				{
					if (i - a < 0 || j + a + b >= N || i + b >= N) {
						continue; 
					}

					int nx = i; int ny = j;
					int cannotEat = 0;
					initVisited();

					for (int k = 0; k < a; k++)
					{
						if (visited[map[nx][ny]] == 0) {
							visited[map[nx][ny]] = 1;
							cnt++;
						}
						else {
							cannotEat = 1;
							break;
						}
						nx--; ny++;
					}

					if (cannotEat == 1) {
						cnt = 0;
						continue;
					}

					for (int k = 0; k < b; k++)
					{
						if (visited[map[nx][ny]] == 0) {
							visited[map[nx][ny]] = 1;
							cnt++;
						}
						else {
							cannotEat = 1;
							break;
						}
						nx++; ny++;
					}

					if (cannotEat == 1) {
						cnt = 0;
						continue;
					}

					for (int k = 0; k < a; k++)
					{
						if (visited[map[nx][ny]] == 0) {
							visited[map[nx][ny]] = 1;
							cnt++;
						}
						else {
							cannotEat = 1;
							break;
						}
						nx++; ny--;
					}

					if (cannotEat == 1) {
						cnt = 0;
						continue;
					}

					for (int k = 0; k < b; k++)
					{
						if (visited[map[nx][ny]] == 0) {
							visited[map[nx][ny]] = 1;
							cnt++;
						}
						else {
							cannotEat = 1;
							break;
						}
						nx--; ny--;
					}
					
					if (cannotEat == 1) {
						cnt = 0;
						continue;
					}

					if (max < cnt) {
						max = cnt;
					}

					cnt = 0;
				}
			}
		}
	}
}
int main()
{
	freopen("input.txt", "r", stdin);
	scanf("%d", &T);

	for (int tc = 0; tc < T; tc++)
	{
		init();
		scanf("%d", &N);
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				scanf("%d", &map[i][j]);
			}
		}

		solve();

		if (max == 0) {
			printf("#%d %d\n", tc + 1, -1);
		}
		else {
			printf("#%d %d\n", tc + 1, max);
		}
		

	}

	return 0;
}