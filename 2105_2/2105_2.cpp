#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

int N;
int map[20][20];
int visited[101];
int result;


void initVisited()
{
	result = -1;
	for (int x = 0; x < 101; x++)
	{
		visited[x] = 0;
	}
}
		
int main() {

	freopen("input2.txt", "r", stdin);
	int tc = 0;
	scanf("%d", &tc);

	for (int k = 0; k < tc; k++)
	{
		initVisited();
		memset(map, 0, sizeof(map));
		scanf("%d", &N);

		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				scanf("%d", &map[i][j]);
			}
		}

		
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				for (int a = 1; a < N; a++)
				{
					for (int b = 1; b < N; b++)
					{
						if (j-b >= 0 && j+a < N && i+a+b <N) {
							if ( (a + b) * 2 > result) {
								initVisited();
								bool isVisited = false;

								int iDir = i;
								int jDir = j;

								for (int w = 0; w < a; w++)
								{

									iDir++;
									jDir++;
									if (visited[map[iDir][jDir]] == 0) {
										visited[map[iDir][jDir]] = 1;
									}
									else {
										isVisited = true;
										break;
									}
								}

								if (isVisited)
									continue;

								for (int w = 0; w < b; w++)
								{
									iDir++;
									jDir--;
									if (visited[map[iDir][jDir]] == 0) {
										visited[map[iDir][jDir]] = 1;
									}
									else {
										isVisited = true;
										break;
									}
									
								}

								if (isVisited)
									continue;

								for (int w = 0; w < a; w++)
								{
									iDir--;
									jDir--;
									if (visited[map[iDir][jDir]] == 0) {
										visited[map[iDir][jDir]] = 1;
									}
									else {
										isVisited = true;
										break;
									}
									
								}

								if (isVisited)
									continue;

								for (int w = 0; w < b; w++)
								{
									iDir--;
									jDir++;
									if (visited[map[iDir][jDir]] == 0) {
										visited[map[iDir][jDir]] = 1;
									}
									else {
										isVisited = true;
										break;
									}
								}

								if (isVisited)
									continue;

								result = (a + b) * 2;
							}
						}
					}
				}
			}
		}

		printf("#%d %d\n", k + 1, result);
		

	}

	


	return 0;
}