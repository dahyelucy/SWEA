#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

int dx[8] = { -1, -1, 0, 1, 1, 1, 0, -1 };
int dy[8] = { 0, 1, 1, 1, 0, -1, -1, -1 };
int map[9][9];
int N, M;
int cantGetCnt;

void init()
{
	N = 0; M = 0;
	for (int i = 0; i<9; i++) {
		for (int j = 0; j<9; j++) {
			map[i][j] = 0;
		}
	}
}

void changeColor(int x, int y, int color, int depth) {

	
	if (cantGetCnt >= 3) {
		return;
	}
	int colorChangeFlag = 0;
	
	map[x][y] = color;

	for (int k = 0; k<8; k++) {
		int nx = x + dx[k];
		int ny = y + dy[k];
		if (nx<=0 || ny<=0 || nx > N || ny > N) {
			continue;
		}
		//There is other color
		if (map[nx][ny] != color && map[nx][ny] != 0) {
			int nx2 = nx + dx[k];
			int ny2 = ny + dy[k];
			if (map[nx2][ny2] == color) {
				map[nx][ny] = color;
				colorChangeFlag = 1;
				changeColor(nx, ny, color, depth+1);
			}
		}
	}
	
	if (colorChangeFlag == 0 && depth == 0) {
		if (color == 1) {
			map[x][y] = 2;
			cantGetCnt++;
			changeColor(x, y, 2, depth);
			map[x][y] = 1;
		}
		else {
			map[x][y] = 1;
			cantGetCnt++;
			changeColor(x, y, 1, depth);
			map[x][y] = 2;
		}
	}
	
}

int main()
{
	int TC=0;
	freopen("input.txt", "r", stdin);
	scanf("%d", &TC);

	for (int tc = 0; tc<TC; tc++) {
		init();
		
		scanf("%d %d", &N, &M);
		map[N / 2][N / 2] = 2;
		map[N / 2][N / 2 + 1] = 1;
		map[N / 2 + 1][N / 2] = 1;
		map[N / 2 + 1][N / 2 + 1] = 2;

		for (int k = 0; k<M; k++) {
			int x, y, color;
			scanf("%d %d %d", &x, &y, &color);
			cantGetCnt = 0;
			changeColor(x, y, color, 0);
		}

		int blackCnt=0; int whiteCnt=0;
		for (int i = 1; i<=N; i++) {
			for (int j = 1; j<=N; j++) {
				if (map[i][j] == 1)
					blackCnt++;
				else if (map[i][j] == 2)
					whiteCnt++;
			}
		}
		printf("#%d %d %d\n", tc + 1, blackCnt, whiteCnt);
	}

	return 0;
}