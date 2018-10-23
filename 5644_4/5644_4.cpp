#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

typedef struct BC {
	int x;
	int y;
	int c;
	int p;
}BC;

typedef struct User {
	int x;
	int y;
}User;

int M, A;
int move[2][101];
User user[2];
BC bc[9];
int visited[9];
int dx[5] = { 0,-1,0,1,0 };
int dy[5] = { 0,0,1,0,-1 };
int maxPower;

void init() {
	M = 0; A = 0; maxPower = 0;
	for (int u = 0; u < 2; u++)
	{
		user[u] = { 0,0 };
		for (int i = 0; i < 101; i++)
		{
			move[u][i] = 0;
		}
	}
	for (int b = 0; b < 9; b++)
	{
		bc[b] = { 0,0,0,0 };
		visited[b] = 0;
	}
}
int abs(int a) {
	return (a > 0) ? a : -a;
}
void dfs(int u, int mp) {
	if (u == 2) {
		if (mp > maxPower) {
			maxPower = mp;
		}
		return;
	}

	for (int i = 1; i <= A; i++)
	{
		int dist = abs(bc[i].x - user[u].x) + abs(bc[i].y - user[u].y);
		if (dist <= bc[i].c && visited[i]==0) {
			visited[i] = 1;
			dfs(u + 1, mp + bc[i].p);
			visited[i] = 0;
		}
	}

	dfs(u + 1, mp);

}
void solve() {
	for (int m = 0; m <= M; m++)
	{
		user[0].x = user[0].x + dx[move[0][m]];
		user[0].y = user[0].y + dy[move[0][m]];
		user[1].x = user[1].x + dx[move[1][m]];
		user[1].y = user[1].y + dy[move[1][m]];
		dfs(0, maxPower);
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
		for (int u = 0; u < 2; u++)
		{
			for (int m = 1; m <= M; m++)
			{
				scanf("%d", &move[u][m]);
			}
		}
		for (int a = 1; a <= A; a++)
		{
			int x, y, c, p;
			scanf("%d %d %d %d", &x, &y, &c, &p);
			bc[a] = { y,x,c,p };
		}
		user[0] = { 1,1 };
		user[1] = { 10,10 };
		solve();
		printf("#%d %d\n", t, maxPower);
	}
	return 0;
}