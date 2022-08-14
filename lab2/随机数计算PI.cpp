#include<iostream>
#include<cmath>
#include<iomanip>
#include<cstdlib>
#include<ctime>
using namespace std;
const double E = 0.0001;		//求解PI的精度
const int N = 30000;		//表示生成的随机数的个数
int main()
{
	double residual = 100, PI = 100, nPI = 0;
	double temp1, temp2;
	int i, r = 10, M = 0, square = 0;	//圆的半径R为10
	srand(time(0));		//用当前的时间作为种子
	int count = 0;		//count用来计算进行了几轮
	while (residual > E)
	{
		count++;
		for (i = 0; i < N; i++)
		{
			temp1 = (rand() % 1001) * 0.01;
			temp2 = (rand() % 1001) * 0.01;		//用两个随机数来表示该点的坐标
			if (sqrt(pow(temp1, 2) + pow(temp2, 2)) <= r)
				M++;		//假设圆心为(0,0)点，计算该点到圆心的距离，小于R便落在圆内
		}
		nPI = 4 * (double(M) / double((N*count)));
		residual = fabs(PI - nPI);
		PI = nPI;
	}
	cout << PI << endl;
	return 0;
}