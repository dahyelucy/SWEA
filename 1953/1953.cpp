#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <queue>

using namespace std;
typedef struct Node {
	int x;
	int y;
	int dir;
	int level;
}Node;
int dx[4] = { -1, 0, 1, 0 };
int dy[4] = { 0, 1, 0, -1 };
int N, M, R, C, L;
int map[51][51];
int visited[51][51];
int available;
queue<Node> q;

void init() {
	N = 0, M = 0, R = 0, C = 0, L = 0;
	available = 0;
	for (int i = 0; i<51; i++)
	{
		for (int j = 0; j<51; j++) {
			map[i][j] = 0;
			visited[i][j] = 0;
		}
	}
	queue<Node> empty;
	swap(q, empty);
}

void pushNewNode(int x, int y, int dir, int bfLevel) {
	Node next;
	next.x = x;
	next.y = y;
	next.dir = dir;
	next.level = bfLevel + 1;
	q.push(next);
	visited[x][y] = next.level;
	available++;
}
void solve() {

	Node start;
	start.x = R; start.y = C;
	start.dir = map[R][C];
	start.level = 1;
	q.push(start);
	available++;
	visited[R][C] = 1;

	while (!q.empty()) {
		Node temp = q.front();
		q.pop();
		if (temp.level == L) {
			break;
		}

		switch (temp.dir)
		{
		case 1: {
			for (int k = 0; k < 4; k++) {
				int newX = temp.x + dx[k];
				int newY = temp.y + dy[k];
				if (newX < 0 || newY < 0 || newX >= N || newY >= M) {
					continue;
				}
				if (k == 0) {
					if ((map[newX][newY] == 1 || map[newX][newY] == 2 || map[newX][newY] == 5 || map[newX][newY] == 6) && visited[newX][newY] == 0) {
						pushNewNode(newX, newY, map[newX][newY], temp.level);
					}
				}
				else if (k == 1) {
					if ((map[newX][newY] == 1 || map[newX][newY] == 3 || map[newX][newY] == 6 || map[newX][newY] == 7) && visited[newX][newY] == 0) {
						pushNewNode(newX, newY, map[newX][newY], temp.level);
					}
				}
				else if (k == 2) {
					if ((map[newX][newY] == 1 || map[newX][newY] == 2 || map[newX][newY] == 4 || map[newX][newY] == 7) && visited[newX][newY] == 0) {
						pushNewNode(newX, newY, map[newX][newY], temp.level);
					}
				}
				else {
					if ((map[newX][newY] == 1 || map[newX][newY] == 3 || map[newX][newY] == 4 || map[newX][newY] == 5) && visited[newX][newY] == 0) {
						pushNewNode(newX, newY, map[newX][newY], temp.level);
					}
				}
			}
		}
				break;
		case 2: {
			int uX = temp.x + dx[0];
			int uY = temp.y + dy[0];
			int dX = temp.x + dx[2];
			int dY = temp.y + dy[2];

			if (uX >= 0 && uX < N && uY >= 0 && uY < M) {
				if ((map[uX][uY] == 1 || map[uX][uY] == 2 || map[uX][uY] == 5 || map[uX][uY] == 6) && visited[uX][uY] == 0) {
					pushNewNode(uX, uY, map[uX][uY], temp.level);
				}
			}
			if (dX >= 0 && dX < N && dY >= 0 && dY < M) {
				if ((map[dX][dY] == 1 || map[dX][dY] == 2 || map[dX][dY] == 4 || map[dX][dY] == 7) && visited[dX][dY] == 0) {
					pushNewNode(dX, dY, map[dX][dY], temp.level);
				}

			}
		}
				break;
		case 3: {
			int rX = temp.x + dx[1];
			int rY = temp.y + dy[1];
			int lX = temp.x + dx[3];
			int lY = temp.y + dy[3];

			if (rX >= 0 && rX < N && rY >= 0 && rY < M) {
				if ((map[rX][rY] == 1 || map[rX][rY] == 3 || map[rX][rY] == 6 || map[rX][rY] == 7) && visited[rX][rY] == 0) {
					pushNewNode(rX, rY, map[rX][rY], temp.level);
				}
			}
			if (lX >= 0 && lX < N && lY >= 0 && lY < M) {
				if ((map[lX][lY] == 1 || map[lX][lY] == 3 || map[lX][lY] == 4 || map[lX][lY] == 5) && visited[lX][lY] == 0) {
					pushNewNode(lX, lY, map[lX][lY], temp.level);
				}

			}
		}
				break;
		case 4: {
			int uX = temp.x + dx[0];
			int uY = temp.y + dy[0];
			int rX = temp.x + dx[1];
			int rY = temp.y + dy[1];

			if (uX >= 0 && uX < N && uY >= 0 && uY < M) {
				if ((map[uX][uY] == 1 || map[uX][uY] == 2 || map[uX][uY] == 5 || map[uX][uY] == 6) && visited[uX][uY] == 0) {
					pushNewNode(uX, uY, map[uX][uY], temp.level);
				}
			}
			if (rX >= 0 && rX < N && rY >= 0 && rY < M) {
				if ((map[rX][rY] == 1 || map[rX][rY] == 3 || map[rX][rY] == 6 || map[rX][rY] == 7) && visited[rX][rY] == 0) {
					pushNewNode(rX, rY, map[rX][rY], temp.level);
				}
			}
		}
				break;
		case 5: {
			int dX = temp.x + dx[2];
			int dY = temp.y + dy[2];
			int rX = temp.x + dx[1];
			int rY = temp.y + dy[1];

			if (dX >= 0 && dX < N && dY >= 0 && dY < M) {
				if ((map[dX][dY] == 1 || map[dX][dY] == 2 || map[dX][dY] == 4 || map[dX][dY] == 7) && visited[dX][dY] == 0) {
					pushNewNode(dX, dY, map[dX][dY], temp.level);
				}
			}
			if (rX >= 0 && rX < N && rY >= 0 && rY < M) {
				if ((map[rX][rY] == 1 || map[rX][rY] == 3 || map[rX][rY] == 6 || map[rX][rY] == 7) && visited[rX][rY] == 0) {
					pushNewNode(rX, rY, map[rX][rY], temp.level);
				}
			}
		}
				break;
		case 6: {
			int dX = temp.x + dx[2];
			int dY = temp.y + dy[2];
			int lX = temp.x + dx[3];
			int lY = temp.y + dy[3];

			if (dX >= 0 && dX < N && dY >= 0 && dY < M) {
				if ((map[dX][dY] == 1 || map[dX][dY] == 2 || map[dX][dY] == 4 || map[dX][dY] == 7) && visited[dX][dY] == 0) {
					pushNewNode(dX, dY, map[dX][dY], temp.level);
				}
			}
			if (lX >= 0 && lX < N && lY >= 0 && lY < M) {
				if ((map[lX][lY] == 1 || map[lX][lY] == 3 || map[lX][lY] == 4 || map[lX][lY] == 5) && visited[lX][lY] == 0) {
					pushNewNode(lX, lY, map[lX][lY], temp.level);
				}
			}
		}
				break;
		case 7: {
			int uX = temp.x + dx[0];
			int uY = temp.y + dy[0];
			int lX = temp.x + dx[3];
			int lY = temp.y + dy[3];

			if (uX >= 0 && uX < N && uY >= 0 && uY < M) {
				if ((map[uX][uY] == 1 || map[uX][uY] == 2 || map[uX][uY] == 5 || map[uX][uY] == 6) && visited[uX][uY] == 0) {
					pushNewNode(uX, uY, map[uX][uY], temp.level);
				}
			}
			if (lX >= 0 && lX < N && lY >= 0 && lY < M) {
				if ((map[lX][lY] == 1 || map[lX][lY] == 3 || map[lX][lY] == 4 || map[lX][lY] == 5) && visited[lX][lY] == 0) {
					pushNewNode(lX, lY, map[lX][lY], temp.level);
				}
			}
		}
				break;
		}
	}

}
int main() {
	int TC;
	//freopen("input.txt", "r", stdin);
	scanf("%d", &TC);
	for (int tc = 0; tc<TC; tc++) {
		init();
		scanf("%d %d %d %d %d", &N, &M, &R, &C, &L);
		for (int i = 0; i<N; i++) {
			for (int j = 0; j<M; j++) {
				scanf("%d", &map[i][j]);
			}
		}
		solve();
		printf("#%d %d\n", tc + 1, available);

	}
	return 0;
}