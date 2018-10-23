#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

int arr[101][101];

int main()
{

	int tc = 10;
	freopen("input.txt", "r", stdin);

	for (int k = 0; k < tc; k++)
	{
		int temp = 0;
		scanf("%d", &temp);
		for (int i = 0; i < 100; i++)
		{
			for (int j = 0; j < 100; j++)
			{
				scanf("%d", &arr[i][j]);
			}
		}

		int MaxSum = -1;
		int NowSum = 0;
		for (int i = 0; i < 100; i++)
		{
			for (int j = 0; j < 100; j++) {
				NowSum += arr[i][j];
			}
			if (MaxSum < NowSum)
			{
				MaxSum = NowSum;
			}
			NowSum = 0;
		}

		NowSum = 0;
		for (int j = 0; j < 100; j++)
		{
			for (int i = 0; i < 100; i++)
			{
				NowSum += arr[i][j];
			}
			if (MaxSum < NowSum)
			{
				MaxSum = NowSum;
			}
			NowSum = 0;
		}

		NowSum = 0;
		for (int i = 0; i < 100; i++)
		{
			NowSum += arr[i][i];
		}
		if (MaxSum < NowSum)
		{
			MaxSum = NowSum;
		}

		NowSum = 0;
		for (int i = 0; i < 100; i++)
		{
			NowSum += arr[i][99 - i];
		}
		if (MaxSum < NowSum)
		{
			MaxSum = NowSum;
		}

		printf("#%d %d\n", k + 1, MaxSum);
		memset(arr, 0, sizeof(arr));
	}

	return 0;
}