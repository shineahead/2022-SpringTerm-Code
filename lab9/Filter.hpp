#include<iostream>
#include<numeric>
#include<algorithm>
#include "Mat.hpp"
#ifndef FILTER_HPP
#define FILTER_HPP
using namespace std;

//Filter��

template <class T>
class Filter
{
public:
	Filter()
	{

	}
	Filter(int size) //���캯��
	{
		filterSize = size;
	}
	virtual ~Filter() //��������;
	{
		
	}
	virtual Mat<T> Filtering(const Mat<T> &input) = 0 //�˲����������麯����;
	{

	}

protected:
	int filterSize;
};


//meanFilter��
template <class T>
class MeanFilter : public Filter<T>
{
public:
	MeanFilter()
	{
		this->filterSize = 5;
	}
	MeanFilter(int size)
	{
		this->filterSize = size;
	}
	virtual ~MeanFilter()
	{

	}
	virtual Mat<T> Filtering(const Mat<T> &input) //��ֵ�˲�����
	{
		int Height = input.Height();
		int Width = input.Width();
		int sep = (this->filterSize - 1) / 2;
		Mat<T> temp = input;
		//��ֵ�˲�
		for (int i = 0; i < Height; i++)
		{
			for (int j = 0; j < Width; j++)
			{
				T data = temp.At(i, j), sum = 0;
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
				temp.Set(i, j, sum / (this->filterSize * this->filterSize));
			}
		}
		return temp;
	}
};


//median��
template <class T>
class MedianFilter : public Filter<T>
{
public:
	MedianFilter()
	{
		this->filterSize = 5;
	}
	MedianFilter(int size)
	{
		this->filterSize = size;
	}
	virtual ~MedianFilter()
	{

	}
	virtual Mat<T> Filtering(const Mat<T> &input) // ��ֵ�˲�������
	{
		int Height = input.Height();
		int Width = input.Width();
		int sep = (this->filterSize - 1) / 2;
		T *data = new double[this->filterSize * this->filterSize + 10];
		Mat<T> temp = input;
		//��ֵ�˲�
		for (int i = 0; i < Height; i++)
		{
			for (int j = 0; j < Width; j++)
			{
				int count = 0;
				T da = temp.At(i, j);
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
				sort(data, data + this->filterSize * this->filterSize);
				T value = data[count / 2];
				temp.Set(i, j, value);
			}
		}
		return temp;
	}
};

#endif // !FILTER_HPP