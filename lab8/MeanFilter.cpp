#include<iostream>
#include  "MeanFilter.h"

MeanFilter::MeanFilter(int size)
{
	filterSize = size;
}

MeanFilter::~MeanFilter()
{
	std::cout << "MeanFilter����������" << std::endl;
}

Matrix MeanFilter::Filtering(const Matrix &input)
{
	int Height = input.Height();
	int Width = input.Width();
	int sep = (filterSize - 1) / 2;
	Matrix temp = input;
	//��ֵ�˲�
	for (int i = 0; i < Height; i++)
	{
		for (int j = 0; j < Width; j++)
		{
			double data = temp.At(i, j), sum = 0;
			sum += data;
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
					sum += temp.At(i - m, j - n);
				}
				for (int n = 1; n <= right; n++)
				{
					sum += temp.At(i - m, j + n);
				}
				//��Ԫ��û�б�����
				sum += temp.At(i - m, j);
			}
			//��ʼ������չ
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
				//��Ԫ��û�б�����
				sum += temp.At(i + m, j);
			}
			//��ʼ������չ
			for (int n = 1; n <= left; n++)
			{
				sum += temp.At(i, j - n);
			}
			//��ʼ������չ
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
