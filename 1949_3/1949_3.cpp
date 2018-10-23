#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>


typedef struct node {
	int x;
	int y;
	int height;
	int length;
	int usedK;
}node;

int max;
int maxlength;
int N,K;
int map[8][8];
int visited[8][8];
int dx[4] = { -1, 0, 1, 0 };
int dy[4] = { 0,1,0,-1 };

void initVisited() {
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			visited[i][j] = 0;
		}
	}
}

void init() {
	N = 0; K = 0;
	max = 0;
	maxlength = 0;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			map[i][j] = 0;
		}
	}
	initVisited();
}

void findMax() {
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (max < map[i][j]) {
				max = map[i][j];
			}
		}
	}
}

void solve(node now) {
	
	visited[now.x][now.y] = 1;

	for (int k = 0; k < 4; k++)
	{
		int newX = now.x + dx[k];
		int newY = now.y + dy[k];
		if (newX < 0 || newY < 0 || newX >= N || newY >= N) {
			continue;
		}

		if (now.usedK == 0) {
			if (map[newX][newY] < now.height && visited[newX][newY] == 0) {
				node next = { newX, newY, map[newX][newY], now.length + 1, 0 };
				solve(next);
				visited[next.x][next.y] = 0;
			}
			else if (map[newX][newY] - K <now.height && visited[newX][newY] == 0) {
				node next = { newX, newY, now.height - 1, now.length + 1, 1 };
				solve(next);
				visited[next.x][next.y] = 0;
			}
		}
		else {
			if (map[newX][newY] < now.height && visited[newX][newY] == 0) {
				node next = { newX, newY, map[newX][newY], now.length + 1, 1 };
				solve(next);
				visited[next.x][next.y] = 0;
			}
		}
	}

	if (maxlength < now.length) {
		maxlength = now.length;
	}

	return;
}

int main() {
	int TC;
	freopen("input.txt", "r", stdin);

	scanf("%d", &TC);
	for (int tc = 0; tc < TC; tc++)
	{
		init();
		scanf("%d %d", &N, &K);
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				scanf("%d", &map[i][j]);
			}
		}

		findMax();

		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				if (map[i][j] == max) {
					initVisited();
					node start = { i, j, map[i][j], 1, 0 };
					solve(start);
				}
			}
		}

		printf("#%d %d\n", tc + 1, maxlength);

	}

	return 0;
}