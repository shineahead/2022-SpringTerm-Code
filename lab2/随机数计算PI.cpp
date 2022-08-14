#include<iostream>
#include<cmath>
#include<iomanip>
#include<cstdlib>
#include<ctime>
using namespace std;
const double E = 0.0001;		//���PI�ľ���
const int N = 30000;		//��ʾ���ɵ�������ĸ���
int main()
{
	double residual = 100, PI = 100, nPI = 0;
	double temp1, temp2;
	int i, r = 10, M = 0, square = 0;	//Բ�İ뾶RΪ10
	srand(time(0));		//�õ�ǰ��ʱ����Ϊ����
	int count = 0;		//count������������˼���
	while (residual > E)
	{
		count++;
		for (i = 0; i < N; i++)
		{
			temp1 = (rand() % 1001) * 0.01;
			temp2 = (rand() % 1001) * 0.01;		//���������������ʾ�õ������
			if (sqrt(pow(temp1, 2) + pow(temp2, 2)) <= r)
				M++;		//����Բ��Ϊ(0,0)�㣬����õ㵽Բ�ĵľ��룬С��R������Բ��
		}
		nPI = 4 * (double(M) / double((N*count)));
		residual = fabs(PI - nPI);
		PI = nPI;
	}
	cout << PI << endl;
	return 0;
}