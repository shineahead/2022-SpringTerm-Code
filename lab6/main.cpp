#include<iostream>
#include"image.h"
using namespace std;

int main()
{
	Image ans("Fruits.bmp");//用来传递信息头和文件头的图像
	Matrix m(160000, 1);
	for (int i = 0; i < 160000; i++)
		m.At(i, 0) = i % 256;
	m.Reshape(400, 400);
	Image img(m);
	img.infohead = ans.infohead;
	img.filehead = ans.filehead;
	img.Writebmp("Matrix.bmp");
	Matrix d = m.MajorDiagonal();
	Image *p = new Image(d);
	p->infohead = img.infohead;
	p->filehead = img.filehead;
	p->Reshape(20, 20);
	p->text("test.txt");
	p->Writebmp("pImageReshaped.bmp");
	delete p;
	p = nullptr;

	Image im("Fruits.bmp");
	im.Resize(200, 200);
	im.Writebmp("Resized.bmp");
	im.Rotate(-180);
	im.Writebmp("Rotated.bmp");

	Image img1("Fruits.bmp");
	Image img2("Word.bmp");
	
	//两图片相加
	Image img_add(Add(img1, img2));
	img_add.infohead = img1.infohead;
	img_add.filehead = img1.filehead;
	img_add.Writebmp("Add.bmp");
	//两图片相减
	Image img_sub(Sub(img1, img2));
	img_sub.infohead = img1.infohead;
	img_sub.filehead = img1.filehead;
	img_sub.Writebmp("Sub.bmp");

	//图片的转置
	Image img3("lena.bmp");
	img3.Transpose();
	img3.Writebmp("Transpose.bmp");

	//在右边拼接图片
	Image img4("Airplane.bmp");
	Image img5("Baboon.bmp");
	img4.Cat(img5, 1);
	img4.Writebmp("CATRight.bmp");

	//在下面拼接图片
	Image img6("Airplane.bmp");
	Image img7("Baboon.bmp");
	img6.Cat(img7, 2);
	img6.Writebmp("CATDown.bmp");

	return 0;
}