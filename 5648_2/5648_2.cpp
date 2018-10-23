#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

typedef struct atom {
	int x;
	int y;
	int dir;
	int energy;
}atom;

typedef struct node {
	int cnt;
	int energySum;
}node;

int N;
int energySumAns;
atom arr[1001];
node visited[4001][4001];

void init() {
	N = 0; energySumAns = 0;
	for (int i = 0; i < 1001; i++)
	{
		arr[i] = { 0,0,0,0 };
	}
	for (int i = 0; i < 4001; i++)
	{
		for (int j = 0; j < 4001; j++)
		{
			visited[i][j] = { 0,0 };
		}
	}
}


void removeAtom(int n, int *pnSize) {
	int nLastIndex = (*pnSize) - 1;
	arr[n].x = arr[nLastIndex].x;
	arr[n].y = arr[nLastIndex].y;
	arr[n].dir = arr[nLastIndex].dir;
	arr[n].energy = arr[nLastIndex].energy;
	(*pnSize)--;
}

void checkCollision(int *pnSize) {
	for (int i = 0; i < N; i++)
	{
		int x = arr[i].x;
		int y = arr[i].y;
		if (visited[x][y].cnt >= 2) {
			energySumAns += visited[x][y].energySum;
			visited[x][y] = { 0,0 };
			removeAtom(i, pnSize);
			i--;
		}
	}
}
void solve() {

	int nRest = N;

	for (int k = 0; k < 4000; k++)
	{
		//원소 이동
		for (int i = 0; i < N; i++)
		{
			int x = arr[i].x;
			int y = arr[i].y;
			visited[x][y].cnt--;
			visited[x][y].energySum -= arr[i].energy;
			if (arr[i].dir == 0) {
				y++;
			}
			else if (arr[i].dir == 1) {
				y--;
			}
			else if (arr[i].dir == 2) {
				x--;
			}
			else if (arr[i].dir == 3) {
				x++;
			}

			if (x < 0 || y < 0 || x >= 4000 || y >= 4000) {
				removeAtom(i, &nRest);
				i--;
			}
			else {
				visited[x][y].cnt++;
				visited[x][y].energySum += arr[i].energy;
				arr[i].x = x;
				arr[i].y = y;
			}
			
		}
		//충돌 확인
		checkCollision(&nRest);

		if (nRest == 0)
			break;
	}
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
			arr[i].x = (x + 1000) * 2;
			arr[i].y = (y + 1000) * 2;
			arr[i].dir = dir;
			arr[i].energy = energy;
			visited[arr[i].x][arr[i].y].cnt++;
			visited[arr[i].x][arr[i].y].energySum = arr[i].energy;
		}
		solve();
		printf("#%d %d\n", tc, energySumAns);
	}
	return 0;
}