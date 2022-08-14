#pragma once
#ifndef IMAGE_H
#define IMAGE_H
#include<Windows.h>
class Image
{
	public:
		Image();//无参数的构造函数，创建行列都为零的Image对象
		Image(int h, int w);//构造函数重载，创建h行，w列的Image对象
		Image(int h, int w, unsigned char val);//构造函数重载，创建的图像像素值都为val
		Image(const char ImageName[]);//构造函数重载，利用文件名从硬盘加载图像文件成为Image对象
		Image(unsigned char *m, int rows, int cols);//构造函数重载，从一维静态数组中创建Image对象，图像的行数和列数由后面两个参数给出
		Image(unsigned char m[][100], int rows);//构造函数重载，从静态二维数组创建Image对象，图像的行数由rows给出
		Image(unsigned char **m, int h, int w);//构造函数重载，从动态数组（二维指针）创建Image对象，图像的行数和列数由后面两个参数给出
		Image(const Image& im);//复制构造函数
		~Image();//析构函数

		void Readbmp(const char filename[]);//从BMP文件中读入图像数据
		void Writebmp(const char filename[]);//将图像数据保存为BMP图像文件
		void ReadText(const char filename[]);//从文本文件中读入图像数据
		void WriteText(const char filename[]);//将图像数据保存为文本文件
		unsigned char& At(int row, int col);//获取第row行col列的像素点的值
		void Set(int row, int col, unsigned char value);//设置像素(row, col)为某值
		void Set(unsigned char value);//设置图像所有像素为同一值
		void Filp(int code);//图像的翻转，根据code的值:0：左右翻转， 1：上下翻转
		void Resize(int code);//图像的缩放，根据code的值：0：缩小一倍，1：放大一倍
		void Crop(int x1, int y1, int x2, int y2);//裁剪点(x1, y1)到点(x2,y2)的图像
		void Rotate(int degree);//图像旋转的函数（旋转角度为90度的整数倍）
		void Mean_Variance(float &m, float &var);//求图像的均值和方差，利用参数输出

		friend void Swap(Image &a, Image &b);//使用友元函数交换两个Image对象的数据

	private:
		int width, height;
		unsigned char **data;
		BITMAPFILEHEADER filehead;
		BITMAPINFOHEADER infohead;
};

#endif