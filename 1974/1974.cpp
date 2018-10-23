#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>


int sdoku[9][9];
int visited[10];
int dx[9] = { -1, 0, 1, -1, 0, 1, -1, 0, 1 };
int dy[9] = { -1, -1, -1, 0, 0, 0, 1, 1, 1 };

int checkAllNum(int i, int j);

int main() {

	int tc = 0;	
	freopen("input.txt", "r", stdin);

	scanf("%d", &tc);

	for (int k = 0; k < tc; k++)
	{
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				scanf("%d", &sdoku[i][j]);
			}
		}

		
		int flag = false;
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				memset(visited, 0, sizeof(visited));
				if (checkAllNum(i, j) == 1)
				{
					continue;
				}
				else
				{
					flag = true;
					break;
				}
			}
		}

		if (flag == true)
		{
			printf("#%d %d\n", k+1, 0);
		}
		else 
		{
			printf("#%d %d\n", k+1, 1);
		}
		
		memset(sdoku, 0, sizeof(sdoku));
	}
	

	return 0;
}

int checkAllNum(int i, int j)
{

	for (int k = 0; k < 9; k++)
	{
		visited[sdoku[i][k]]++;
		visited[sdoku[k][j]]++;
	}

	if ((0 <= i && i <= 2)) {
		if (0 <= j && j <= 2) {
			for (int k = 0; k <= 8; k++) {
				int nX = 1 + dx[k];
				int nY = 1 + dy[k];
				visited[sdoku[nX][nY]]++;
			}
		}
		else if (3 <= j && j <= 5) {
			for (int k = 0; k <= 8; k++) {
				int nX = 1 + dx[k];
				int nY = 4 + dy[k];
				visited[sdoku[nX][nY]]++;
			}
		}
		else if (6 <= j && j <= 8) {
			for (int k = 0; k <= 8; k++) {
				int nX = 1 + dx[k];
				int nY = 7 + dy[k];
				visited[sdoku[nX][nY]]++;
			}
		}
	}
	else if (3 <= i && i <= 5)
	{
		if (0 <= j && j <= 2) {
			for (int k = 0; k <= 8; k++) {
				int nX = 4 + dx[k];
				int nY = 1 + dy[k];
				visited[sdoku[nX][nY]]++;
			}
		}
		else if (3 <= j && j <= 5) {
			for (int k = 0; k <= 8; k++) {
				int nX = 4 + dx[k];
				int nY = 4 + dy[k];
				visited[sdoku[nX][nY]]++;
			}
		}
		else if (6 <= j && j <= 8) {
			for (int k = 0; k <= 8; k++) {
				int nX = 4 + dx[k];
				int nY = 7 + dy[k];
				visited[sdoku[nX][nY]]++;
			}
		}
	}
	else
	{
		if (0 <= j && j <= 2) {
			for (int k = 0; k <= 8; k++) {
				int nX = 7 + dx[k];
				int nY = 1 + dy[k];
				visited[sdoku[nX][nY]]++;
			}
		}
		else if (3 <= j && j <= 5) {
			for (int k = 0; k <= 8; k++) {
				int nX = 7 + dx[k];
				int nY = 4 + dy[k];
				visited[sdoku[nX][nY]]++;
			}
		}
		else if (6 <= j && j <= 8) {
			for (int k = 0; k <= 8; k++) {
				int nX = 7 + dx[k];
				int nY = 7 + dy[k];
				visited[sdoku[nX][nY]]++;
			}
		}
	}

	for (int k = 1; k <= 9; k++)
	{
		if (visited[k] != 3)
		{
			return 0;
		}
	}

	return 1;

}