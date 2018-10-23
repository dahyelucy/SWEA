#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

typedef struct Worm {
	int x;
	int y;
}Worm;

typedef struct Hist {
	int x;
	int y;
	int dir;
}Hist;
int map[101][101];
int copy[101][101];
Worm worm[5][2];
int saveCnt[5];
int dx[4] = { -1,0,1,0 };
int dy[4] = { 0,1,0,-1 };
int N;
int MAX;
int roop, histCnt;
Hist hist[20000];

void init() {
	N = 0; MAX = -1;
	roop = 0; 
	for (int i = 0; i < 101; i++)
	{
		for (int j = 0; j < 101; j++)
		{
			map[i][j] = 0;
			copy[i][j] = 0;
		}
	}
	for (int i = 0; i < 5; i++)
	{
		saveCnt[i] = 0;
		for (int j = 0; j < 2; j++)
		{
			worm[i][j] = { 0,0 };
		}
	}
}

int returnDir(int blockNum, int inDir) {
	if (blockNum == 1) {
		switch (inDir)
		{
		case 0: return 2;
		case 1: return 3;
		case 2: return 1;
		case 3: return 0;
		default:
			break;
		}
	}
	else if (blockNum == 2) {
		switch (inDir)
		{
		case 0: return 1;
		case 1: return 3;
		case 2: return 0;
		case 3: return 2;
		default:
			break;
		}
	}
	else if (blockNum ==3) 
	{
		switch (inDir)
		{
		case 0: return 3;
		case 1:return 2;
		case 2:return 0;
		case 3: return 1;
		default:
			break;
		}
	}
	else if (blockNum ==4)
	{
		switch (inDir)
		{
		case 0: return 2;
		case 1: return 0;
		case 2: return 3;
		case 3: return 1;
		default:
			break;
		}
	}
	else if (blockNum == 5) {
		switch (inDir)
		{
		case 0: return 2;
		case 1: return 3;
		case 2: return 0;
		case 3: return 1;
		default:
			break;
		}
	}
	return -1;
}

int returnDir2(int dir) {
	switch (dir)
	{
	case 0: return 2;
	case 1: return 3;
	case 2: return 0;
	case 3: return 1;
	default:
		break;
	}
	return -1;
}

bool checkHist(int x, int y, int dir) {
	for (int i = 0; i < histCnt; i++)
	{
		//นÝบนตส
		if (hist[i].x == x && hist[i].y == y && hist[i].dir == dir) {
			return false;
		}
	}
	return true;
}
void start(int sx, int sy, int sdir) {
	int score = 0;
	int x = sx; int y = sy; int dir = sdir;
	while (true) {
		int nx = x + dx[dir];
		int ny = y + dy[dir];
		int ndir = dir;

		if (map[nx][ny] == -1 ||nx == sx && ny == sy ) {
			if (MAX < score) {
				MAX = score;
			}
			return;
		}
		else if (nx < 0 || ny < 0 || nx >= N || ny >= N) {
			score++;
			ndir = returnDir2(ndir);
		}
		else if (1 <= map[nx][ny] && map[nx][ny] <= 5) {
			score++;
			ndir = returnDir(map[nx][ny], ndir);
		}
		else if (6 <= map[nx][ny] && map[nx][ny] <= 10) {
			if (worm[map[nx][ny] - 6][0].x == nx && worm[map[nx][ny] - 6][0].y == ny) {
				int nnx = worm[map[nx][ny] - 6][1].x;
				int nny = worm[map[nx][ny] - 6][1].y;
				nx = nnx;
				ny = nny;
			}
			else if (worm[map[nx][ny] - 6][1].x == nx && worm[map[nx][ny] - 6][1].y == ny) {
				int nnx = worm[map[nx][ny] - 6][0].x;
				int nny = worm[map[nx][ny] - 6][0].y;
				nx = nnx;
				ny = nny;
			}
		}

		x = nx;
		y = ny;
		dir = ndir;
	}
}

void solve() {
	
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (map[i][j] == 0) {
				for (int d = 0; d < 4; d++)
				{
					start(i, j, d);
				}
			}
		}
	}
	
	//start(0, 4, 1);
}
int main() {
	int TC;
	freopen("input.txt", "r", stdin);
	scanf("%d", &TC);
	for (int t = 1; t <= TC; t++)
	{
		init();
		scanf("%d", &N);
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				scanf("%d", &map[i][j]);
				if (6 <= map[i][j] && map[i][j] <= 10) {
					if (saveCnt[map[i][j] - 6] == 0) {
						saveCnt[map[i][j] - 6]++;
						worm[map[i][j] - 6][0] = { i,j };
					}
					else if(saveCnt[map[i][j] - 6] == 1) {
						worm[map[i][j] - 6][1] = { i,j };
					}
				}
			}
		}

		solve();
		printf("#%d %d\n", t, MAX);
	}
	return 0;
}