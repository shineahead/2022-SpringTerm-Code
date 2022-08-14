#include<iostream>
#include "image.h"
#include<Windows.h>
using namespace std;


Image::Image() {
	width = 0;
	height = 0;
}
Image::Image(int h, int w)
{
	width = w;
	height = h;
	data = new unsigned char*[height];
	for (int i = 0; i < height; i++)
		data[i] = new unsigned char[width];
}
Image::Image(int h, int w, unsigned char val)
{
	width = w;
	height = h;
	for (int i = 0; i < height; i++)
		data[i] = new unsigned char[width];
	for (int i = 0; i < height; i++)
		data[i] = new unsigned char[width];
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			data[i][j] = val;
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
	data = new unsigned char*[height];
	for (int i = 0; i < height; i++)
		data[i] = new unsigned char[width];
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			fread(&temp, 3, 1, fp);
			data[i][j] = (temp[0] + temp[1] + temp[2]) / 3;
		}
	}
	fclose(fp);
}
Image::Image(unsigned char *m, int rows, int cols)
{
	height = rows;
	width = cols;
	for (int i = 0; i < height; i++)
		data[i] = new unsigned char[width];
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			data[i][j] = m[j];
}
Image::Image(unsigned char m[][100], int rows)
{
	height = rows;
	width = 100;
	data = new unsigned char*[height];
	for (int i = 0; i < height; i++)
		data[i] = new unsigned char[width];
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			data[i][j] = m[i][j];
}
Image::Image(unsigned char **m, int h, int w)
{
	height = h;
	width = w;
	data = new unsigned char*[height];
	for (int i = 0; i < height; i++)
		data[i] = new unsigned char[width];
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			data[i][j] = m[i][j];
}
Image::Image(const Image& im)
{
	width = im.width;
	height = im.height;
	infohead = im.infohead;
	filehead = im.filehead;
	data = new unsigned char*[height];
	for (int i = 0; i < height; i++)
		data[i] = new unsigned char[width];
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			data[i][j] = im.data[i][j];
	cout << "复制构造函数调用" << endl;
}
Image::~Image(){
	for (int i = 0; i < height; i++)
		delete[]data[i];
	delete[]data;
	std::cout << "析构函数调用" << std::endl;
}
void Image::Readbmp(const char filename[])
{
	FILE *fp;
	fopen_s(&fp, filename, "rb");

	fread(&filehead, sizeof(BITMAPFILEHEADER), 1, fp);
	fread(&infohead, sizeof(BITMAPINFOHEADER), 1, fp);
	height = infohead.biHeight;
	width = infohead.biWidth;
	unsigned char temp[4];
	data = new unsigned char*[height];
	for (int i = 0; i < height; i++)
		data[i] = new unsigned char[width];
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			fread(temp, 3, 1, fp);
			data[i][j] = (temp[0] + temp[1] + temp[2]) / 3;
		}
	}
	fclose(fp);
}

void Image::Writebmp(const char filename[])
{
	FILE *fp = nullptr;
	fopen_s(&fp, filename, "wb");
	fwrite(&filehead, sizeof(BITMAPFILEHEADER), 1, fp);
	fwrite(&infohead, sizeof(BITMAPINFOHEADER), 1, fp);
	for (int i = 0; i < infohead.biHeight; i++)
		for (int j = 0; j < infohead.biWidth; j++)
			fwrite(&data[i][j], 3, 1, fp);
	fclose(fp);
}

void Image::ReadText(const char filename[])
{
	FILE *fp;
	fopen_s(&fp, filename, "r");
	fscanf(fp, "%d", &height);
	fscanf(fp, "%d\n", &width);
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			fscanf(fp, "%d", &data[i][j]);
	fclose(fp);
}

void Image::WriteText(const char filename[])
{
	FILE *fp;
	fopen_s(&fp, filename, "w");
	fprintf(fp, "%d", &height);
	fprintf(fp, "%d\n", &width);
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			fprintf(fp, "%d", &data[i][j]);
	fclose(fp);
}

unsigned char& Image::At(int row, int col)
{
	return data[row][col];
}

void Image::Set(int row, int col, unsigned char value)
{
	data[row][col] = value;
}

void Image::Set(unsigned char value)
{
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			data[i][j] = value;
}

void Image::Filp(int code)
{
	switch (code)
	{
		case 0:	//左右翻转
			unsigned char temp1;
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
			unsigned char temp2;
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

void Image::Resize(int code)
{
	switch (code)
	{
		case 0://缩小一倍
			{unsigned char **temp1 = new unsigned char*[height / 2];
			for (int i = 0; i < height / 2; i++)
				temp1[i] = new unsigned char[width / 2];
			for (int i = 0, p = 0; i < height; i = i + 2, p++)
			{
				for (int j = 0, q = 0; j < width; j = j + 2, q++)
				{
					temp1[p][q] = data[i][j];
				}
			}
			height /= 2;
			width /= 2;
			for (int i = 0; i < height; i++)
				for (int j = 0; j < width; j++)
					data[i][j] = temp1[i][j];
			infohead.biSizeImage /= 4;
			infohead.biHeight /= 2;
			infohead.biWidth /= 2;break; }
		case 1://放大一倍
			{unsigned char **temp2 = new unsigned char*[height * 2];
			for (int i = 0; i < height * 2; i++)
				temp2[i] = new unsigned char[width * 2];
			for (int i = 0, p = 0; i < height; i++, p++)
			{
				for (int j = 0, q = 0; j < width; j++, q++)
				{
					temp2[p][q++] = data[i][j];
					temp2[p][q] = data[i][j];
				}
				p++;
				for (int j = 0, q = 0; j < width; j++, q++)
				{
					temp2[p][q++] = data[i][j];
					temp2[p][q] = data[i][j];
				}
			}
			//释放之前data申请的空间
			for (int i = 0; i < height; i++)
				delete[]data[i];
			delete[]data;
			height *= 2;
			width *= 2;
			//放大一倍图片超过了data之前申请的空间，故应该重新给data申请空间
			data = new unsigned char*[height];
			for (int i = 0; i < height; i++)
				data[i] = new unsigned char[width];
			for (int i = 0; i < height; i++)
				for (int j = 0; j < width; j++)
					data[i][j] = temp2[i][j];
			infohead.biSizeImage *= 4;
			infohead.biHeight *= 2;
			infohead.biWidth *= 2;break; }
		default: std::cout << "请输入正确的code值" << std::endl; break;
	}
}

void Image::Crop(int x1, int y1, int x2, int y2)
{
	if (x2 > x1 && y2 > y1)
	{
		int h = y2 - y1 + 1;
		int w = x2 - x1 + 1;
		unsigned char** temp = new unsigned char*[h];
		for (int i = 0; i < h; i++)
			temp[i] = new unsigned char[w];
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
		data = new unsigned char*[h];
		for (int i = 0; i < h; i++)
			data[i] = new unsigned char[w];
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
	if (degree == 90) {
		unsigned char **temp1 = new unsigned char*[width];
		for (int i = 0; i < width; i++)
			temp1[i] = new unsigned char[height];
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
		data = new unsigned char*[height];
		for (int i = 0; i < height; i++)
			data[i] = new unsigned char[width];
		for (int i = 0; i < height; i++)
			for (int j = 0; j < width; j++)
				data[i][j] = temp1[i][j];
	}
	else if (degree == 180) {
		unsigned char t2;
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
		unsigned char **temp2 = new unsigned char*[width];
		for (int i = 0; i < width; i++)
			temp2[i] = new unsigned char[height];
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
		data = new unsigned char*[height];
		for (int i = 0; i < height; i++)
			data[i] = new unsigned char[width];
		for (int i = 0; i < height; i++)
			for (int j = 0; j < width; j++)
				data[i][j] = temp2[i][j];
	}
	else
		std::cout << "输入的degree值不符合要求" << std::endl;
}

void Image::Mean_Variance(float &m, float &var)
{
	long sum = 0;
	float value = 0;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			sum += data[i][j];
		}
	}
	m = static_cast<float>(sum) / (width * height);
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			value += static_cast<float>((m - data[i][j]) * (m - data[i][j]));
	var = static_cast<float>(value / (width * height));
}

//void Swap(Image& a, Image& b)
//{
//	Image t(a);
//	t.Writebmp("Ex.bmp");
//	a = b;
//	b = t;
//	a.Writebmp("Ex1.bmp");
//	b.Writebmp("Ex2.bmp");
//	cout << "图像交换成功" << endl;
//}

void Swap(Image& a, Image& b)
{
	int h, w;
	BITMAPFILEHEADER filehead1;
	BITMAPINFOHEADER infohead1;
	h = a.height;
	w = b.width;
	filehead1 = a.filehead;
	infohead1 = a.infohead;
	unsigned char **temp = new unsigned char*[h];
	for (int i = 0; i < h; i++)
		temp[i] = new unsigned char[w];
	for (int i = 0; i < h; i++)
		for (int j = 0; j < w; j++)
			temp[i][j] = a.data[i][j];
	a.height = b.height;
	a.width = b.width;
	a.infohead = b.infohead;
	a.filehead = b.filehead;
	for (int i = 0; i < h; i++)
		for (int j = 0; j < w; j++)
			a.data[i][j] = b.data[i][j];
	b.height = h;
	b.width = w;
	b.infohead = infohead1;
	b.filehead = filehead1;
	for (int i = 0; i < h; i++)
		for (int j = 0; j < w; j++)
			b.data[i][j] = temp[i][j];
}

