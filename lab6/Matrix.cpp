#include<iostream>
#include<cstdlib>
#include<ctime>
#include"image.h"
#include<Windows.h>
using namespace std;

Matrix::Matrix()
{
	height = 0;
	width = 0;
	data = nullptr;
}
Matrix::Matrix(int h, int w)
{
	height = h;
	width = w;
	data = new double*[h];
	for (int i = 0; i < h; i++)
		data[i] = new double[w];
}
Matrix::Matrix(int h, int w, double val)
{
	height = h;
	width = w;
	data = new double*[h];
	for (int i = 0; i < h; i++)
	{
		data[i] = new double[w];
		for (int j = 0; j < w; j++)
			data[i][j] = val;
	}
}
//复制构造函数
Matrix::Matrix(const Matrix &m)
{
	height = m.height;
	width = m.width;
	data = new double*[height];
	for (int i = 0; i < height; i++)
	{
		data[i] = new double[width];
		for (int j = 0; j < width; j++)
			data[i][j] = m.data[i][j];
	}
}
Matrix::~Matrix()
{
	for (int i = 0; i < height; i++)
		delete[]data[i];
	delete[]data;
}
//从文本文件中读入矩阵数据
void Matrix::ReadText(const char filename[])
{
	FILE *fp;
	fopen_s(&fp, filename, "rb");
	fread(&height, sizeof(int), 1, fp);
	fread(&width, sizeof(int), 1, fp);

	for (int i = 0; i < height; i++)
		fread(data[i], sizeof(double) * width, 1, fp);
}
//将矩阵数据保存为文本文件
void Matrix::WriteText(const char filename[])
{
	FILE *fp;
	fopen_s(&fp, filename, "wb");
	fwrite(&height, sizeof(int), 1, fp);
	fwrite(&height, sizeof(int), 1, fp);

	for (int i = 0; i < height; i++)
		fwrite(data[i], sizeof(double) * width, 1, fp);
}
void Matrix::Zeros(int h, int w)
{
	height = h;
	width = w;
	data = new double*[height];
	for (int i = 0; i < height; i++)
	{
		data[i] = new double[width];
		for (int j = 0; j < width; j++)
			data[i][j] = 0;
	}
}
void Matrix::Ones(int h, int w)
{
	height = h;
	width = w;
	data = new double*[height];
	for (int i = 0; i < height; i++)
	{
		data[i] = new double[width];
		for (int j = 0; j < width; j++)
			data[i][j] = 1;
	}
}
void Matrix::Random(int h, int w)
{
	srand(time(0));
	height = h;
	width = w;
	data = new double*[height];
	for (int i = 0; i < height; i++)
	{
		data[i] = new double[width];
		for (int j = 0; j < width; j++)
		{
			double temp;
			temp = (rand() % 1000) * 0.01;
			data[i][j] = temp;
		}
	}
}
void Matrix::Identity(int n)
{
	height = n;
	width = n;
	data = nullptr;
}
int Matrix::Height() const
{
	return height;
}
int Matrix::Width() const
{
	return width;
}
Matrix Matrix::MajorDiagonal()
{
	double **temp = new double*[height];
	for (int i = 0; i < height; i++)
		temp[i] = new double[1];
	int N = 0;
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			if (i == j)
				temp[N++][0] = data[i][j];
	unsigned char**temp_u = new unsigned char*[height];
	for (int i = 0; i < height; i++)
		temp_u[i] = new unsigned char[1];
	for (int i = 0; i < height; i++)
		temp_u[i][0] = static_cast<unsigned char>(temp[i][0]);
	Image m(temp_u, height, 1);
	return m;
}
Matrix Matrix::MinoDiagonal()
{
	double **temp = new double*[height];
	for (int i = 0; i < height; i++)
		temp[i] = new double[1];
	int N = 0;
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			if (i + j == height - 1)
				temp[N++][0] = data[i][j];
	unsigned char**temp_u = new unsigned char*[height];
	for (int i = 0; i < height; i++)
		temp_u[i] = new unsigned char[1];
	for (int i = 0; i < height; i++)
		temp_u[i][0] = static_cast<unsigned char>(temp[i][0]);
	Image m(temp_u, height, width);
	return m;
}
Matrix Matrix::Column(int n)
{
	double **temp = new double*[height];
	for (int i = 0; i < height; i++)
		temp[i] = new double[1];
	int N = 0;
	for (int i = 0; i < height; i++)
		temp[N++][0] = data[i][n - 1];
	unsigned char**temp_u = new unsigned char*[height];
	for (int i = 0; i < height; i++)
		temp_u[i] = new unsigned char[1];
	for (int i = 0; i < height; i++)
		temp_u[i][0] = static_cast<unsigned char>(temp[i][0]);
	Image m(temp_u, height, width);
	return m;
}
void Matrix::Transpose()
{
	int temp_h, temp_w;
	temp_h = width;
	temp_w = height;
	double **temp_data = new double*[temp_h];
	for (int i = 0; i < temp_h; i++)
		temp_data[i] = new double[temp_w];
	for (int i = 0, p = 0; i < height; i++, p++)
		for (int j = 0, q = 0; j < width; j++, q++)
			temp_data[q][p] = data[i][j];

	for (int i = 0; i < height; i++)
		delete[]data[i];
	delete[]data;

	height = temp_h;
	width = temp_w;
	data = new double*[height];
	for (int i = 0; i < height; i++)
		data[i] = new double[width];

	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			data[i][j] = temp_data[i][j];
	//释放该临时矩阵
	for (int i = 0; i < height; i++)
		delete[]temp_data[i];
	delete[]temp_data;
}
double& Matrix::At(int row, int col)
{
	return data[row][col];
}
void Matrix::Set(int row, int col, double value)
{
	data[row][col] = value;
}
void Matrix::Set(double value)
{
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			data[i][j] = value;

}
void Matrix::Normalize()
{
	double max = 0, min = 0;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (data[i][j] >= max)
				max = data[i][j];
			if (data[i][j] <= min)
				min = data[i][j];
		}
	}

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (data[i][j] == min)
				data[i][j] = 0;
			else if (data[i][j] == max)
				data[i][j] = 1;
			else
				data[i][j] = (data[i][j] - min) / max;
		}
	}
}
void Matrix::Reshape(int h, int w)
{
	int temp_h, temp_w;
	temp_h = h;
	temp_w = w;
	double **temp_data = new double*[temp_h];
	for (int i = 0; i < temp_h; i++)
		temp_data[i] = new double[temp_w];
	int p = 0, q = 0;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (q == temp_w)
			{
				p++;
				q = 0;
			}
			temp_data[p][q] = data[i][j];
			q++;
		}
	}
	for (int i = 0; i < height; i++)
		delete[]data[i];
	delete[]data;

	height = temp_h;
	width = temp_w;
	data = new double*[height];
	for (int i = 0; i < height; i++)
		data[i] = new double[width];

	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			data[i][j] = temp_data[i][j];
	//释放该临时矩阵
	for (int i = 0; i < height; i++)
		delete[]temp_data[i];
	delete[]temp_data;
}
bool Matrix::IsEmpty()
{
	bool flag = false;
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			if (data[i][j] != 0)
			{
				flag = true;
				break;
			}
	return flag;
}
bool Matrix::IsSquare()
{
	return (height == width);

}
void Matrix::CopyTo(Matrix &m)
{
	if (m.data != nullptr)
	{
		for (int i = 0; i < m.height; i++)
			delete[]m.data[i];
		delete[]m.data;

		m.height = height;
		m.width = width;
		m.data = new double*[height];
		for (int i = 0; i < height; i++)
			m.data[i] = new double[width];
	}
	else
	{
		m.height = height;
		m.width = width;
		m.data = new double*[height];
		for (int i = 0; i < height; i++)
			m.data[i] = new double[width];
	}

	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			m.data[i][j] = data[i][j];
}
void Matrix::Mult(double s)
{
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			data[i][j] *= s;

}
void Matrix::Cat(Matrix &m, int code)
{
	int temp_h, temp_w;
	temp_h = height;
	temp_w = width;
	double **temp_data = new double*[temp_h];
	for (int i = 0; i < temp_h; i++)
		temp_data[i] = new double[temp_w];
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			temp_data[i][j] = data[i][j];

	for (int i = 0; i < height; i++)
		delete[]data[i];
	delete[]data;

	if (code == 1)
	{
		width += m.width;
		data = new double*[height];
		for (int i = 0; i < height; i++)
			data[i] = new double[width];
		for (int i = 0; i < temp_h; i++)
			for (int j = 0; j < temp_w; j++)
				data[i][j] = temp_data[i][j];

		for (int i = 0; i < height; i++)
			for (int j = 0; j < m.width; j++)
				data[i][j + m.width] = m.data[i][j];
	}
	else if (code == 2)
	{
		height += m.height;
		data = new double*[height];
		for (int i = 0; i < height; i++)
			data[i] = new double[width];
		for (int i = 0; i < temp_h; i++)
			for (int j = 0; j < temp_w; j++)
				data[i][j] = temp_data[i][j];

		for (int i = 0; i < m.height; i++)
			for (int j = 0; j < m.width; j++)
				data[i + m.height][j] = m.data[i][j];
	}
	else if (code == 3)
	{
		width += m.width;
		data = new double*[height];
		for (int i = 0; i < height; i++)
			data[i] = new double[width];
		for (int i = 0; i < temp_h; i++)
			for (int j = 0; j < temp_w; j++)
				data[i][j + m.width] = temp_data[i][j];

		for (int i = 0; i < m.height; i++)
			for (int j = 0; j < m.width; j++)
				data[i][j] = m.data[i][j];
	}
	else if (code == 4)
	{
		height += m.height;
		data = new double*[height];
		for (int i = 0; i < height; i++)
			data[i] = new double[width];
		for (int i = 0; i < temp_h; i++)
			for (int j = 0; j < temp_w; j++)
				data[i + m.height][j] = temp_data[i][j];

		for (int i = 0; i < m.height; i++)
			for (int j = 0; j < m.width; j++)
				data[i][j] = m.data[i][j];
	}
	else
		cout << "wrong code!" << endl;
}
Matrix Add(const Matrix &m1, const Matrix &m2)
{
	Image temp;
	temp.height = m1.height;
	temp.width = m1.width;
	temp.data = new double*[m1.height];
	for (int i = 0; i < m1.height; i++)
		temp.data[i] = new double[m1.width];
	for (int i = 0; i < m1.height; i++)
		for (int j = 0; j < m1.width; j++)
			temp.data[i][j] = m1.data[i][j] + m2.data[i][j];
	return temp;
}
Matrix Sub(const Matrix &m1, const Matrix &m2)
{
	Matrix temp;
	temp.height = m1.height;
	temp.width = m1.width;
	temp.data = new double*[m1.height];
	for (int i = 0; i < m1.height; i++)
		temp.data[i] = new double[m1.width];
	for (int i = 0; i < m1.height; i++)
		for (int j = 0; j < m1.width; j++)
			temp.data[i][j] = m1.data[i][j] - m2.data[i][j];
	return temp;
}
void Swap(Matrix &a, Matrix &b)
{
	Matrix temp;
	temp.height = a.height;
	temp.width = a.width;
	temp.data = new double*[temp.height];
	for (int i = 0; i < temp.height; ++i)
		temp.data[i] = new double[temp.width];
	for (int i = 0; i < temp.height; ++i)
		for (int j = 0; j < temp.width; ++j)
			temp.data[i][j] = a.data[i][j];

	a.height = b.height;
	a.width = b.width;
	for (int i = 0; i < a.height; ++i)
		for (int j = 0; j < a.width; ++j)
			a.data[i][j] = b.data[i][j];

	b.height = temp.height;
	b.width = temp.width;
	for (int i = 0; i < b.height; ++i)
		for (int j = 0; j < b.width; ++j)
			b.data[i][j] = temp.data[i][j];
}
void Matrix::text(const char filename[])
{
	FILE *fp = nullptr;
	fopen_s(&fp, filename, "w+");
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			fprintf(fp, "%f ", data[i][j]);
		}
		fprintf(fp, "\n");
	}
}