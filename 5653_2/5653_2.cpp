#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

using namespace std;

// 가능한 배열의 최대 크기 50 + 300
#define MAXL 352

struct data_type
{
	// 0 : 빈 공간, 1 : 비활성 상태, 2 : 활성 상태, 3 : 죽은 상태
	int Status;
	int LP, HP;
};

int T, N, M, K;
data_type Map[2][MAXL][MAXL];

//상, 하, 우, 좌 (y,x)
int dir[4][2] = { {0,-1},{0,1}, {1,0}, {-1,0} };

int main() {

	freopen("input.txt", "r", stdin);
	setbuf(stdout, NULL);
	cin >> T;

	for (int tc = 1; tc <= T; tc++)
	{
		cin >> N >> M >> K;
		//init
		for (int i = 0; i < N+K+2; i++)
		{
			for (int j = 0; j < M+K+2; j++)
			{
				Map[0][i][j].Status = 0;
				Map[1][i][j].Status = 0;
			}
		}
		//초기 줄기 세포의 LP
		for (int i = 0 + K/2 +1; i < N+K/2+1; i++)
		{
			for (int j = 0+K/2+1; j < M+K/2+1; j++)
			{
				cin >> Map[0][i][j].LP;
				if (Map[0][i][j].LP > 0) {
					Map[0][i][j].Status = 1;
					Map[0][i][j].HP = 0;
				}
			}
		}

		//줄기 세포가 K시간 내에 분포될 수 있는 최대 범위
		N = N + K + 2;
		M = M + K + 2;

		int curMap = 0;
		for (int k = 0; k < K; k++)
		{
			for (int i = 0; i < N; i++)
			{
				for (int j = 0; j < M; j++)
				{
					//죽은 세포일 경우
					if (Map[curMap][i][j].Status == 3) {
						//아무 동작도 하지 않음
						Map[1 - curMap][i][j].Status = Map[curMap][i][j].Status;
						continue;
					}
					//비활성화 상태일 경우
					else if (Map[curMap][i][j].Status == 1) {
						Map[1 - curMap][i][j].HP = Map[curMap][i][j].HP + 1;
						Map[1 - curMap][i][j].LP = Map[curMap][i][j].LP;
						//비활성화 상태로 LP만큼 시간이 지난 경우
						if (Map[1 - curMap][i][j].HP == Map[1 - curMap][i][j].LP)
							Map[1 - curMap][i][j].Status = 2;
						else {
							Map[1 - curMap][i][j].Status = 1;
						}
					}
					//활성화 상태일 경우
					else if (Map[curMap][i][j].Status == 2) {
						//확장
						if (Map[curMap][i][j].HP == Map[curMap][i][j].LP) {
							for (int d = 0; d < 4; d++)
							{
								int i2 = i + dir[d][0];
								int j2 = j + dir[d][1];

								//하나의 줄기 세포가 번식하려고 하는 경우
								if (Map[curMap][i2][j2].Status == 0) {
									if (Map[1 - curMap][i2][j2].Status == 0) {
										Map[1 - curMap][i2][j2].Status = 1;
										Map[1 - curMap][i2][j2].LP = Map[curMap][i][j].LP;
										Map[1 - curMap][i2][j2].HP = 0;
									}
								}
								//두 개 이상의 줄기 세포가 번식하려고 하는 경우
								else if (Map[1 - curMap][i2][j2].Status == 1 && Map[1 - curMap][i2][j2].LP < Map[curMap][i][j].LP) {
									Map[1 - curMap][i2][j2].LP = Map[curMap][i][j].LP;
								}
							}

						}


						Map[1 - curMap][i][j].HP = Map[curMap][i][j].HP - 1;
						if (Map[1 - curMap][i][j].HP == 0) {
							Map[1 - curMap][i][j].Status = 3;
						}
						else {
							Map[1 - curMap][i][j].Status = 2;
						}
					}
					
				}
			}

			curMap = 1 - curMap;
		}


		int Answer = 0;
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < M; j++)
			{
				if (Map[curMap][i][j].Status == 1 || Map[curMap][i][j].Status == 2) {
					Answer++;
				}
			}
		}
		
		cout << "#" << tc << ' ' << Answer << endl;

	}
	return 0;
}