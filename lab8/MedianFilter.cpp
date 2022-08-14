#include<numeric>
#include<iostream>
#include<algorithm>
#include "MedianFilter.h"
using namespace std;

MedianFilter::MedianFilter(int size)
{
	filterSize = size;
}

MedianFilter::~MedianFilter()
{
	std::cout << "MedianFilter的析构函数" << std::endl;
}

Matrix MedianFilter::Filtering(const Matrix &input)
{
	int Height = input.Height();
	int Width = input.Width();
	int sep = (filterSize - 1) / 2;
	double *data = new double[filterSize * filterSize + 10];
	Matrix temp = input;
	//均值滤波
	for (int i = 0; i < Height; i++)
	{
		for (int j = 0; j < Width; j++)
		{
			int count = 0;
			double da = temp.At(i, j);
			data[count++] = da;
			int up, down, left, right;
			//用四个值表示要从当前像素点向上下左右四个方位扩展的像素个数
			up = down = left = right = sep;
			//表示向上扩展时超出了矩阵的顶部
			if (i - up < 0)
			{
				up = i;
				down += up - i;//上面扩展时超出的行数直接加到下面进行扩展
			}
			//表示向上扩展时超出了矩阵的底部
			else if (i + down >= Height)
			{
				down = Height - i - 1;
				up += i + down - Height;//下面扩展时超出的行数直接加到上面进行扩展
			}
			//表示向上扩展时超出了矩阵的左部
			if (j - left < 0)
			{
				left = j;
				right += left - j;//左边扩展时超出的行数直接加到右边进行扩展
			}
			//表示向上扩展时超出了矩阵的右部
			else if (j + right >= Width)
			{
				right = Width - j - 1;//右边扩展时超出的行数直接加到左边进行扩展
				left += j + right - Width;
			}
			//开始向上扩展
			for (int m = 1; m <= up; m++)
			{
				for (int n = 1; n <= left; n++)
				{
					data[count++] = temp.At(i - m, j - n);
				}
				for (int n = 1; n <= right; n++)
				{
					data[count++] = temp.At(i - m, j + n);
				}
				//该元素没有被遍历
				data[count++] = temp.At(i - m, j);
			}
			//开始向下扩展
			for (int m = 1; m <= down; m++)
			{
				for (int n = 1; n <= left; n++)
				{
					data[count++] = temp.At(i + m, j - n);
				}
				for (int n = 1; n <= right; n++)
				{
					data[count++] = temp.At(i + m, j + n);
				}
				//该元素没有被遍历
				data[count++] = temp.At(i + m, j);
			}
			//开始向左扩展
			for (int n = 1; n <= left; n++)
			{
				data[count++] = temp.At(i, j - n);
			}
			//开始向右扩展
			for (int n = 1; n <= right; n++)
			{
				data[count++] = temp.At(i, j + n);
			}
			//对data数组进行排序处理
			sort(data, data + filterSize * filterSize);
			double value = data[count / 2];
			temp.Set(i, j, value);
		}
	}
	return temp;
}

void MedianFilter::Resize(int new_size)
{
	filterSize = new_size;
}
//排序函数
int MedianFilter::cmp(double a, double b)
{
	return a < b;
}