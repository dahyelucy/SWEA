#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>
#include <string>

using namespace std;


int arr[8][8];
int tempArr[8][8];
int tempArr2[8][8];
int tempArr3[8][8];

string result[8][3];

void init()
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			arr[i][j] = 0;
			tempArr[i][j] = 0;
			tempArr2[i][j] = 0;
			tempArr3[i][j] = 0;
		}
	}

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			result[i][j] = "";
		}
	}
}
int main()
{
	int t;
	freopen("input.txt", "r", stdin);
	scanf("%d", &t);

	for (int k = 0; k < t; k++)
	{
		init();
		int N;
		scanf("%d", &N);
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				scanf("%d", &arr[i][j]);
			}
		}


		//90µµ È¸Àü
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				tempArr[i][j] = arr[N - j - 1][i];
			}
		}

		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				tempArr2[i][j] = tempArr[N - j - 1][i];
			}
		}

		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				tempArr3[i][j] = tempArr2[N - j - 1][i];
			}
		}


		for (int i = 0; i < N; i++)
		{
			string temp1 = "";
			string temp2 = "";
			string temp3 = "";
			for (int j = 0; j < N; j++)
			{
				
				temp1 += to_string(tempArr[i][j]);
				temp2 += to_string(tempArr2[i][j]);
				temp3 += to_string(tempArr3[i][j]);
			}
			result[i][0] = temp1;
			result[i][1] = temp2;
			result[i][2] = temp3;
		}
		printf("%d", stoi(to_string(0)));

		printf("#%d\n", k + 1);
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				cout << result[i][j] + " ";
			}
			printf("\n");
		}
	}

	return 0;

}