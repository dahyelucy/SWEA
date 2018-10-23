#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>

typedef struct {
	int x;
	int y;
}point;

int map[16][16];
int visit[16][16];
point start, end;
bool ans = false;
int dx[4] = { 0, 1, 0, -1 };
int dy[4] = { 1,0,-1,0 };

void init() {
	start = { 0, 0 };
	end = { 0,0 };
	ans = false;
	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			map[i][j] = 0;
			visit[i][j] = 0;
		}
	}
}

void solve(point p) {

	if (p.x == end.x && p.y == end.y) {
		ans = true;
		return;
	}

	visit[p.x][p.y] = 1;

	for (int k = 0; k < 4; k++)
	{
		int nx = p.x + dx[k];
		int ny = p.y + dy[k];
		if (nx < 0 || ny < 0 || nx >= 16 || ny >= 16) {
			continue;
		}
		if (map[nx][ny] == 1) {
			continue;
		}
		if (map[nx][ny] == 3) {
			ans = true;
			return;
		}
		if (visit[nx][ny] == 0 && map[nx][ny] == 0) {
			point np = { nx, ny };
			solve(np);
			//visit[nx][ny] = 0;
		}

	}

	return;
}
int main() {

	int TC;
	//freopen("input.txt", "r", stdin);
	//scanf("%d", &TC);
	TC = 10;
	for (int k = 1; k <= TC; k++)
	{
		int t = 0;
		scanf("%d", &t);
		init();
		char temp[17];
		for (int i = 0; i < 16; i++)
		{
			scanf("%s", &temp);
			for (int j = 0; j < 16; j++)
			{
				map[i][j] = temp[j] - '0';
				if (map[i][j] == 2) {
					start.x = i;
					start.y = j;
				}
				if (map[i][j] == 3) {
					end.x = i;
					end.y = j;
				}
			}
		}

		solve(start);

		if (ans == true)
			printf("#%d %d\n", k, 1);
		else
			printf("#%d %d\n", k, 0);

	}
	return 0;
}