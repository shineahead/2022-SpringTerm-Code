#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<ctime>
using namespace std;

int main()
{
	void Monkey();
	void noodles();
	void perl();
	noodles();
	system("pause");
	return 0;
}

void noodles()		//从高到低的顺序来排序的
{
	int N, a[100], max = 1000, count = 0;
	FILE *fp;
	if ((fp = fopen("array.txt", "r")) == NULL)
	{
		cout << "cannot open the file";
		exit(0);
	}
	fscanf_s(fp, "%d", &N);
	for (int i = 0; i < N; i++)
		fscanf_s(fp, "%d", &a[i]);

	while (count < N)
	{
		max--;
		for (int i = 0; i < N; i++)
			if (a[i] == max)
			{
				count++;
				cout << a[i] << " ";
			}
	}
	return;
}

void perl()
{
	int arr[100][100], N, a[100], max;
	FILE *fp;
	if ((fp = fopen("array.txt", "r")) == NULL)
	{
		cout << "cannot open the file";
		exit(0);
	}
	fscanf_s(fp, "%d", &N);
	for (int i = 0; i < N; i++)
		fscanf_s(fp, "%d", &a[i]);

	for (int i = 0; i < N; i++)		//初始化算盘
	{
		for (int j = 0; j < a[i]; j++)
		{
			arr[i][j] = 1;
		}
	}

	max = a[0];
	for (int i = 0; i < N; i++)		//找出待排序数组中最大的数值
		if (a[i] > max)
			max = a[i];
	for (int i = 0; i < max; i++)	//外层循环表示从第一列走到最后一列,i表示列
	{
		for (int j = 0; j < N; j++)		//选择排序法把算珠掉落
		{
			int k = arr[j][i], temp, flag;
			for (int p = j + 1; p < N; p++)
				if (arr[p][i] < k)
				{
					k = arr[p][i];
					flag = p;
				}
			if (k != arr[j][i])
			{
				temp = arr[j][i];
				arr[j][i] = arr[flag][i];
				arr[flag][i] = temp;
			}
		}
	}

	for (int i = 0; i < N; i++)		//打印排序好的数组
	{
		int count = 0;
		for (int j = 0; j < max; j++)
		{
			if (arr[i][j] == 1)
				count++;
		}
		cout << count << " ";
	}
	return;
}

void Monkey()
{
	int N, a[100], m, n;
	bool flag = true;
	srand((unsigned int)time(0));
	FILE *fp;
	if ((fp = fopen("array.txt", "r")) == NULL)
	{
		cout << "cannot open the file";
		exit(0);
	}
	fscanf_s(fp, "%d", &N);
	for (int i = 0; i < N; i++)
		fscanf_s(fp, "%d", &a[i]);

	while (true)
	{
		int val = 1, temp;	//用来判断数组是否具有正确的排序
		for (int i = 0; i < N; i++)
			if (a[i] > a[i + 1] && i < N - 1)
			{
				flag = false;
				val = 0;
			}
		if (val == 1)
			flag = true;
		if (flag == true)
			break;
		m = rand() % 5;
		n = rand() % 5;
		temp = a[m];
		a[m] = a[n];
		a[n] = temp;
	}
	for (int i = 0; i < N; i++)
		cout << a[i] << " ";
	fclose(fp);
	return;
}

