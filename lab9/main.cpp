#include<iostream>
#include "Mat.hpp"
#include "Filter.hpp"
using namespace std;

int main()
{
	Mat<double> img1, res, img2, img3, img4, img5, img6, img7, img8, img9, sub, add, divide, mult;
	img1.ReadBMP("Fruits.bmp");
	img1.WriteText("demo1.txt");
	img1.WriteBMP("demo1.bmp");
	img1.Flip(0);
	img1.WriteBMP("demo2.bmp");

	//图片相减
	img2.ReadBMP("scene2_fg.bmp");
	img3.ReadBMP("scene2_bg.bmp");
	sub = img2 - img3;
	sub.WriteBMP("demo3.bmp");

	//图片相加
	img2.ReadBMP("scene2_fg.bmp");
	img3.ReadBMP("scene2_bg.bmp");
	add = img2 + img3;
	add.WriteBMP("demo4.bmp");

	//图片相除
	img2.ReadBMP("scene2_fg.bmp");
	img3.ReadBMP("scene2_bg.bmp");
	divide = img2 / 2;
	divide.WriteBMP("demo5.bmp");

	//图片相乘
	img2.ReadBMP("scene2_fg.bmp");
	img3.ReadBMP("scene2_bg.bmp");
	mult = img2 * 2;
	mult.WriteBMP("demo6.bmp");

	//图片放大
	img6.ReadBMP("Airplane.bmp");
	img6.Resize(1);
	img6.WriteBMP("demo7.bmp");

	//图片左右翻转
	img7.ReadBMP("Airplane.bmp");
	img7.Flip(0);
	img7.WriteBMP("demo8.bmp");

	//阈值分割
	img7 = img2 - img3;
	img7.gray2bw(0.6);
	img7.WriteBMP("demo6.bmp");

	//滤波器
	int num;
	cout << "请输入想要的滤波器规格:(默认:5)" << endl;
	cin >> num;
	Mat<double> Lena;
	Lena.ReadBMP("Lena_gaussian.bmp");
	Filter<double> *filter = NULL;
	filter = new MeanFilter<double>(num);
	res = filter->Filtering(Lena);
	res.WriteBMP("res.bmp");


	cout << "文件处理成功" << endl;
	system("pause");
	return 0;
}
