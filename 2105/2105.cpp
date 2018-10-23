#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

int tc;
int N; 
int isVisit[101];
int map[20][20];
int result;

void visitClear()
{
	for (int i = 0; i < 101; i++)
	{
		isVisit[i] = 0;
	}
}

void init()
{
	visitClear();
	result = -1;
}

void solve()
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			for (int a = 1; a < N; a++)
			{
				for (int b = 1; b < N; b++)
				{

					if (j + a  <  N && // 오른쪽 범
						i + a + b < N && //왼쪽 범위
						j - b >= 0 && //아래쪽 범위
						(a + b) * 2 > result) //현재 경로가 이전 경로보다 길 경우
					{
						printf("i : %d j : %d a : %d b : %d\n", i, j, a, b);
						visitClear();
						bool isAble = true;
						int curi = i;
						int curj = j;

						//우측 하단, 좌측 하단, 좌측 상단, 우측 상단
						//시계 방향 순서로 확인
						for (int t = 0; t < a; t++)
						{
							curi++; curj++;
							if (isVisit[map[curi][curj]] == 0) {
								isVisit[map[curi][curj]] = 1;
							}
							else
							{
								isAble = false;
								break;
							}
						}
						if (!isAble) continue;

						for (int t = 0; t < b; t++)
						{
							curi++; curj--;
							if (isVisit[map[curi][curj]] == 0) {
								isVisit[map[curi][curj]] = 1;
							}
							else
							{
								isAble = false;
								break;
							}
						}

						if (!isAble) continue;

						for (int t = 0; t < a; t++) {
							curi--; curj--;
							if (isVisit[map[curi][curj]] == 0) {
								isVisit[map[curi][curj]] = 1;
							}
							else
							{
								isAble = false;
								break;
							}
						}

						if (!isAble) continue;

						for (int t = 0; t < b; t++)
						{
							curi--; curj++;
							if (isVisit[map[curi][curj]] == 0) {
								isVisit[map[curi][curj]] = 1;
							}
							else
							{
								isAble = false;
								break;
							}
						}

						if (!isAble) continue;

						result = (a + b) * 2;
					}

				}
			}
		}
	}
}
int main()
{
	freopen("input2.txt", "r", stdin);
	scanf("%d", &tc);

	for (int k = 0; k < tc; k++)
	{
		init();
		memset(map, 0, sizeof(map));

		scanf("%d", &N);
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				scanf("%d", &map[i][j]);
			}
		}

		solve();

		printf("#%d %d\n", k + 1, result);

	}
	return 0;
}
