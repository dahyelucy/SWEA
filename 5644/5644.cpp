#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

typedef struct BC {
	int y;
	int x;
	int coverage;
	int performance;
}BC;

typedef struct Exist {
	int bcNum;
	int performance;
}Exist;

typedef struct node {
	Exist exist[9];
	int max1;
	int max2;
}node;

int M, A;
int moveA[101];
int moveB[101];
int Azzim[9];
int dy[5] = {0,-1,0,1,0};
int dx[5] = { 0,0,1,0,-1 };
node Map[11][11];
BC bc[9];
int ax, ay;
int bx, by;
int asum, bsum;

//i는 y 방향, j는 x 방향

void init();
void makeRange();
int checkSameRange(int, int, int, int);
int rtMaxPerf_forNotSameRagne(int, int);
int rtMaxPerf_forSameRange(int, int, int, char);

void init() {
	M = 0; A = 0;
	for (int i = 0; i < 101; i++)
	{
		moveA[i] = 0;
		moveB[i] = 0;
	}
	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 11; j++)
		{
			for (int k = 0; k < 9; k++)
			{
				Map[i][j].exist[k] = { 0,0 };
			}
		}
	}
	for (int i = 0; i < 9; i++)
	{
		bc[i] = { 0,0,0,0 };
		Azzim[i] = 0;
	}
	ay = 1; ax = 1;
	by = 10; bx = 10;
}

void makeRange() {
	for (int k = 1; k <= A; k++)
	{
		int n = bc[k].coverage;
		int range = 2 * n + 1;

		int x = bc[k].x;
		int y = bc[k].y;
		int perf = bc[k].performance;
		for (int i = 0; i <= range; i++)
		{
			int ty = i - n;
			if (i <= range / 2) {
				
				for (int j = i*(-1); j <= i; j++)
				{
					int dy = y + ty;
					int dx = x + j;
					if (dy < 1 || dx < 1 || dy >= 11 || dx >= 11) {
						continue;
					}
					else {
						Map[dy][dx].exist[k].bcNum = k;
						Map[dy][dx].exist[k].performance = perf;
					}
				}
			}
			else {
				for (int j = (n -ty)*(-1); j <= (n-ty); j++)
				{
					int dy = y + ty;
					int dx = x + j;
					if (dy < 1 || dx < 1 || dy >= 11 || dx >= 11) {
						continue;
					}
					else {
						Map[dy][dx].exist[k].bcNum = k;
						Map[dy][dx].exist[k].performance = perf;
					}
				}
			}
			
		}
	}
}


int checkSameRange(int ay, int ax, int by, int bx) {
	bool existBC = false;
	for (int i = 1; i <= A; i++)
	{
		if (Map[ay][ax].exist[i].bcNum == Map[by][bx].exist[i].bcNum) {
			if (Map[ay][ax].exist[i].bcNum != 0) {
				return i;
			}
		}
		else {
			if (Map[ay][ax].exist[i].bcNum != 0 || Map[by][bx].exist[i].bcNum != 0) {
				return -1;
			}
		}
	}
	return 0;
}

int rtMaxPerf_forNotSameRagne(int y, int x) {
	int max = 0;
	for (int i = 1; i <= A; i++)
	{
		//해당 바운더리에 있는 BC의 perf값 중, max값을 반환
		if (Map[y][x].exist[i].performance > max) {
			max = Map[y][x].exist[i].performance;
		}
	}
	return max;
}


int rtMaxPerf_forSameRange(int y, int x, int temp, char AorB) {
	int max = 0;
	return max;
}

int rtMaxPerf_forSameRange2(int y, int x, int temp, char AorB) {
	int max = 0;
	if (AorB == 'a') {
		int maxIndex = 0;
		for (int i = 1; i <= A; i++)
		{
			if (Map[y][x].exist[i].performance > max && Map[y][x].exist[i].performance > temp) {
				max = Map[y][x].exist[i].performance;
				maxIndex = i;
			}
			else if (Map[y][x].exist[i].performance < temp && temp > max) {
				max = temp;
			}
		}
		if (maxIndex != 0) {
			Azzim[maxIndex] = 1;
		}
	}
	else {
		for (int i = 1; i <= A; i++)
		{
			if (Azzim[i] == 1) {
				continue;
			}
			if (Map[y][x].exist[i].performance > max && Map[y][x].exist[i].performance > temp) {
				max = Map[y][x].exist[i].performance;
			}
			else if (Map[y][x].exist[i].performance < temp && temp > max) {
				max = temp;
			}
		}
	}
	return max;
}

void solve() {
	makeRange();
	for (int t = 0; t <= M; t++)
	{
		int nay = ay + dy[moveA[t]];
		int nax = ax + dx[moveA[t]];

		int nby = by + dy[moveB[t]];
		int nbx = bx + dx[moveB[t]];

		int rtBCNum = checkSameRange(nay, nax, nby, nbx);
		//동일 바운더리가 아닌 경우
		if (rtBCNum == -1) {
			asum += rtMaxPerf_forNotSameRagne(nay, nax);
			bsum += rtMaxPerf_forNotSameRagne(nby, nbx);
		}
		else if (rtBCNum == 0) {
			continue;
		}
		//동일 바운더리인 경우
		else {
			int tmpA = Map[nay][nax].exist[rtBCNum].performance / 2;
			int tmpB = Map[nby][nbx].exist[rtBCNum].performance / 2;
			asum += rtMaxPerf_forSameRange(nay, nax, tmpA, 'a');
			bsum += rtMaxPerf_forSameRange(nby, nbx, tmpB, 'b');
		}
		ay = nay;
		ax = nax;
		by = nby;
		bx = nbx;
	}
}
int main() {
	int TC;
	freopen("input2.txt", "r", stdin);
	scanf("%d", &TC);
	for (int tc = 1; tc <= TC; tc++)
	{
		init();
		scanf("%d %d", &M, &A);
		for (int i = 1; i <= M; i++)
		{
			scanf("%d", &moveA[i]);
		}
		for (int i = 1; i <= M; i++)
		{
			scanf("%d", &moveB[i]);
		}
		for (int i = 1; i <= A; i++)
		{
			int x, y, cov, perf;
			scanf("%d %d %d %d", &x, &y, &cov, &perf);
			bc[i].x = x;
			bc[i].y = y;
			bc[i].coverage = cov;
			bc[i].performance = perf;
		}

		solve();
		printf("#%d %d", tc, asum + bsum);

	}
	return 0;
}