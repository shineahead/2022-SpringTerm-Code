#include<iostream>
using namespace std;
const int UP = 6;
const int DOWN = 4;
const int STAY = 5;

int main(int argc, int argv[])
{
	int a[101], i, n, diff, time = 0;//a用来储存层数，diff是时间差
	int head, tail;		//head和tail用来计算两哥楼层之间的时间
	head = 0, tail = 1;
	cin >> n;
	a[0] = 0;
	for (i = 1; i <= 100; i++)
		a[i] = -1;
	for (i = 1; i <= n; i++)
		cin >> a[i];
	while (a[tail] != -1)
	{
		if (a[tail] > a[head])
		{
			diff = a[tail] - a[head];
			time += UP * diff + STAY;
		}
		else
		{
			diff = a[head] - a[tail];
			time += DOWN * diff + STAY;
		}
		head++;
		tail++;
	}
	cout << time;
	return 0;
}