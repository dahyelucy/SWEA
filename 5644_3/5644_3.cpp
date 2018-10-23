#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

typedef struct BC {
	int x;
	int y;
	int coverage;
	int power;
	int user;
}BC;

typedef struct User {
	int x;
	int y;
}User;

int maxPower;
int cnt;
int M, A;
int move[2][101];
int maxPowerArr[101];
User user[2];
BC bc[9];

int dx[5] = {0,0,1,0,-1};
int dy[5] = {0,-1,0,1,0};

void init() {
	M = 0; A = 0; maxPower = 0;
	cnt = 0;
	for (int i = 0; i < 2; i++)
	{
		user[i] = { 0,0 };
		for (int j = 0; j < 101; j++)
		{
			move[i][j] = 0;
		}
	}
	for (int i = 0; i < 9; i++)
	{
		bc[i] = { 0,0,0,0,0 };
	}
	for (int j = 0; j < 101; j++)
	{
		maxPowerArr[j] = 0;
	}
}

int abs(int a) {
	return (a > 0) ? a : -a;
}

bool isBoundary(User user, BC bc) {
	if (bc.coverage >= abs(bc.x - user.x) + abs(bc.y - user.y)) {
		return true;
	}
	return false;
}

void dfs(int u, int nowPower) {
	if (u == 3) {
		if (maxPower <= nowPower) {
			maxPower = nowPower;
		}
		return;
	}

	for (int i = 0; i < A; i++)
	{
		if (bc[i].user == 0 && isBoundary(user[u-1], bc[i])) {
			bc[i].user = u;
			dfs(u + 1, nowPower + bc[i].power);
			bc[i].user = 0;
		}
	}

	dfs(u + 1, nowPower);
}

void solve() {
		for (int j = 0; j <= M; j++)
		{
			for (int i = 0; i < 2; i++)
			{
				int x = user[i].x;
				int y = user[i].y;
				user[i].x = x + dx[move[i][j]];
				user[i].y = y + dy[move[i][j]];
			}
			dfs(1, maxPower);
		}
}

int main() {
	int TC;
	freopen("input.txt", "r", stdin);
	scanf("%d", &TC);
	for (int t = 1; t <= TC; t++)
	{
		init();
		scanf("%d %d", &M, &A);
		for (int i = 0; i < 2; i++)
		{
			for (int j = 1; j <= M; j++)
			{
				scanf("%d",&move[i][j]);
			}
		}
		for (int i = 0; i < A; i++)
		{
			int x, y, cov, power;
			scanf("%d %d %d %d", &x, &y, &cov, &power);
			bc[i].x = x;
			bc[i].y = y;
			bc[i].coverage = cov;
			bc[i].power = power;
			bc[i].user = 0;
		}

		user[0] = { 1,1 };
		user[1] = { 10,10 };
		solve();
		printf("#%d %d\n", t, maxPower);
	}
	return 0;
}