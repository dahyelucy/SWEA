#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

using namespace std;

// ������ �迭�� �ִ� ũ�� 50 + 300
#define MAXL 352

struct data_type
{
	// 0 : �� ����, 1 : ��Ȱ�� ����, 2 : Ȱ�� ����, 3 : ���� ����
	int Status;
	int LP, HP;
};

int T, N, M, K;
data_type Map[2][MAXL][MAXL];

//��, ��, ��, �� (y,x)
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
		//�ʱ� �ٱ� ������ LP
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

		//�ٱ� ������ K�ð� ���� ������ �� �ִ� �ִ� ����
		N = N + K + 2;
		M = M + K + 2;

		int curMap = 0;
		for (int k = 0; k < K; k++)
		{
			for (int i = 0; i < N; i++)
			{
				for (int j = 0; j < M; j++)
				{
					//���� ������ ���
					if (Map[curMap][i][j].Status == 3) {
						//�ƹ� ���۵� ���� ����
						Map[1 - curMap][i][j].Status = Map[curMap][i][j].Status;
						continue;
					}
					//��Ȱ��ȭ ������ ���
					else if (Map[curMap][i][j].Status == 1) {
						Map[1 - curMap][i][j].HP = Map[curMap][i][j].HP + 1;
						Map[1 - curMap][i][j].LP = Map[curMap][i][j].LP;
						//��Ȱ��ȭ ���·� LP��ŭ �ð��� ���� ���
						if (Map[1 - curMap][i][j].HP == Map[1 - curMap][i][j].LP)
							Map[1 - curMap][i][j].Status = 2;
						else {
							Map[1 - curMap][i][j].Status = 1;
						}
					}
					//Ȱ��ȭ ������ ���
					else if (Map[curMap][i][j].Status == 2) {
						//Ȯ��
						if (Map[curMap][i][j].HP == Map[curMap][i][j].LP) {
							for (int d = 0; d < 4; d++)
							{
								int i2 = i + dir[d][0];
								int j2 = j + dir[d][1];

								//�ϳ��� �ٱ� ������ �����Ϸ��� �ϴ� ���
								if (Map[curMap][i2][j2].Status == 0) {
									if (Map[1 - curMap][i2][j2].Status == 0) {
										Map[1 - curMap][i2][j2].Status = 1;
										Map[1 - curMap][i2][j2].LP = Map[curMap][i][j].LP;
										Map[1 - curMap][i2][j2].HP = 0;
									}
								}
								//�� �� �̻��� �ٱ� ������ �����Ϸ��� �ϴ� ���
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