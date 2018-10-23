#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <queue>

using namespace std;

typedef struct Node {
	int x;
	int y;
}Node;

int map[16][16];
int visited[16][16];
Node s;
Node e;

void init() {
	start = { 0,0 };
	e = { 0, 0 };
	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			map[i][j] = 0;
			visited[i][j] = 0;
		}
	}
}

void solve() {

}
int main() {

	freopen("input.txt", "r", stdin);
	for (int tc = 0; tc < 10; tc++)
	{
		int t;
		scanf("%d", &t);
		char temp[17];
		for (int i = 0; i < 16; i++)
		{
			scanf("%s", temp);
			for (int j = 0; j < 16; j++)
			{
				map[i][j] = temp[j] - '0';
				if (temp[j] - '0' == 2) {
					s = { i, j };
				}
				else if (temp[j] - '0' == 3) {
					e = { i, j };
				}
			}
		}
	}
	return 0;
}