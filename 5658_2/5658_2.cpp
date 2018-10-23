#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <algorithm>

using namespace std;

int N, K;
char map[8][29];
int numbers[50];

void init() {
	N = 0; K = 0;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 29; j++)
		{
			map[i][j] = '\0';
		}
	}
	for (int i = 0; i < 50; i++)
	{
		numbers[i] = 0;
	}
}

int charToNum(char A) {
	if ('0' <= A && A <= '9') {
		return A - '0';
	}
	else {
		switch (A)
		{
		case 'A' :
			return 10;
		case 'B':
			return 11;
		case 'C':
			return 12;
		case 'D':
			return 13;
		case 'E':
			return 14;
		case 'F':
			return 15;
		}
	}
	return 0;
}

void solve() {
	for (int i = 1; i < (N/4); i++)
	{
		for (int j = 0; j < N; j++)
		{
			int jdx = (j - 1) < 0 ? N - 1 : j - 1;
			map[i][j] = map[i - 1][jdx];
		}
	}
	
	int cnt = 0;
	int n = N / 4;

	for (int i = 0; i < (N/4); i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (j % n == 0) {
				cnt++;
			}
			numbers[cnt] += pow(16, n - (j % n) - 1) * (charToNum(map[i][j]));
		}
	}

	sort(numbers, numbers + cnt+1, greater<int>());

	for (int i = 0; i <= cnt; i++)
	{
		if (numbers[i + 1] == numbers[i]) {
			numbers[i + 1] = 0;
		}
	}
	sort(numbers, numbers + cnt + 1, greater<int>());
}

int main() {
	int TC;
	freopen("input.txt", "r", stdin);
	scanf("%d", &TC);
	for (int t = 1; t <= TC; t++)
	{
		init();
		scanf("%d %d", &N, &K);
		char temp[29] = "";
		scanf("%s", temp);
		for (int j = 0; j < N; j++)
		{
			map[0][j] = temp[j];
		}
		solve();
		printf("#%d %d\n", t, numbers[K - 1]);
	}
	return 0;
}