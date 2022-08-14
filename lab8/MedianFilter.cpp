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
	std::cout << "MedianFilter����������" << std::endl;
}

Matrix MedianFilter::Filtering(const Matrix &input)
{
	int Height = input.Height();
	int Width = input.Width();
	int sep = (filterSize - 1) / 2;
	double *data = new double[filterSize * filterSize + 10];
	Matrix temp = input;
	//��ֵ�˲�
	for (int i = 0; i < Height; i++)
	{
		for (int j = 0; j < Width; j++)
		{
			int count = 0;
			double da = temp.At(i, j);
			data[count++] = da;
			int up, down, left, right;
			//���ĸ�ֵ��ʾҪ�ӵ�ǰ���ص������������ĸ���λ��չ�����ظ���
			up = down = left = right = sep;
			//��ʾ������չʱ�����˾���Ķ���
			if (i - up < 0)
			{
				up = i;
				down += up - i;//������չʱ����������ֱ�Ӽӵ����������չ
			}
			//��ʾ������չʱ�����˾���ĵײ�
			else if (i + down >= Height)
			{
				down = Height - i - 1;
				up += i + down - Height;//������չʱ����������ֱ�Ӽӵ����������չ
			}
			//��ʾ������չʱ�����˾������
			if (j - left < 0)
			{
				left = j;
				right += left - j;//�����չʱ����������ֱ�Ӽӵ��ұ߽�����չ
			}
			//��ʾ������չʱ�����˾�����Ҳ�
			else if (j + right >= Width)
			{
				right = Width - j - 1;//�ұ���չʱ����������ֱ�Ӽӵ���߽�����չ
				left += j + right - Width;
			}
			//��ʼ������չ
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
				//��Ԫ��û�б�����
				data[count++] = temp.At(i - m, j);
			}
			//��ʼ������չ
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
				//��Ԫ��û�б�����
				data[count++] = temp.At(i + m, j);
			}
			//��ʼ������չ
			for (int n = 1; n <= left; n++)
			{
				data[count++] = temp.At(i, j - n);
			}
			//��ʼ������չ
			for (int n = 1; n <= right; n++)
			{
				data[count++] = temp.At(i, j + n);
			}
			//��data�������������
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
//������
int MedianFilter::cmp(double a, double b)
{
	return a < b;
}