#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int K;
int map[5][3][3]; //자석 저장 배열 0 은 안씀
int map2[5][3][3];
int moveDir[5];

int dx[8] = { -1, -1, 0, 1, 1, 1, 0, -1};
int dy[8] = { 0, 1, 1, 1, 0, -1, -1, -1};

void initTurn() {
	for (int i = 0; i < 5; i++)
	{
		moveDir[i] = 0;
	}
}

void init() {
	K = 0;

	for (int k = 0; k < 5; k++)
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				map[k][i][j] = 0;
				map2[k][i][j] = 0;
			}
		}
	}

	initTurn();
}

void updateMoveDir(int input, int dir) {
	switch (input) {
	case 1:
		moveDir[1] = dir;
		if (map[1][1][2] != map[2][1][0] && moveDir[2]==0) {
			
			updateMoveDir(2, dir*(-1));
		}
		break;
	case 2:
		moveDir[2] = dir;
		if (map[1][1][2] != map[2][1][0] && moveDir[1] == 0) {
			updateMoveDir(1, dir*(-1));
		}

		if (map[2][1][2] != map[3][1][0] && moveDir[3] == 0) {
			updateMoveDir(3, dir*(-1));
		}
		break;
	case 3:
		moveDir[3] = dir;
		if (map[2][1][2] != map[3][1][0] && moveDir[2] == 0) {
			updateMoveDir(2, dir*(-1));
		}

		if (map[3][1][2] != map[4][1][0] && moveDir[4] == 0) {
			updateMoveDir(4, dir*(-1));
		}
		break;
	case 4:
		moveDir[4] = dir;
		if (map[3][1][2] != map[4][1][0] && moveDir[3] == 0) {

			updateMoveDir(3, dir*(-1));
		}
		break;
	default:
		break;
	}
}

void moveMagnet() {
	for (int k = 1; k <= 4; k++)
	{
		map2[k][1][1] = map[k][1][1];
		//시계방향
		if (moveDir[k] == 1) {
			for (int d = 0; d < 8; d++)
			{
				int xAfter, yAfter;
				int xBefore, yBefore;
				if (d + 1 == 8) {
					xAfter = 1 + dx[0];
					yAfter = 1 + dy[0];
				}
				else {
					xAfter = 1 + dx[d + 1];
					yAfter = 1 + dy[d + 1];
				}
				xBefore = 1 + dx[d];
				yBefore = 1 + dy[d];
				map2[k][xAfter][yAfter] = map[k][xBefore][yBefore];
			}
		}
		//반시계방향
		else if (moveDir[k] == -1) {
			for (int d = 0; d < 8; d++)
			{
				int xAfter, yAfter;
				int xBefore, yBefore;
				if (d == 0) {
					xAfter = 1 + dx[7];
					yAfter = 1 + dy[7];
				}
				else {
					xAfter = 1 + dx[d - 1];
					yAfter = 1 + dy[d - 1];
				}
				xBefore = 1 + dx[d];
				yBefore = 1 + dy[d];
				map2[k][xAfter][yAfter] = map[k][xBefore][yBefore];
			}
		}
		else {
			for (int d = 0; d < 8; d++)
			{
				int nx = 1 + dx[d];
				int ny = 1 + dy[d];
				map2[k][nx][ny] = map[k][nx][ny];
			}
		}
	}

	for (int k = 1; k <= 4; k++)
	{
		map[k][1][1] = map2[k][1][1];
		for (int d = 0; d < 8; d++)
		{
			int nx = 1 + dx[d];
			int ny = 1 + dy[d];
			map[k][nx][ny] = map2[k][nx][ny];
		}
	}

}

int calcScore() {

	int score = 0;
	for (int k = 1; k <= 4; k++)
	{
		//S극이면
		if (map[k][0][1] == 1) {
			score += pow(2, (k - 1));
		}
	}
	return score;
}

int main() {
	int TC;
	freopen("input.txt", "r", stdin);
	scanf("%d", &TC);
	for (int tc = 1; tc <= TC; tc++)
	{
		init();
		scanf("%d", &K);
		//자석 입력받기
		for (int i = 1; i <= 4; i++)
		{
			map[i][1][1] = i;
			for (int k = 0; k < 8; k++)
			{
				int nx = 1 + dx[k];
				int ny = 1 + dy[k];
				scanf("%d", &map[i][nx][ny]);
			}
		}

		for (int i = 0; i < K; i++)
		{
			initTurn();
			int target, dir;
			scanf("%d %d", &target, &dir);
			updateMoveDir(target, dir);
			moveMagnet();
		}

		printf("#%d %d\n", tc, calcScore());
	}
	return 0;
}