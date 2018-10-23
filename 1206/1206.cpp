#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

int main() {
	int test_case = 10;
	int buildings[1000];
	int dx[4] = { -2, -1, 1, 2 };

	freopen("input.txt", "r", stdin);

	for (int tc = 1; tc <= test_case; tc++)
	{
		int building_num = 0;
		int see_possible = 0;
		scanf("%d", &building_num);

		for (int i = 0; i < building_num; i++)
		{
			scanf("%d", &buildings[i]);
		}

		for (int i = 0; i < building_num; i++)
		{
			if (i == 0 || i == 1 || i == building_num - 1 || i == building_num - 2) {
				continue;
			}

			int cur_building = buildings[i];
			

			if (buildings[i - 1] < cur_building && buildings[i - 2] < cur_building
				&& buildings[i + 1] < cur_building && buildings[i + 2] < cur_building)
			{
				int Max_floor = -1;

				for (int j = 0; j < 4; j++)
				{
					if (buildings[i - dx[j]] > Max_floor)
					{
						Max_floor = buildings[i - dx[j]];
					}
				}
				see_possible += (cur_building - Max_floor);
			}
			else {
				continue;
			}

			
		}

		printf("#%d %d\n", tc, see_possible);

		memset(buildings,-1,sizeof(buildings));

	}

	return 0;
} 