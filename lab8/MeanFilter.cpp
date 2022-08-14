#include<iostream>
#include  "MeanFilter.h"

MeanFilter::MeanFilter(int size)
{
	filterSize = size;
}

MeanFilter::~MeanFilter()
{
	std::cout << "MeanFilter的析构函数" << std::endl;
}

Matrix MeanFilter::Filtering(const Matrix &input)
{
	int Height = input.Height();
	int Width = input.Width();
	int sep = (filterSize - 1) / 2;
	Matrix temp = input;
	//均值滤波
	for (int i = 0; i < Height; i++)
	{
		for (int j = 0; j < Width; j++)
		{
			double data = temp.At(i, j), sum = 0;
			sum += data;
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
					sum += temp.At(i - m, j - n);
				}
				for (int n = 1; n <= right; n++)
				{
					sum += temp.At(i - m, j + n);
				}
				//该元素没有被遍历
				sum += temp.At(i - m, j);
			}
			//开始向下扩展
			for (int m = 1; m <= down; m++)
			{
				for (int n = 1; n <= left; n++)
				{
					sum += temp.At(i + m, j - n);
				}
				for (int n = 1; n <= right; n++)
				{
					sum += temp.At(i + m, j + n);
				}
				//该元素没有被遍历
				sum += temp.At(i + m, j);
			}
			//开始向左扩展
			for (int n = 1; n <= left; n++)
			{
				sum += temp.At(i, j - n);
			}
			//开始向右扩展
			for (int n = 1; n <= right; n++)
			{
				sum += temp.At(i, j + n);
			}
			temp.Set(i, j, sum / (filterSize * filterSize));
		}
	}
	return temp;
}

void MeanFilter::Resize(int new_size)
{
	filterSize = new_size;
}
