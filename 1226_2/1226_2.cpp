#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int x;
	int y;
}node;

int map[16][16];
int visited[16][16];
int dx[4] = { -1, 0, 1, 0 };
int dy[4] = { 0,1,0,-1 };
// 위, 오른, 아래, 왼
node start;
node end;
int result;

void init() {
	start.x = 0;
	start.y = 0;
	end.x = 0;
	end.y = 0;
	result = 0;
	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			map[i][j] = 0;
			visited[i][j] = 0;
		}
	}

}

void solve(node now) {
	
	visited[now.x][now.y] = 1;

	if (now.x == end.x && now.y == end.y) {
		result = 1;
		return ;
	}

	for (int k = 0; k < 4; k++)
	{
		int nx = now.x + dx[k];
		int ny = now.y + dy[k];

		if (nx < 0 || ny < 0 || nx >= 16 || ny >= 16) {
			continue;
		}

		if (visited[nx][ny] == 0 && (map[nx][ny] == 0 || map[nx][ny] == 3)) {
			node newNode;
			newNode.x = nx;
			newNode.y = ny;
			solve(newNode);
		}
	}

	return ;
}

int main() {

	freopen("input.txt", "r", stdin);
	for (int tc = 0; tc < 10; tc++)
	{	
		int tempTC = 0;
		scanf("%d", &tempTC);
		init();
		
		for (int i = 0; i < 16; i++)
		{
			char temp[17] = "";
			scanf("%s", temp);
			for (int j = 0; j < 16; j++)
			{
				if (temp[j]-'0' == 2) {
					start.x = i;
					start.y = j;
				}
				else if (temp[j]-'0' == 3) {
					end.x = i;
					end.y = j;
				}
				map[i][j] = temp[j]-'0';
			}
		}
		
		solve(start);

		if (result == 1) {
			printf("#%d %d\n", tc + 1, 1);
		}
		else {
			printf("#%d %d\n", tc + 1, 0);
		}
	}

	return 0;
}