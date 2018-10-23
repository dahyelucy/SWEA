#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>

using namespace std;

int N;
int M;
int base[10][7] = {
	{0,0,0,1,1,0,1},
	{0,0,1,1,0,0,1},
	{0,0,1,0,0,1,1},
	{0,1,1,1,1,0,1},
	{0,1,0,0,0,1,1},
	{0,1,1,0,0,0,1},
	{0,1,0,1,1,1,1},
	{0,1,1,1,0,1,1},
	{0,1,1,0,1,1,1},
	{ 0,0,0,1,0,1,1 }
};
int map[51][101];
int result[8];
int realResult;
int middleTest;

void init()
{

	realResult = 0;
	middleTest = 0;
	N = 0; M = 0;

	memset(map, 0, sizeof(map));
	memset(result, 0, sizeof(result));

	for (int i = 0; i < 51; i++)
	{
		for (int j = 0; j < 101; j++)
		{
			map[i][j] = 0;
		}
	}

	for (int i = 0; i < 8; i++)
	{
		result[i] = 0;
	}
}


void returnNumber(int x, int y) {
	
	int temp[7];//암호에서 하나씩 읽어들이는 값
	int tempcnt = 0;
	int resultCnt = 0;
	for (int i = 0; i < 56; i++) {
	
		temp[tempcnt++] = map[x][y + i];

		//7의 배수가 아니면 계속 숫자를 모음
		if ((i + 1) % 7 == 0) {
		//7의 배수이면 기준코드와 비교 시작
			for (int  a = 0; a < 10; a++)
			{
				int sameflag = false;
				for (int b = 0; b < 7; b++)
				{
					if(temp[b] == base[a][b]) {
						sameflag = true;
						continue;
					}
					else {
						sameflag = false;
						break;
					}
				}
				if (sameflag == true) {
					result[resultCnt] = a;
				}
			}
			tempcnt = 0;
			resultCnt++;
			memset(temp, 0, sizeof(temp));
		}
	}
}

int main() {

	freopen("input.txt", "r", stdin);
	int tc = 0;
	scanf("%d", &tc);

	for (int k = 0; k < tc; k++)
	{
		char tmpString[101];
		init();
		scanf("%d %d", &N, &M);

		for (int i = 0; i < N; i++)
		{
			scanf("%s", tmpString);
			for (int j = 0; j < 101; j++)
			{
				if (tmpString[j] != '\0') {
					map[i][j] = tmpString[j] - '0';
				}
			}
		}
		//find last number1
		int x = 0;
		int y = 0;
		bool lastOneflag = false;
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < M; j++)
			{
				if (map[i][j] == 1) {
					x = i; y = j;
					lastOneflag = true;
				}
			}
			if (lastOneflag == true)
				break;
		}

		returnNumber(x, y - 55);

		int oddSum = 0;
		int evenSum = 0;

		for (int i = 0; i < 7; i++)
		{
			// 홀수이면
			if ((i + 1) % 2 == 1) {
				oddSum += result[i];
			}
			else if((i + 1) % 2 == 0){
				evenSum += result[i];
			}
		}

		middleTest = oddSum * 3 + evenSum + result[7];

		if (middleTest % 10 == 0) {
			
			for (int i = 0; i < 8; i++)
			{
				realResult += result[i];
			}
			printf("#%d %d\n", k+1, realResult);
		}
		else
		{
			printf("#%d %d\n", k + 1, 0);
		}

	}


	return 0;
}