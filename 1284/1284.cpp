#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

int main()
{
	int tc = 0;

	freopen("input.txt", "r", stdin);
	scanf("%d", &tc);

	for (int k = 0; k < tc; k++)
	{
		int P; int Q; int R; int S; int W;
		scanf("%d %d %d %d %d", &P, &Q, &R, &S, &W);

		int A = W * P;
		int B = (R - W) < 0 ? Q + (W-R)*S : Q;

		//printf("A : %d  B : %d ", A, B);
		if (A > B)
		{
			printf("#%d %d\n",k + 1, B);
		}
		else
		{
			printf("#%d %d\n", k + 1, A);
		}

	}

	return 0;
}
