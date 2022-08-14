#include<iostream>
#include"Image.h"
#include"Matrix.h"
#include<string>
#include"Filter.h"
#include"MeanFilter.h"
#include"MedianFilter.h"
using namespace std;


int main()
{
	Image img("Lena_gaussian.bmp");

	int num;
	string str;
	cout << "请输入Mean或者Median来选择滤波器的类型：" << endl;
	cin >> str;

	if (str[2] == 'a')
	{
		cout << "请输入想要的滤波器规格:(默认:5)" << endl;
		cin >> num;
		Filter *filter = NULL;
		filter = new MeanFilter(num);
		Image result_mean, result_mean2;
		result_mean = filter->Filtering(img);
		result_mean.Info(img);
		result_mean.Writebmp("Mean.bmp");

		delete filter;
	}
	else
	{
		cout << "请输入想要的滤波器规格:(默认:5)" << endl;
		cin >> num;
		Filter *filter = NULL;
		filter = new MedianFilter(num);
		Image result_median, result_median2;
		result_median = filter->Filtering(img);
		result_median.Info(img);
		result_median.Writebmp("Median.bmp");

		delete filter;
	}
	
	cout << "文件处理成功" << endl;
	system("pause");
	return 0;
}