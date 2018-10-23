#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	int state; //0 빈공간 1 사람 2 계단
	int time;
	bool isStairs;
	int personNum;
	bool isWaiting;
}Node;

typedef struct Stairs {
	int x;
	int y;
	int personCnt;
	int height;
}Stairs;

Node map[11][11];
Node copy[11][11];
Stairs stairs[3];
int N;
int pCnt;
int min=2123456789;
int check[10]; //각 사람들이 어떤 계단을 탈지 저장

void init() {
	N = 0; pCnt = 0;
	min = 2123456789;

	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 11; j++)
		{
			map[i][j] = { 0,0,0,0,0 };
			copy[i][j] = { 0,0,0,0,0 };
		}
	}

	for (int i = 0; i < 10; i++)
	{
		check[i] = 0;
	}

	for (int i = 0; i < 3; i++)
	{
		stairs[i] = { 0,0,0,0 };
	}
}

int abs(int a) {
	return (a > 0) ? a : -a;
}
void copyMap() {
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			copy[i][j] = map[i][j];
		}
	}
}
void mapCopy() {
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			map[i][j] = copy[i][j];
		}
	}
}
//각자 정해진 계단으로 이동
int gotoStairs() {

	//person 시간 업데이트
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (map[i][j].state == 1) {
				int sx = stairs[check[map[i][j].personNum]].x;
				int sy = stairs[check[map[i][j].personNum]].y;
				map[i][j].time = abs(i - sx) + abs(j - sy);
			}
		}
	}

	int time = 1;
	int ppCnt = pCnt;
	while (ppCnt>0) {
		time++;
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				//사람이면
				if (map[i][j].state == 1) {
					//계단 아니면
					if (map[i][j].isStairs == false && map[i][j].time != 0) {
						map[i][j].time--;
					}
					//계단이면
					if (map[i][j].isStairs == true && map[i][j].isWaiting == false) {
						map[i][j].time++;
						if (map[i][j].time == stairs[check[map[i][j].personNum]].height) {
							stairs[check[map[i][j].personNum]].personCnt--;
							map[i][j] = { 0,0,false,0 };
							ppCnt--;
							continue;
						}
					}
					if (map[i][j].time == 0) {
						if (stairs[check[map[i][j].personNum]].personCnt < 3) {
							stairs[check[map[i][j].personNum]].personCnt++;
							map[i][j].isStairs = true;
							map[i][j].isWaiting = false;
						}
						else {
							map[i][j].isStairs = true;
							map[i][j].time = 0;
							map[i][j].isWaiting = true;
						}
					}
				}
			}
		}
	}

	return time;
}

void dfs(int depth) {
	if (depth == pCnt+1) {
		int nowTime = gotoStairs();
		if (nowTime < min) {
			min = nowTime;
		}
		mapCopy();
		return;
	}

	for (int i = 1; i <= 2; i++)
	{
		check[depth] = i;
		dfs(depth + 1);
	}
}

void solve() {
	dfs(1);
}


int main() {
	int TC;
	freopen("input2.txt", "r", stdin);
	scanf("%d", &TC);
	for (int t = 1; t <= TC; t++)
	{
		init();
		scanf("%d", &N);
		int sCnt = 1;
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				int temp;
				scanf("%d", &temp);
				if (temp == 1) {
					pCnt++;
					map[i][j].state = 1;
					map[i][j].time = 0;
					map[i][j].personNum = pCnt;
				}
				else if (2 <= temp && temp <= 10) {
					map[i][j].state = 2;
					stairs[sCnt].x = i;
					stairs[sCnt].y = j;
					stairs[sCnt].personCnt = 0;
					stairs[sCnt].height = temp;
					sCnt++;
				}
			}
		}

		copyMap();
		solve();

		printf("#%d %d\n", t, min);
	}
	return 0;
}