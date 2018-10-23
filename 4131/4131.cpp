#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

int N, X;
int map[21][21];
int available;

int wdx[2] = { 0,0 };
int wdy[2] = { 1,-1 }; //0번째 인덱스는 오른쪽 방향 , 1번째 인덱스는 왼쪽 방향
int hdx[2] = { 1,-1 };
int hdy[2] = { 0,-0 }; // 0번째 인덱스는 아래 방향, 1번째 인덱스는 위쪽 방향


void init() {
	N = 0; X = 0;
	available = 0;
	for (int i = 0; i < 21; i++)
	{
		for (int j = 0; j < 21; j++)
		{
			map[i][j] = 0;
		}
	}
}

void solve() {
	//왼쪽-오른쪽 탐색
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			bool isMakable = true;
			//양쪽 방향 확인
			for (int k = 1; k <= X; k++)
			{
				int rx = i + wdx[0] * k;
				int ry = j + wdy[0] * k;
				int lx = i + wdx[1] * k;
				int ly = j + wdy[1] * k;
				if (ry >= N || ly < 0) {
					isMakable = false;
					continue;
				}
				if (map[i][j] - 1 == map[rx][ry] && map[i][j] - 1 == map[lx][ly]) {
					printf("(lx ly : %d %d) (i j : %d %d) (rx ry : %d %d)\n", lx, ly, i, j, rx, ry);
					continue;
				}
				else {
					isMakable = false;
					break;
				}
			}
			if (isMakable == true) {
				available++;
				break;
			}

			isMakable = true;
			//오른쪽 방향 확인
			for (int k = 1; k <= X; k++)
			{
				int rx = i + wdx[0] * k;
				int ry = j + wdy[0] * k;
				if (ry >= N) {
					isMakable = false;
					continue;
				}
				if ( (map[i][j] - 1 == map[rx][ry]) || (map[i][j] == map[rx][ry]) ) {
					printf("(i j : %d %d) (rx ry : %d %d)\n", i, j, rx, ry);
					continue;
				}
				else {
					isMakable = false;
					break;
				}
			}

			if (isMakable == true) {
				int isLarge = false;
				for (int f = 0;  f < j;  f++)
				{
					//위에서 경사로를 만들 수 있었지만 이전 값이 현재 값 보다 큰 경우
					if (map[i][f] > map[i][j]) {
						isLarge = true;
						break;
					}
				}
				if (isLarge == false) {
					available++;
					break;
				}
			}
				
			isMakable = true;
			//왼쪽 방향 확인
			for (int k = 1; k <= X; k++)
			{
				int lx = i + wdx[1] * k;
				int ly = j + wdy[1] * k;
				if (ly < 0) {
					isMakable = false;
					continue;
				}
				if ( (map[i][j] - 1 == map[lx][ly]) || (map[i][j] == map[lx][ly]) ) {
					printf("(lx ly : %d %d) (i j : %d %d)\n", lx, ly, i, j);
					continue;
				}
				else {
					isMakable = false;
					break;
				}
			}

			if (isMakable == true) {
				int isLarge = false;
				for (int f = j+1;  f < N;  f++)
				{
					//위에서 경사로를 만들 수 있었지만 다음 값이 현재 값 보다 큰 경우
					if (map[i][f] > map[i][j]) {
						isLarge = true;
						break;
					}
				}
				if (isLarge == false) {
					available++;
					break;
				}
			}
		}
	}

	//위-아래 탐색
	for (int j = 0; j < N; j++)
	{
		for (int i = 0; i < N; i++)
		{
			bool isMakable = true;
			//위-아래 방향 확인
			for (int k = 1; k <= X; k++)
			{
				int dx = i + hdx[0] * k;
				int dy = j + hdy[0] * k;
				int ux = i + hdx[1] * k;
				int uy = j + hdy[1] * k;
				if (dx >= N || ux < 0) {
					isMakable = false;
					continue;
				}

				if ( map[i][j] - 1 == map[dx][dy] && map[i][j] - 1 == map[ux][uy] )
					continue;
				else {
					isMakable = false;
					break;
				}
			}
			if (isMakable == true) {
				available++;
				break;
			}

			isMakable = true;
			//아래쪽 방향 확인
			for (int k = 1; k <= X; k++)
			{
				int dx = i + hdx[0] * k;
				int dy = j + hdy[0] * k;
				if (dx >= N) {
					isMakable = false;
					continue;
				}

				if ((map[i][j] - 1 == map[dx][dy]) || (map[i][j] == map[dx][dy])) {
					continue;
				}
				else {
					isMakable = false;
					break;
				}
			}

			if (isMakable == true) {
				int isLarge = false;
				for (int f = 0; f < i; f++)
				{
					//위에서 경사로를 만들 수 있었지만 이전 값이 현재 값 보다 큰 경우
					if (map[f][j] > map[i][j]) {
						isLarge = true;
						break;
					}
				}
				if (isLarge == false) {
					available++;
					break;
				}
			}

			isMakable = true;
			//위쪽 방향 확인
			for (int k = 1; k <= X; k++)
			{
				int ux = i + hdx[1] * k;
				int uy = j + hdy[1] * k;
				if (ux < 0) {
					isMakable = false;
					continue;
				}
				if ((map[i][j] - 1 == map[ux][uy])) {
					continue;
				}
				else {
					isMakable = false;
					break;
				}
			}

			if (isMakable == true) {
				int isLarge = false;
				for (int f = i + 1; f < N; f++)
				{
					//위에서 경사로를 만들 수 있었지만 다음 값이 현재 값 보다 큰 경우
					if (map[f][j] > map[i][j]) {
						isLarge = true;
						break;
					}
				}
				if (isLarge == false) {
					available++;
					break;
				}
			}
		}
	}
}
//예외 처리
void solveException() {

	//<->
	for (int i = 0; i < N; i++)
	{
		bool isMakable = true;
		int startValue = map[i][0];
		for (int j = 1; j < N; j++)
		{
			if (map[i][j] != startValue) {
				isMakable = false;
				break;
			}
		}
		if (isMakable == true) {
			available++;
		}
	}

	// ^v 
	for (int j = 0; j < N; j++)
	{
		bool isMakable = true;
		int startValue = map[0][j];
		for (int i = 1; i < N; i++)
		{
			if (map[i][j] != startValue) {
				isMakable = false;
				break;
			}
		}
		if (isMakable == true) {
			available++;
		}
	}
}
int main() {
	int TC;
	freopen("input.txt", "r", stdin);
	scanf("%d", &TC);
	for (int tc = 1; tc <= TC; tc++)
	{
		init();
		scanf("%d %d", &N, &X);
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				scanf("%d", &map[i][j]);
			}
		}
		solve();
		solveException();

		printf("#%d %d\n", tc, available);
	}
	return 0;
}