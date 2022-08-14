#include<iostream>
#include<Windows.h>
using namespace std;

//检查该图片的长度和宽度是否能被四整除
void Readbmp(const char *filename, unsigned char **d, BITMAPFILEHEADER filehead, BITMAPINFOHEADER infohead)
{
	FILE *fp = NULL;
	fopen_s(&fp, filename, "rb");
	long bit = infohead.biSizeImage;
	if (bit % 4 != 0)
		infohead.biWidth = ((infohead.biWidth * infohead.biBitCount) / 8 + 3) / 3;	//补齐宽度
	else
		infohead.biWidth = infohead.biWidth;
	return;
}
//把图片的像素信息写进数组
void Writebmp(const char *filename, unsigned char **d, BITMAPFILEHEADER filehead, BITMAPINFOHEADER infohead)
{
	FILE *fp = NULL;
	fopen_s(&fp, filename, "rb");
	long width, height;
	width = infohead.biWidth;
	height = infohead.biHeight;
	unsigned char temp[4];
	for (int i = 0; i < height; i++)	//把像素写到二维数组里面
	{
		for (int j = 0; j < width; j++)
		{
			fread(temp, 3, 1, fp);
			d[i][j] = (temp[0] + temp[1] + temp[2]) / 3;
		}
	}
}
//把图像上下翻转
void FileImageUpDown(unsigned char **d, int rows, int cols)
{
	unsigned char temp;
	for (int i = 0; i <= rows / 2; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			temp = d[rows - 1 - i][j];
			d[rows - 1 - i][j] = d[i][j];
			d[i][j] = temp;
		}
	}
}
//把图像左右翻转
void FileImageLeftRight(unsigned char **d, int rows, int cols)
{
	unsigned char temp;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j <= cols / 2; j++)
		{
			temp = d[i][j];
			d[i][j] = d[i][cols - 1 - j];
			d[i][cols - 1 - j] = temp;
		}
	}
}
//将原图缩小为原尺寸的一半
void ResizeImage(unsigned char **a, unsigned char **b, int rows, int cols)
{
	for (int i = 0, p = 0; i < rows; i = i + 2, p++)
	{
		for (int j = 0, q = 0; j < cols; j = j + 2, q++)
		{
			b[p][q] = a[i][j];
		}
	}
}

int main()
{
	FILE *fp = NULL;
	fopen_s(&fp, "Fruits.bmp", "rb");

	BITMAPFILEHEADER filehead;
	BITMAPINFOHEADER infohead;
	fread(&filehead, sizeof(BITMAPFILEHEADER), 1, fp);
	fread(&infohead, sizeof(BITMAPINFOHEADER), 1, fp);

	long width, height;
	width = infohead.biWidth;
	height = infohead.biHeight;

	//储存像素的二维数组
	unsigned char **d = new unsigned char *[height];
	for (int i = 0; i < height; i++)
		d[i] = new unsigned char [width];
	//检测是否需要补齐宽度
	Readbmp("Fruits.bmp", d, filehead, infohead);
	width = infohead.biWidth;
	height = infohead.biHeight;
	//把图片的像素写到二维数组里面
	unsigned char **d2 = new unsigned char *[height];
	for (int i = 0; i < height; i++)
		d2[i] = new unsigned char[width];
	Writebmp("Fruits.bmp", d2, filehead, infohead);
	//调用FileImageUpDown函数
	FileImageUpDown(d2, height, width);
	FILE *fp_UpDown;
	fopen_s(&fp_UpDown, "Fruits_UpDown.bmp", "wb");
	fwrite(&filehead, sizeof(BITMAPFILEHEADER), 1, fp_UpDown);
	fwrite(&infohead, sizeof(BITMAPINFOHEADER), 1, fp_UpDown);
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
			fwrite(&d2[i][j], 3, 1, fp_UpDown);
	}
	//重新把图片的像素写到二维数组里面
	unsigned char **d3 = new unsigned char *[height];
	for (int i = 0; i < height; i++)
		d3[i] = new unsigned char[width];
	Writebmp("Fruits.bmp", d3, filehead, infohead);
	//调用FileImageLeftRight函数
	FileImageLeftRight(d3, height, width);
	FILE *fp_LeftRight;
	fopen_s(&fp_LeftRight, "Fruits_LeftRight.bmp", "wb");
	fwrite(&filehead, sizeof(BITMAPFILEHEADER), 1, fp_LeftRight);
	fwrite(&infohead, sizeof(BITMAPINFOHEADER), 1, fp_LeftRight);
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
			fwrite(&d3[i][j], 3, 1, fp_LeftRight);
	}
	//重新把图片的像素写到二维数组里面
	unsigned char **d4 = new unsigned char *[height];
	for (int i = 0; i < height; i++)
		d4[i] = new unsigned char[width];
	Writebmp("Fruits.bmp", d4, filehead, infohead);
	unsigned char **b = new unsigned char *[height / 2];
	for (int i = 0; i < height / 2; i++)
		b[i] = new unsigned char[width / 2];
	ResizeImage(d4, b, height, width);
	FILE *fp_resize;
	fopen_s(&fp_resize, "Fruits_resize.bmp", "wb");
	infohead.biSizeImage /= 4;
	infohead.biHeight /= 2;
	infohead.biWidth /= 2;
	fwrite(&filehead, sizeof(BITMAPFILEHEADER), 1, fp_resize);
	fwrite(&infohead, sizeof(BITMAPINFOHEADER), 1, fp_resize);
	for (int i = 0; i < height / 2; i++)
	{
		for (int j = 0; j < width / 2; j++)
			fwrite(&b[i][j], 3, 1, fp_resize);
	}
	//释放申请的内存空间
	for (int i = 0; i < height; i++)
	{
		delete[]d[i];
		delete[]d2[i];
		delete[]d3[i];
		delete[]d4[i];
	}
	delete[]d;
	delete[]d2;
	delete[]d3;
	delete[]d4;
	for (int i = 0; i < height / 2; i++)
	{
		delete[]b[i];
	}
	delete[]b;
	//关闭文件夹
	fclose(fp);
	fclose(fp_LeftRight);
	fclose(fp_UpDown);
	fclose(fp_resize);
	cout << "文件处理成功" << endl;
	system("pause");
	return 0;
}
