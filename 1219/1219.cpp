#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <queue>

using namespace std;

int N;
int result;
int map1[101];
int map2[101];
int visited1[101];
int visited2[101];

typedef struct edge {
	int from;
	int to;
}edge;


void init() {
	N = 0; result = 0;
	for (int i = 0; i < 101; i++)
	{
		map1[i] = 0;
		map2[i] = 0;
		visited1[i] = 0;
		visited2[i] = 0;
	}
}

void solve() {
	queue<edge> q;
	edge start = { 0, map1[0] };
	q.push(start);
	visited1[0] = 1;
	if (map2[0] != NULL) {
		edge start2 = { 0, map2[0] };
		q.push(start2);
		visited2[0] = 1;
	}

	while (!q.empty()) {
		edge temp = q.front();
		q.pop();
		if (temp.to == 99) {
			result = 1;
			break;
		}
		if(map1[temp.to] != NULL){
			edge next = { temp.to, map1[temp.to] };
			q.push(next);
			visited1[temp.to] = 1;
			
		}
		if (map2[temp.to] != NULL) {
			edge next2 = { temp.to, map2[temp.to] };
			q.push(next2);
			visited2[temp.to] = 1;
		}
	}

}
int main() {
	

	freopen("input.txt", "r", stdin);

	for (int tc = 0; tc < 10; tc++)
	{
		init();
		int temp = 0;
		scanf("%d %d", &temp, &N);

		for (int i = 0; i < N; i++)
		{
			int from = 0; int to = 0;
			scanf("%d %d", &from, &to);
			if (map1[from] == NULL) {
				map1[from] = to;
			}
			else {
				map2[from] = to;
			}
		}

		solve();

		printf("#%d %d\n", tc + 1, result);
	}

	return 0;
}