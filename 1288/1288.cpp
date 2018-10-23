#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
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
	freopen("input2.txt", "r", stdin);
	scanf("%d", &tc);

	for (int k = 0; k < tc; k++)
	{
		init();
		unsigned int N = 0;
		scanf("%u", &N);
		
		
		bool flag = true;

		while(true)
		{
			string tempN = to_string(N);
			int tempNLen = tempN.size();
			for (int i = 0; i < tempNLen; i++)
			{
				if (visitNum[tempN.at(i)] == 0) {
					visitNum[tempN.at(i)] = 1;
				}
			}
			
			N += N;

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
		printf("#%d %d\n", k+1, N);

	}

	return 0;
}