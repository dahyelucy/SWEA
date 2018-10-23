#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int x;
	int y;
	int val;
	int dir;
}node;

int R, C;
char map[20][20];
node visitHistory[88888];
int dx[4] = {-1,0,1,0};
int dy[4] = {0,1,0,-1};
int result;
int checkCnt;


void init() {
	result = 0;
	checkCnt = 0;
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			map[i][j] = '\0';
		}
	}
}

node checkBoundary(node now) {
	
	node temp = now;
	
	if (temp.dir == 0) {
		if (temp.x  < 0) {
			temp.x = R-1;
		}
	}
	else if (temp.dir == 1) {
		if (temp.y >= C) {
			temp.y = 0;
		}
	}
	else if (temp.dir == 2) {
		if (temp.x >= R) {
			temp.x = 0;
		}
	}
	else {
		if (temp.y < 0) {
			temp.y = C;
		}
	}

	return temp;
}

void solve(node now) {

	now = checkBoundary(now);

	int x = now.x;
	int y = now.y;

	for (int h = 0; h < checkCnt; h++)
	{
		if (visitHistory[h].x == now.x && visitHistory[h].y == now.y &&
			visitHistory[h].dir == now.dir && visitHistory[h].val == now.val) {
			return;
		}

	}
	visitHistory[checkCnt++] = now;

	node newNode = {};

	if (map[x][y] == '>') {
		newNode.dir = 1;
		newNode.x = x + dx[newNode.dir];
		newNode.y = y + dy[newNode.dir];
		newNode.val = now.val;
		solve(newNode);
	}
	else if (map[x][y] == '<') {
		newNode.dir = 3;
		newNode.x = x + dx[newNode.dir];
		newNode.y = y + dy[newNode.dir];
		newNode.val = now.val;
		solve(newNode);
	}
	else if (map[x][y] == '^') {
		newNode.dir = 0;	
		newNode.x = x + dx[newNode.dir];
		newNode.y = y + dy[newNode.dir];
		newNode.val = now.val;
		solve(newNode);
	}
	else if (map[x][y] == 'v') {
		newNode.dir = 2;
		newNode.x = x + dx[newNode.dir];
		newNode.y = y + dy[newNode.dir];
		newNode.val = now.val;
		solve(newNode);
	}
	else if (map[x][y] == '_') {
		if (now.val == 0) {
			newNode.dir = 1;
		}
		else {
			newNode.dir = 3;
		}
		newNode.x = x + dx[newNode.dir];
		newNode.y = y + dy[newNode.dir];
		newNode.val = now.val;
		solve(newNode);
	}
	else if (map[x][y] == '|') {
		if (now.val == 0) {
			newNode.dir = 2;
		}
		else {
			newNode.dir = 0;
		}
		newNode.x = x + dx[newNode.dir];
		newNode.y = y + dy[newNode.dir];
		newNode.val = now.val;
		solve(newNode);
	}
	else if (map[x][y] == '?') {
		for (int k = 0; k < 4; k++)
		{
			newNode.dir = k;
			if (x + dx[newNode.dir] < 0 || y + dy[newNode.dir] < 0 || x + dx[newNode.dir] >= C || y + dy[newNode.dir] >= R) {
				continue;
			}
			newNode.x = x + dx[newNode.dir];
			newNode.y = y + dy[newNode.dir];
			newNode.val = now.val;
			solve(newNode);
		}
	}
	else if (map[x][y] == '.') {
		newNode.val = now.val;
		newNode.dir = now.dir;
		newNode.x = x + dx[now.dir];
		newNode.y = y + dy[now.dir];
		solve(newNode);
	}
	else if (map[x][y] == '@') {
		result = 1;
		return;
	}
	else if (map[x][y] >= '0' && map[x][y] <= '9') {
		newNode.val = map[x][y] - '0';
		newNode.dir = now.dir;
		newNode.x = x + dx[now.dir];
		newNode.y = y + dy[now.dir];
		solve(newNode);
	}
	else if (map[x][y] == '+') {
		if (now.val == 15) {
			newNode.val = 0;
		}
		else {
			newNode.val = now.val + 1;
		}
		newNode.x = x + dx[now.dir];
		newNode.y = y + dy[now.dir];
		newNode.dir = now.dir;
		solve(newNode);
	}
	else if (map[x][y] == '-') {
		if (now.val == 0) {
			newNode.val = 15;
		}
		else {
			newNode.val = now.val - 1;
		}
		newNode.x = x + dx[now.dir];
		newNode.y = y + dy[now.dir];
		newNode.dir = now.dir;
		solve(newNode);
	}
	else {
		;
	}

	return;
}


void solve2(node now) {
	
	node newNode = {}; // 현재 노드 다음..
	newNode.x = now.x + dx[now.dir];
	newNode.y = now.y + dy[now.dir];
	newNode.val = now.val;
	newNode.dir = now.dir;

	newNode = checkBoundary(newNode);
	int x = newNode.x;
	int y = newNode.y;

	for (int h = 0; h < checkCnt; h++)
	{
		if (visitHistory[h].x == newNode.x && visitHistory[h].y == newNode.y &&
			visitHistory[h].dir == newNode.dir && visitHistory[h].val == newNode.val) {
			return;
		}

	}
	visitHistory[checkCnt++] = now;

	if (map[x][y] == '>') {
		newNode.dir = 1;
		solve(newNode);
	}
	else if (map[x][y] == '<') {
		newNode.dir = 3;
		solve(newNode);
	}
	else if (map[x][y] == '^') {
		newNode.dir = 0;
		solve(newNode);
	}
	else if (map[x][y] == 'v') {
		newNode.dir = 2;
		solve(newNode);
	}
	else if (map[x][y] == '_') {
		if (now.val == 0) {
			newNode.dir = 1;
		}
		else {
			newNode.dir = 3;
		}
		solve(newNode);
	}
	else if (map[x][y] == '|') {
		if (now.val == 0) {
			newNode.dir = 2;
		}
		else {
			newNode.dir = 0;
		}
		solve(newNode);
	}
	else if (map[x][y] == '?') {
		for (int k = 0; k < 4; k++)
		{
			newNode.dir = k;
			if (x + dx[newNode.dir] < 0 || y + dy[newNode.dir] < 0 || x + dx[newNode.dir] >= C || y + dy[newNode.dir] >= R) {
				continue;
			}
			solve(newNode);
		}
	}
	else if (map[x][y] == '.') {
		solve(newNode);
	}
	else if (map[x][y] == '@') {
		result = 1;
		return;
	}
	else if (map[x][y] >= '0' && map[x][y] <= '9') {
		newNode.val = map[x][y] - '0';
		solve(newNode);
	}
	else if (map[x][y] == '+') {
		if (now.val == 15) {
			newNode.val = 0;
		}
		else {
			newNode.val = now.val + 1;
		}
		solve(newNode);
	}
	else if (map[x][y] == '-') {
		if (now.val == 0) {
			newNode.val = 15;
		}
		else {
			newNode.val = now.val - 1;
		}
		solve(newNode);
	}
	else {
		;
	}

	return;

}

int main() {

	freopen("input2.txt", "r", stdin);
	int TC;
	scanf("%d", &TC);
	for (int tc = 0; tc < TC; tc++)
	{
		init();
		scanf("%d %d", &R, &C);
		for (int i = 0; i < R; i++)
		{
			char temp[21] = "";
			scanf("%s", temp);

			for (int j = 0; j < C; j++)
			{
				map[i][j] = temp[j];
			}
		}

		node newNode = {};
		if ('0' <= map[0][0] && map[0][0] <= '9') {
			newNode = { 0,0,map[0][0]-'0',1 };
		}
		else {
			newNode = { 0,0,0,1 };
		}
		solve2(newNode);
		if (result == 0) {
			printf("#%d NO\n", tc + 1);
		}
		else {
			printf("#%d YES\n", tc + 1);
		}

	}

	return 0;
}