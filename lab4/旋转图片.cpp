#include<iostream>
#include<Windows.h>
using namespace std;

//����ͼƬ�ĳ��ȺͿ���Ƿ��ܱ�������
void Readbmp(const char *filename, unsigned char **d, BITMAPFILEHEADER filehead, BITMAPINFOHEADER infohead)
{
	FILE *fp = NULL;
	fopen_s(&fp, filename, "rb");
	long bit = infohead.biSizeImage;
	if (bit % 4 != 0)
		infohead.biWidth = ((infohead.biWidth * infohead.biBitCount) / 8 + 3) / 3;	//������
	else
		infohead.biWidth = infohead.biWidth;
	return;
}
//��ͼƬ��������Ϣд������
void Writebmp(const char *filename, unsigned char **d, BITMAPFILEHEADER filehead, BITMAPINFOHEADER infohead)
{
	FILE *fp = NULL;
	fopen_s(&fp, filename, "rb");
	long width, height;
	width = infohead.biWidth;
	height = infohead.biHeight;
	unsigned char temp[4];
	for (int i = 0; i < height; i++)	//������д����ά��������
	{
		for (int j = 0; j < width; j++)
		{
			fread(temp, 3, 1, fp);
			d[i][j] = (temp[0] + temp[1] + temp[2]) / 3;
		}
	}
}
//��ͼ�����·�ת
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
//��ͼ�����ҷ�ת
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
//��ԭͼ��СΪԭ�ߴ��һ��
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

	//�������صĶ�ά����
	unsigned char **d = new unsigned char *[height];
	for (int i = 0; i < height; i++)
		d[i] = new unsigned char [width];
	//����Ƿ���Ҫ������
	Readbmp("Fruits.bmp", d, filehead, infohead);
	width = infohead.biWidth;
	height = infohead.biHeight;
	//��ͼƬ������д����ά��������
	unsigned char **d2 = new unsigned char *[height];
	for (int i = 0; i < height; i++)
		d2[i] = new unsigned char[width];
	Writebmp("Fruits.bmp", d2, filehead, infohead);
	//����FileImageUpDown����
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
	//���°�ͼƬ������д����ά��������
	unsigned char **d3 = new unsigned char *[height];
	for (int i = 0; i < height; i++)
		d3[i] = new unsigned char[width];
	Writebmp("Fruits.bmp", d3, filehead, infohead);
	//����FileImageLeftRight����
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
	//���°�ͼƬ������д����ά��������
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
	//�ͷ�������ڴ�ռ�
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
	//�ر��ļ���
	fclose(fp);
	fclose(fp_LeftRight);
	fclose(fp_UpDown);
	fclose(fp_resize);
	cout << "�ļ�����ɹ�" << endl;
	system("pause");
	return 0;
}
