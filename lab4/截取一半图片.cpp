#include<iostream>
#include<cstdlib>
#include<Windows.h>
using namespace std;

int main3()
{
	FILE *fp, *fp2;
	if (fopen_s(&fp, "Fruits.bmp", "rb") != 0)
	{
		cout << "can not open the file! " << endl;
		exit(0);
	}

	BITMAPFILEHEADER filehead;
	BITMAPINFOHEADER infohead;
	fread(&filehead, sizeof(BITMAPFILEHEADER), 1, fp);
	fread(&infohead, sizeof(BITMAPINFOHEADER), 1, fp);

	long width, height;
	width = infohead.biWidth;
	height = infohead.biHeight;
	if (width % 4 != 0)
		width = ((width * infohead.biBitCount) / 8 + 3) / 3;	//补齐宽度

	long num_pix = width * height;
	unsigned char *data = (unsigned char *)malloc(num_pix / 2 * 3);//每个像素三个字节
	fread(data, num_pix / 2 * 3, 1, fp);
	cout << num_pix / 2 * 3;
	cout << " " << sizeof(data) << endl;
	//只读入一半的像素
	//信息头里的行数和数据总数减半
	infohead.biHeight /= 2;
	infohead.biSizeImage /= 2;

	if (fopen_s(&fp2, "Fruit2.bmp", "wb") != 0)
	{
		cout << "can not open the file!" << endl;
		exit(0);
	}
	fwrite(&filehead, sizeof(BITMAPFILEHEADER), 1, fp2);
	fwrite(&infohead, sizeof(BITMAPINFOHEADER), 1, fp2);
	fwrite(data, num_pix / 2 * 3, 1, fp2);

	fclose(fp);
	fclose(fp2);
	free(data);
	cout << "写入成功" << endl;
	system("pause");
	return 0;
}