#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>

#define Size 20


bool ans = false;
int R, C;
char map[Size][Size];
int check[10000][4];
int moveCnt;

int dir[4][2] = {
	{0,1}, {1,0}, {0,-1}, {-1,0} //오른쪽 아래 왼쪽 위
};

typedef struct info {
	int x;
	int y;
	int d;
	int memory;
};

void init() {
	ans = false;
	moveCnt = 0;
	for (int i = 0; i < Size; i++)
	{
		for (int j = 0; j < Size; j++)
		{
			map[i][j] = '\0';
		}
	}

	for (int i = 0; i < 10000; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			check[i][j] = 0;
		}
	}
}

info checkOutofMap(info cur) {
	info temp = cur;
	if (temp.x < 0){
		temp.x = R-1;
	}
	else if (temp.x >= R) {
		temp.x = 0;
	}
	else {
		;
	}

	if (temp.y < 0) {
		temp.y = C-1;
	}
	else if (temp.y >= C) {
		temp.y = 0;
	}
	else {
		;
	}
	return temp;
}

void solve(info cur) {
	
	cur = checkOutofMap(cur);
	info nxt = cur;

	//같은 곳에 같은 조건으로 방문한 적 있는지 확인
	for (int i = 0; i < moveCnt; i++)
	{
		if (check[i][0] == cur.x && check[i][1] == cur.y && check[i][2] == cur.d && check[i][3] == cur.memory) {
			return;
		}
	}

	check[moveCnt][0] = cur.x;
	check[moveCnt][1] = cur.y;
	check[moveCnt][2] = cur.d;
	check[moveCnt][3] = cur.memory;
	moveCnt++;

	if (map[cur.x][cur.y] == '.') {
		nxt.x = cur.x + dir[cur.d][0];
		nxt.y = cur.y + dir[cur.d][1];
		solve(nxt);
	}
	else if (map[cur.x][cur.y] == '@') {
		ans = true;
		return;
	}
	else if ('0' <= map[cur.x][cur.y] && map[cur.x][cur.y] <= '9') {
		nxt.x = cur.x + dir[cur.d][0];
		nxt.y = cur.y + dir[cur.d][1];
		nxt.memory = map[cur.x][cur.y] - '0';
		solve(nxt);
	}
	else if (map[cur.x][cur.y] == '+') {
		if (cur.memory == 15) {
			nxt.memory = 0;
		}
		else {
			nxt.memory = cur.memory + 1;
		}
		nxt.x = cur.x + dir[cur.d][0];
		nxt.y = cur.y + dir[cur.d][1];
		solve(nxt);
	}
	else if (map[cur.x][cur.y] == '-') {
		if (cur.memory == 0) {
			nxt.memory = 15;
		}
		else {
			nxt.memory = cur.memory - 1;
		}
		nxt.x = cur.x + dir[cur.d][0];
		nxt.y = cur.y + dir[cur.d][1];
		solve(nxt);
	}
	else if (map[cur.x][cur.y] == '>') {
		nxt.d = 0;
		nxt.x = cur.x + dir[nxt.d][0];
		nxt.y = cur.y + dir[nxt.d][1];
		solve(nxt);
	}
	else if (map[cur.x][cur.y] == '<') {
		nxt.d = 2;
		nxt.x = cur.x + dir[nxt.d][0];
		nxt.y = cur.y + dir[nxt.d][1];
		solve(nxt);
	}
	else if (map[cur.x][cur.y] == '^') {
		nxt.d = 3;
		nxt.x = cur.x + dir[nxt.d][0];
		nxt.y = cur.y + dir[nxt.d][1];
		solve(nxt);
	}
	else if (map[cur.x][cur.y] == 'v') {
		nxt.d = 1;
		nxt.x = cur.x + dir[nxt.d][0];
		nxt.y = cur.y + dir[nxt.d][1];
		solve(nxt);
	}
	else if (map[cur.x][cur.y] == '_') {
		if (cur.memory == 0) {
			nxt.d = 0;
			nxt.x = cur.x + dir[nxt.d][0];
			nxt.y = cur.y + dir[nxt.d][1];
		}
		else {
			nxt.d = 2;
			nxt.x = cur.x + dir[nxt.d][0];
			nxt.y = cur.y + dir[nxt.d][1];
		}
		solve(nxt);
	}
	else if (map[cur.x][cur.y] == '|') {
		if (cur.memory == 0) {
			nxt.d = 1;
			nxt.x = cur.x + dir[nxt.d][0];
			nxt.y = cur.y + dir[nxt.d][1];
		}
		else {
			nxt.d = 3;
			nxt.x = cur.x + dir[nxt.d][0];
			nxt.y = cur.y + dir[nxt.d][1];
		}
		solve(nxt);
	}
	else if (map[cur.x][cur.y] == '?') {
		for (int k = 0; k < 4; k++)
		{
			nxt.d = k;
			nxt.x = cur.x + dir[nxt.d][0];
			nxt.y = cur.y + dir[nxt.d][1];
			solve(nxt);
			if (ans == true) {
				return;
			}
		}
	}
	return;
}

int main() {
	freopen("input2.txt", "r", stdin);
	int TC = 0;
	scanf("%d", &TC);
	for (int t = 1; t <= TC; t++)
	{
		init();
		char temp[Size + 1];
		scanf("%d %d", &R, &C);
		for (int i = 0; i < R; i++)
		{
			scanf("%s", &temp);
			for (int j = 0; j < C; j++)
			{
				map[i][j] = temp[j];
			}
		}

		info stt = { 0,0,0,0 };
		solve(stt);
		if (ans == true) {
			printf("#%d YES\n", t);
		}
		else {
			printf("#%d NO\n", t);
		}
	}
	return 0;
}