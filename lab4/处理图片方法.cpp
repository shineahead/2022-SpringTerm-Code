#include<iostream>
#include<Windows.h>
using namespace std;

int main1()
{
	FILE *fp;
	if (fopen_s(&fp, "Fruits_480x511.bmp", "rb") != 0)
	{
		cout << "can not open the file!" << endl;
		exit(0);
	}

	long height, width;
	BITMAPFILEHEADER filehead;
	BITMAPINFOHEADER infohead;

	fread(&filehead, sizeof(BITMAPFILEHEADER), 1, fp);//文件头
	fread(&infohead, sizeof(BITMAPINFOHEADER), 1, fp);//信息头
	width = infohead.biWidth;
	height = infohead.biHeight;
	cout << "Width = " << width << " Height = " << height << endl;

	//宽度变为能被4整除的方法
	width = ((width * infohead.biBitCount) / 8 + 3);
	width = width / 3;

	cout << "照片经过补齐之后的宽和高是：" << endl;
	cout << "width = " << width << " height = " << height << endl;

	char *bmpbuff = new char[width * height * 3];
	fread(bmpbuff, sizeof(char), width * height * 3, fp);
	fclose(fp);

	//写入文件信息
	FILE *fp2;
	if (fopen_s(&fp2, "out.bmp", "wb") != 0)
	{
		cout << "can not open the file!" << endl;
		exit(0);
	}
	fwrite(&filehead, sizeof(BITMAPFILEHEADER), 1, fp2);
	fwrite(&infohead, sizeof(BITMAPINFOHEADER), 1, fp2);
	char *outbmp = bmpbuff;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width * 3; j++)		//3表示该像素以三通道储存的，占三个字节
			fwrite(outbmp++, 1, 1, fp2);
	}
	fclose(fp2);
	delete[]bmpbuff;		//释放内存空间

	cout << "图片写入成功!" << endl;
	system("pause");
	return 0;
}