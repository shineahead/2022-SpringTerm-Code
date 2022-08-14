#include<iostream>
#include<Windows.h>
#include "image.h"
using namespace std;

int main()
{
	Image img;
	FILE *fp;
	fopen_s(&fp, "Fruits.bmp", "rb");

	BITMAPFILEHEADER filehead;
	BITMAPINFOHEADER infohead;
	fread(&filehead, sizeof(BITMAPFILEHEADER), 1, fp);
	fread(&infohead, sizeof(BITMAPINFOHEADER), 1, fp);

	long width, height;
	width = infohead.biWidth;
	height = infohead.biHeight;
	img.Readbmp("Fruits.bmp");
	Image img_ss;
	img_ss.Readbmp("Fruits.bmp");
	img_ss.Filp(false);
	img_ss.Writebmp("ssss.bmp");
	img_ss.Resize(0);
	img.Writebmp("FruitsCopy.bmp");
	img.WriteText("FruitsCopy.txt");
	//图像的上下翻转
	img.Filp(true);
	img.Writebmp("FruitsUpDown.bmp");
	//图像的左右翻转
	img.Filp(false);
	img.Writebmp("FruitsLeftRight.bmp");
	//图片缩小一倍
	img.Resize(0);
	img.Writebmp("FruitsReduce.bmp");
	//图片放大一倍
	img.Resize(1);
	img.Resize(1);
	img.Writebmp("FruitsEnlarge.bmp");
	img.Resize(0);
	//获取图像的像数值，并保存该图像文件
	unsigned char value = img.At(100, 100);
	cout << "pre = " << (int)img.At(100, 100) << endl;
	img.Set(200, 200, value);
	cout << "At_img = " << int(img.At(200, 200));
	img.Writebmp("Set.bmp");
	//裁剪图片文件
	Image img3("Fruits.bmp");
	Image new_img(img3);
	new_img.Crop(0, 10, 100, 100);
	new_img.Writebmp("Cut.bmp");
	//顺时针旋转图像文件90度
	Image new_img1(img3);
	new_img1.Rotate(90);
	new_img1.Writebmp("90.bmp");
	//顺时针旋转文件180度
	Image new_img2(img3);
	new_img2.Rotate(180);
	new_img2.Writebmp("180.bmp");
	//顺时针旋转文件270度
	Image new_img3(img3);
	new_img3.Rotate(270);
	new_img3.Writebmp("270.bmp");
	//计算图像的均值
	float m = 0, var = 0;
	img.Mean_Variance(m, var);
	cout << "图像的均值为:" << m << ", 方差为:" << var << endl;
	//交换两个图像的数据
	Image img1("Baboon.bmp");
	Image img2("Lena.bmp");
	Swap(img1, img2);
	img1.Writebmp("Exchange1.bmp");
	img2.Writebmp("Exchange2.bmp");

	cout << "文件处理成功" << endl;
	fclose(fp);
	system("pause");
	return 0;
}