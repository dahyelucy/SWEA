#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>

#define Size 10

int N, K;
int map[Size][Size];
int visit[Size][Size];
int heighest;
int ans;

int dir[4][2] = {
	{-1,0}, {1,0}, {0,-1}, {0,1} 
};

typedef struct info {
	int h, w;
	int height;
	int usedK;
	int len;
};

void solve(info cur) {
	//현재 길이가 이전 길이보다 길어졌을 경우에만 저장
	ans = ans > cur.len ? ans : cur.len;

	for (int d = 0; d < 4; d++)
	{
		info nxt = cur;
		nxt.h += dir[d][0];
		nxt.w += dir[d][1];
		nxt.height = map[nxt.h][nxt.w];

		if (nxt.h < 0 || nxt.h >= N || nxt.w < 0 || nxt.w >= N) {
			continue;
		}
		if (visit[nxt.h][nxt.w])
			continue;

		if (nxt.height < cur.height) {
			visit[nxt.h][nxt.w] = 1;
			nxt.len++;
			solve(nxt);
			visit[nxt.h][nxt.w] = 0;
		}
		else {
			if (!cur.usedK && nxt.height - K < cur.height) {
				visit[nxt.h][nxt.w] = 1;
				nxt.len++;
				nxt.usedK = 1;
				nxt.height = cur.height - 1; 
				solve(nxt);
				visit[nxt.h][nxt.w] = 0;
			}
		}

	}
	return;
}

int main()
{
	freopen("input.txt", "r", stdin);
	int T;
	scanf("%d", &T);
	for (int t = 1; t <= T; t++)
	{
		scanf("%d %d", &N, &K);
		heighest = ans = 0;
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				scanf("%d", &map[i][j]);
				heighest = heighest > map[i][j] ? heighest : map[i][j];
			}
		}

		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				if (heighest == map[i][j]) {
					visit[i][j] = 1;
					info cur = { i, j, map[i][j], 0, 1 };
					solve(cur);
					visit[i][j] = 0;
				}
			}
		}
		printf("#%d %d\n", t, ans);
	}
	return 0;
}