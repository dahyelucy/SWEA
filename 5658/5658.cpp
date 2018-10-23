#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <algorithm>
#include <functional>

using namespace std;

int N, K;
char input[28];
char map[28][28];
int sortedArray[50];

void init() {
	N = 0; K = 0;
	for (int i = 0; i < 28; i++)
	{
		input[i] = '\0';
		for (int j = 0; j < 28; j++)
		{
			map[i][j] = '\0';
		}
	}
	for (int i = 0; i < 50; i++)
	{
		sortedArray[i] = 0;
	}
}

void solve() {
	for (int i = 0; i < N/4; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (j + i >= N) {
				map[i][j + i - N] = input[j];
			}
			else {
				map[i][j + i] = input[j];
			}		
		}
	}

	int cnt = 0;

	for (int i = 0; i < N/4; i++)
	{
		int sum = 0;
		for (int j = 0; j < N; j++)
		{
			for (int k = 0; k < N/4; k++)
			{
				if (j % (N / 4) == k) {

					if ('0' <= map[i][j] && map[i][j] <= '9') {
						sum += (map[i][j] - '0') * pow(16, N / 4 - k -1);
					}
					else {
						switch (map[i][j])
						{case 'A':
							sum += 10 * pow(16, N / 4 - k -1);
							break;
						case 'B':
							sum += 11 * pow(16, N / 4 - k -1);
							break;
						case 'C':
							sum += 12 * pow(16, N / 4 - k -1);
							break;
						case 'D':
							sum += 13 * pow(16, N / 4 - k -1);
							break;
						case 'E':
							sum += 14 * pow(16, N / 4 - k -1);
							break;
						case 'F':
							sum += 15 * pow(16, N / 4 - k -1);
							break;
						default:
							break;
						}

					}
				}
			}
			if (j % (N / 4) == N/4 -1) {
				sortedArray[cnt] = sum;
				cnt++;
				sum = 0;
			}
		}
	}

	sort(sortedArray, sortedArray + cnt + 1, greater<int>());

	for (int i = 0; i < cnt-1; i++)
	{
		if (sortedArray[i + 1] == sortedArray[i]) {
			sortedArray[i + 1] = 0;
		}
	}

	sort(sortedArray, sortedArray + cnt + 1, greater<int>());
}

int main() {
	int TC;
	freopen("input.txt", "r", stdin);
	scanf("%d", &TC);
	for (int tc = 1; tc <= TC; tc++)
	{
		init();
		scanf("%d %d", &N, &K);
		char temp[30] = "";
		scanf("%s", temp);
		for (int i = 0; i < N; i++)
		{
			input[i] = temp[i];
		}
		solve();
		printf("#%d %d\n", tc, sortedArray[K-1]);
	}
	return 0;
}