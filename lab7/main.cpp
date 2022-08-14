#include<iostream>
#include"image.h"
using namespace std;

int main()
{
	Image ans("scene2_fg.bmp");	//用来传递信息头和文件头的图像
	Image img1("scene2_fg.bmp");
	Image img2("scene2_bg.bmp");

	//图片相减
	Image sub(img1 - img2);
	sub.Info(ans);
	sub.Writebmp("sub_Image.bmp");

	//图片减去一个数
	Image sub2(img1 - img2);
	sub2.Info(ans);
	sub2.Writebmp("sub_Image2.bmp");

	//图片相加
	Image add(img1 + img2);
	add.Info(ans);
	add.Writebmp("add_Image.bmp");

	//图片加上一个数
	Image add2(img1 + 2);
	add2.Info(ans);
	add2.Writebmp("add2_Image.bmp");

	//图片相乘
	Image mult(img1 * img2);
	mult.Info(ans);
	mult.Writebmp("mult_Image.bmp");

	//图片乘以一个数
	Image mult2(img1 * 2);
	mult2.Info(ans);
	mult2.Writebmp("mult2_Image.bmp");

	//图片相除
	Image divide(img1 / img2);
	divide.Info(ans);
	divide.Writebmp("divide_Image.bmp");

	//图片除以一个数
	Image divide2(img1 / 2);
	divide2.Info(ans);
	divide2.Writebmp("divide2_Image.bmp");

	//图片自加
	Image add_personal("scene2_fg.bmp");
	add_personal.Info(ans);
	add_personal++;
	add_personal.Writebmp("add_personal.bmp");

	//图片自减
	Image sub_personal("scene2_fg.bmp");
	sub_personal.Info(ans);
	sub_personal--;
	sub_personal.Writebmp("sub_personal.bmp");

	//图片相等
	Image img3("scene2_fg.bmp");
	Image img4("scene2_bg.bmp");
	img4 = img3;
	img4.Writebmp("equal.bmp");

	//图片取反
	Image img5("Lena.bmp");
	-img5;
	img5.Writebmp("retreat.bmp");

	//阈值分割
	Image img6(img1 - img2);
	img6.Info(ans);
	img6.gray2bw(0.9);
	img6.Writebmp("break_up.bmp");


	cout << "图片处理成功" << endl;
	system("pause");
	return 0;
}