#pragma once
#ifndef IMAGE_H
#define IMAGE_H
#include<Windows.h>
#include"Matrix.h"

class Image : public Matrix
{
public:
	Image();//无参数的构造函数，创建行列都为零的Image对象
	Image(int h, int w);//构造函数重载，创建h行，w列的Image对象
	Image(int h, int w, unsigned char val);//构造函数重载，创建的图像像素值都为val
	Image(const char ImageName[]);//构造函数重载，利用文件名从硬盘加载图像文件成为Image对象
	Image(unsigned char m[][100], int rows);//构造函数重载，从静态二维数组创建Image对象，图像的行数由rows给出
	Image(unsigned char **m, int h, int w);//构造函数重载，从动态数组（二维指针）创建Image对象，图像的行数和列数由后面两个参数给出
	Image(const Matrix &m);//构造函数重载，由Matrix类对象构造Image类对象
	Image(const Image& im);//复制构造函数
	~Image();//析构函数

	void Readbmp(const char filename[]);//从BMP文件中读入图像数据
	void Writebmp(const char filename[]);//将图像数据保存为BMP图像文件
	void Filp(int code);//图像的翻转，根据code的值:0：左右翻转， 1：上下翻转
	void Resize(int h, int w);//图像的缩放
	void Crop(int x1, int y1, int x2, int y2);//裁剪点(x1, y1)到点(x2,y2)的图像
	void Rotate(int degree);//图像旋转的函数（旋转角度为90度的整数倍）
	double Mean();//返回图像的均值
	double Variance();//返回图像的方差

	Image operator-();//对位图像取反，把所有像素的值都调整到【0，1】之间
	//然后每个元素都被1.0减
	Image gray2bw(double t); //给定阈值t对图像进行二值化，返回结果对象
	//用来方便给bmp文件赋上infohead和filehead
	void Info(const Image &m);

	BITMAPFILEHEADER filehead;
	BITMAPINFOHEADER infohead;
	
};

#endif