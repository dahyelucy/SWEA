#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <queue>

using namespace std;

typedef struct Node {
	int to;
	int level;
}Node;

int N, start;
int map[101][101];
int visited[101];
int maxLevel[101];
int levelCnt;


void init() {
	N = 0; start = 0; levelCnt = 0;
	for (int i = 0; i<101; i++) {
		for (int j = 0; j<101; j++) {
			map[i][j] = 0;			
		}
		maxLevel[i] = 0;
		visited[i] = 0;
	}
}

void solve() {
	queue<Node> q;
	Node S;
	S.to = start;
	S.level = 1;
	q.push(S);
	visited[S.to] = 1;

	while (!q.empty()) {
		Node next = q.front();
		q.pop();
		//동일 레벨의 max 값이   현재
		if (maxLevel[next.level] < next.to) {
			maxLevel[next.level] = next.to;
		}

		for (int i = 0; i<101; i++) {
			if (map[next.to][i] != 0 && visited[i] == 0) {
				Node temp;
				temp.to = i;
				temp.level = next.level + 1;
				q.push(temp);
				visited[temp.to] = 1;
			}
		}
	}
}

int main() {
	int TC = 10;
	freopen("input.txt", "r", stdin);

	for (int tc = 0; tc<TC; tc++) {
		init();
		scanf("%d %d", &N, &start);
		for (int i = 0; i<N / 2; i++) {
			int from; int to;
			scanf("%d %d", &from, &to);
			map[from][to] = 1;
		}

		solve();

		for (int i = 1; i<101; i++) {
			if (maxLevel[i] != 0) {
				continue;
			}
			else {
				levelCnt = i-1;
				break;
			}
		}

		printf("#%d %d\n", tc + 1, maxLevel[levelCnt]);

	}

	return 0;
}
