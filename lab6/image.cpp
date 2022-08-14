#include<iostream>
#include"image.h"
#include<Windows.h>
using namespace std;

Image::Image()
{
	height = 0;
	width = 0;
	data = nullptr;
}
Image::Image(int h, int w)
{
	height = h;
	width = w;
	data = new double*[height];
	for (int i = 0; i < height; i++)
		data[i] = new double[width];
}
Image::Image(int h, int w, unsigned char val)
{
	height = h;
	width = w;
	for (int i = 0; i < height; i++)
		data[i] = new double[width];
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			data[i][j] = double(val);
}
Image::Image(const char ImageName[])
{
	FILE *fp;
	fopen_s(&fp, ImageName, "rb");

	fread(&filehead, sizeof(BITMAPFILEHEADER), 1, fp);
	fread(&infohead, sizeof(BITMAPINFOHEADER), 1, fp);
	width = infohead.biWidth;
	height = infohead.biHeight;
	
	unsigned char temp[4];
	data = new double*[height];
	for (int i = 0; i < height; i++)
		data[i] = new double[width];
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			fread(&temp, 3, 1, fp);
			data[i][j] = double((temp[0] + temp[1] + temp[2]) / 3);
		}
	}
	fclose(fp);
}
Image::Image(unsigned char m[][100], int rows)
{
	height = rows;
	width = 100;
	data = new double*[height];
	for (int i = 0; i < height; i++)
		data[i] = new double[width];
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			data[i][j] = double(m[i][j]);
}
Image::Image(unsigned char **m, int h, int w)
{
	height = h;
	width = w;
	data = new double*[height];
	for (int i = 0; i < height; i++)
		data[i] = new double[width];
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			data[i][j] = double(m[i][j]);
}
Image::Image(const Matrix& m): Matrix(m){}
Image::Image(const Image& im)
{
	height = im.height;
	width = im.width;
	data = new double*[height];
	for (int i = 0; i < height; i++)
	{
		data[i] = new double[width];
		for (int j = 0; j < width; j++)
			data[i][j] = im.data[i][j];
	}
	infohead = im.infohead;
	filehead = im.filehead;
	cout << "复制构造函数调用" << endl;
}
Image::~Image()
{
	cout << "析构函数调用" << endl;
}

void Image::Readbmp(const char filename[])
{
	FILE *fp;
	fopen_s(&fp, filename, "rb");

	fread(&filehead, sizeof(BITMAPFILEHEADER), 1, fp);
	fread(&infohead, sizeof(BITMAPINFOHEADER), 1, fp);
	width = infohead.biWidth;
	height = infohead.biHeight;

	unsigned char temp[4];
	data = new double*[height];
	for (int i = 0; i < height; i++)
		data[i] = new double[width];
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			fread(&temp, 3, 1, fp);
			data[i][j] = double((temp[0] + temp[1] + temp[2]) / 3);
		}
	}
	fclose(fp);
}
void Image::Writebmp(const char filename[])
{
	FILE *fp = nullptr;
	fopen_s(&fp, filename, "wb");
	infohead.biHeight = height;
	infohead.biWidth = width;
	infohead.biSizeImage = height * width;

	fwrite(&filehead, sizeof(BITMAPFILEHEADER), 1, fp);
	fwrite(&infohead, sizeof(BITMAPINFOHEADER), 1, fp);
	
	for (int i = 0; i < infohead.biHeight; i++)
	{
		for (int j = 0; j < infohead.biWidth; j++)
		{
			unsigned char temp = 0;
			if (data[i][j] > 255)
				temp = 255;
			else if (data[i][j] < 0)
				temp = 0;
			else
				temp = static_cast<unsigned char>(data[i][j]);
			fwrite(&temp, 1, 1, fp);
			fwrite(&temp, 1, 1, fp);
			fwrite(&temp, 1, 1, fp);
		}
	}
	fclose(fp);
}

void Image::Filp(int code)
{
	switch (code)
	{
	case 0:	//左右翻转
		double temp1;
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j <= width / 2; j++)
			{
				temp1 = data[i][j];
				data[i][j] = data[i][width - 1 - j];
				data[i][width - 1 - j] = temp1;
			}
		}; break;
	case 1:	//上下翻转
		double temp2;
		for (int i = 0; i <= height / 2; i++)
		{
			for (int j = 0; j < width; j++)
			{
				temp2 = data[height - 1 - i][j];
				data[height - 1 - i][j] = data[i][j];
				data[i][j] = temp2;
			}
		}break;
	default: std::cout << "请输入正确的code值" << std::endl; break;
	}
}
void Image::Resize(int h, int w)
{
	int temp_w, temp_h, ww, hh;
	temp_h = h;
	temp_w = w;
	hh = height / temp_h;
	ww = width / temp_w;
	double **temp = new double*[h];
	for (int i = 0; i < h; i++)
		temp[i] = new double[w];

	for (int i = 0, p = 0; p < h; i += hh, p++)
		for (int j = 0, q = 0; q < w; j += ww, q++)
			temp[p][q] = data[i][j];

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
			data[i][j] = temp[i][j];
	//释放空间
	for (int i = 0; i < temp_h; i++)
		delete[]temp[i];
	delete[]temp;
}
void Image::Crop(int x1, int y1, int x2, int y2)
{
	if (x2 > x1 && y2 > y1)
	{
		int h = y2 - y1 + 1;
		int w = x2 - x1 + 1;
		double** temp = new double*[h];
		for (int i = 0; i < h; i++)
			temp[i] = new double[w];
		for (int i = y1, p = 0; p < h, i < y2 - 1; i++, p++)
			for (int j = x1, q = 0; q < w, j < x2 - 1; j++, q++)
				temp[p][q] = data[i][j];
		for (int i = 0; i < height; i++)
			delete[]data[i];
		delete[]data;
		height = h;
		width = w;
		infohead.biHeight = h - 1;
		infohead.biWidth = w - 1;
		infohead.biSizeImage = infohead.biHeight * infohead.biWidth;
		if (infohead.biSizeImage % 4 != 0)
			infohead.biWidth = ((infohead.biWidth * infohead.biBitCount) / 8 + 3) / 3;	//补齐宽度
		else
			infohead.biWidth = infohead.biWidth;
		data = new double*[h];
		for (int i = 0; i < h; i++)
			data[i] = new double[w];
		for (int i = 0; i < h; i++)
			for (int j = 0; j < w; j++)
				data[i][j] = temp[i][j];
		for (int i = 0; i < h; i++)
			delete[]temp[i];
		delete[]temp;
	}
	else
		cout << "请输入正确的坐标" << endl;
}
void Image::Rotate(int degree)
{
	degree = degree > -degree ? degree : -degree;
	if (degree == 90) {
		double **temp1 = new double*[width];
		for (int i = 0; i < width; i++)
			temp1[i] = new double[height];
		for (int i = 0; i < height; i++)
			for (int j = 0; j < width; j++)
				temp1[j][height - i - 1] = data[i][j];
		for (int i = 0; i < height; i++)
			delete[]data[i];
		delete[]data;
		int t1 = width;
		width = height;
		height = t1;
		infohead.biHeight = height;
		infohead.biWidth = width;
		data = new double*[height];
		for (int i = 0; i < height; i++)
			data[i] = new double[width];
		for (int i = 0; i < height; i++)
			for (int j = 0; j < width; j++)
				data[i][j] = temp1[i][j];
	}
	else if (degree == 180) {
		double t2;
		for (int i = 0; i < height / 2; i++)
		{
			for (int j = 0; j < width; j++)
			{
				t2 = data[height - 1 - i][j];
				data[height - 1 - i][j] = data[i][width - j - 1];
				data[i][width - j - 1] = t2;
			}
		}
	}
	else if (degree == 270) {
		double **temp2 = new double*[width];
		for (int i = 0; i < width; i++)
			temp2[i] = new double[height];
		for (int i = 0; i < height; i++)
			for (int j = 0; j < width; j++)
				temp2[j][i] = data[i][j];
		for (int i = 0; i < height; i++)
			delete[]data[i];
		delete[]data;
		int t3 = width;
		width = height;
		height = t3;
		infohead.biHeight = height;
		infohead.biWidth = width;
		data = new double*[height];
		for (int i = 0; i < height; i++)
			data[i] = new double[width];
		for (int i = 0; i < height; i++)
			for (int j = 0; j < width; j++)
				data[i][j] = temp2[i][j];
	}
	else
		std::cout << "输入的degree值不符合要求" << std::endl;
}
double Image::Mean()
{
	double sum = 0;
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			sum += data[i][j];
	return sum / (width * height);
}
double Image::Variance()
{
	double sum = 0, mean = 0, res = 0;
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			sum += data[i][j];
	mean = sum / (width * height);
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			res += (mean - data[i][j]) * (mean - data[i][j]);
	return res;
}
