#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>

int main()
{
	int tc = 0; int N; int n; int cnt; int s = 1;
	int row;
	int col;
	int dal[11][11];

	freopen("input.txt", "r", stdin);
	scanf("%d", &tc);
	for (int k = 0; k < tc; k++)
	{
		N = 0;
		cnt = 1;
		row = 0;
		col = -1;
		s = 1;
		scanf("%d", &N);
		n = N;

		do
		{
			for (int i = 0; i < n; i++) {
				dal[row][col += s] = cnt++;
			}
			n--;
			if (n > 0) {
				for (int i = 0; i < n; i++)
				{
					dal[row += s][col] = cnt++;
				}
			}
			else
			{
				break;
			}
			s *= -1;
		} while (1);

		printf("#%d\n", k + 1);
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				printf("%d ", dal[i][j]);
			}
			printf("\n");
		}

		memset(dal, 0, sizeof(dal));
	}

}