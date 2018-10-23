#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

int people;
int location[1001];

int main()
{
	int tc;
	freopen("input.txt", "r", stdin);

	scanf("%d", &tc);

	for (int k = 0; k < tc; k++) {

		int min = 2123456789;
		int minCnt = 0;
		scanf("%d", &people);
		for (int i = 0; i < people; i++) {
			int temp = 0;
			scanf("%d", &temp);
			if (temp < 0) {
				location[i] = temp * (-1);
			}
			else {
				location[i] = temp;
			}
		}

		for (int i = 0; i < people; i++)
		{
			if (location[i] < min) {
				min = location[i];
				minCnt = 0;
			}

			if (min == location[i]) {
				minCnt++;
			}
		}

		printf("#%d %d %d\n", k + 1, min, minCnt);

		memset(location, 0, sizeof(location));
	}


}