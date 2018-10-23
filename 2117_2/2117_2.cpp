#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <queue>

using namespace std;

int N, M;
int MAX;
int map[21][21];
int dx[4] = {-1,0,1,0};
int dy[4] = {0,1,0,-1};

//queue로 하니까 시간초과 났음

void init() {
	N = 0; M = 0; MAX = -1;
	for (int i = 0; i < 21; i++)
	{
		for (int j = 0; j < 21; j++)
		{
			map[i][j] = 0;
		}
	}
}

void makeMap(int x, int y) {
	for (int k = 0; k <= N; k++)
	{
		int op = (k + 1)*(k + 1) + k * k;
		int homeCnt = 0;
		for (int i = (-1)*k; i <= k; i++)
		{
			if (i <= 0) {
				for (int j = (-1)*(k+i); j <= (k+i); j++)
				{
					int nx = x + i;
					int ny = y + j;
					if (nx < 0 || ny < 0 || nx >= N || ny >= N) {
						continue;
					}
					if (map[nx][ny] == 1) {
						homeCnt++;
					}
				}
			}
			else {
				for (int j = (-1)*(k - i); j <= (k - i); j++)
				{
					int nx = x + i;
					int ny = y + j;
					if (nx < 0 || ny < 0 || nx >= N || ny >= N) {
						continue;
					}
					if (map[nx][ny] == 1) {
						homeCnt++;
					}
				}
			}
		}
		if ((homeCnt * M - op) >= 0 && homeCnt > MAX) {
			MAX = homeCnt;
		}
	}
}

void solve() {

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			makeMap(i, j);
		}
	}

}

int main() {
	int TC;
	freopen("input.txt", "r", stdin);
	scanf("%d", &TC);
	for (int tc = 0; tc<TC; tc++) {
		init();
		scanf("%d %d", &N, &M);
		for (int i = 0; i<N; i++) {
			for (int j = 0; j<N; j++) {
				scanf("%d", &map[i][j]);
			}
		}

		solve();
		printf("#%d %d\n", tc + 1, MAX);
	}
	return 0;
}