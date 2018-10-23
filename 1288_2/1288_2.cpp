#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string>

using namespace std;

int visitNum[10];

void init()
{
	for (int i = 0; i < 10; i++)
	{
		visitNum[i] = 0;
	}
}
int main()
{
	int tc = 0;
	freopen("input.txt", "r", stdin);
	scanf("%d", &tc);

	for (int k = 0; k < tc; k++)
	{
		init();
		unsigned int N = 0;
		unsigned int N2 = 0;
		scanf("%u", &N);

		N2 = N;
		bool flag = true;

		while (true)
		{
			string tempN = to_string(N2);
			int tempNLen = tempN.size();
			for (int i = 0; i < tempNLen; i++)
			{
				int t = tempN.at(i) - '0';
				if (visitNum[t] == 0) {
					visitNum[t] = 1;
				}
			}

			N2 += N;

			for (int j = 0; j < 10; j++)
			{
				if (visitNum[j] == 1) {
					flag = false;
					continue;
				}
				else
				{
					flag = true;
					break;
				}
			}

			if (flag == false) {
				break;
			}
		}
		printf("#%d %d\n", k + 1, N2-N);

	}

	return 0;
}