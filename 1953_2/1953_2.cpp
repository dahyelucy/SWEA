#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <queue>

using namespace std;

typedef struct Node {
	int x;
	int y;
	int tunnel;
	int time;
}Node;
int N, M, R, C, L;
int cnt;
int dx[4] = { -1,0,1,0 };
int dy[4] = { 0,1,0,-1 };
int tunnel[8][4] = { {0,0,0,0}, {1,1,1,1}, {1,0,1,0}, {0,1,0,1}, {1,1,0,0}, {0,1,1,0}, {0,0,1,1}, {1,0,0,1} };
int map[51][51];
int visited[51][51];
queue<Node> q;


void init() {
	N = 0, M = 0, R = 0, C = 0, L = 0;
	cnt = 0;
	for (int i = 0; i < 51; i++)
	{
		for (int j = 0; j < 51; j++)
		{
			map[i][j] = 0;
			visited[i][j] = 0;
		}
	}
	queue<Node> empty;
	q = empty;
}

void solve() {
	Node start = { R,C, map[R][C], 1 };
	q.push(start);
	visited[R][C] = 1;
	cnt++;

	while (!q.empty()) {
		Node temp = q.front();
		q.pop();

		int x = temp.x; int y = temp.y; 
		int tun = temp.tunnel;  int time = temp.time;

		if (time == L) {
			break;
		}

		for (int k = 0; k < 4; k++)
		{
			int nx = x + dx[k];
			int ny = y + dy[k];
			if (nx < 0 || ny < 0 || nx >= N || ny >= M) {
				continue;
			}
			if (map[nx][ny] != 0 && visited[nx][ny]==0) {
				int ntun = map[nx][ny];
				//방향이 이어짐
				if (tunnel[tun][k] == 1 && tunnel[ntun][(k + 2) % 4] == 1) {
					Node temp2 = { nx, ny, ntun, time + 1 };
					q.push(temp2);
					visited[nx][ny] = 1;
					cnt++;
				}
			}
		}
	}
}


int main() {
	int T;
	freopen("input.txt", "r", stdin);
	scanf("%d", &T);
	for (int t = 1; t <= T; t++)
	{
		init();
		cin >> N >> M >> R >> C >> L;
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < M; j++)
			{
				cin >> map[i][j];
			}
		}
		solve();
		printf("#%d %d\n", t, cnt);
	}

	return 0;
}