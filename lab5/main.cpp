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
	//ͼ������·�ת
	img.Filp(true);
	img.Writebmp("FruitsUpDown.bmp");
	//ͼ������ҷ�ת
	img.Filp(false);
	img.Writebmp("FruitsLeftRight.bmp");
	//ͼƬ��Сһ��
	img.Resize(0);
	img.Writebmp("FruitsReduce.bmp");
	//ͼƬ�Ŵ�һ��
	img.Resize(1);
	img.Resize(1);
	img.Writebmp("FruitsEnlarge.bmp");
	img.Resize(0);
	//��ȡͼ�������ֵ���������ͼ���ļ�
	unsigned char value = img.At(100, 100);
	cout << "pre = " << (int)img.At(100, 100) << endl;
	img.Set(200, 200, value);
	cout << "At_img = " << int(img.At(200, 200));
	img.Writebmp("Set.bmp");
	//�ü�ͼƬ�ļ�
	Image img3("Fruits.bmp");
	Image new_img(img3);
	new_img.Crop(0, 10, 100, 100);
	new_img.Writebmp("Cut.bmp");
	//˳ʱ����תͼ���ļ�90��
	Image new_img1(img3);
	new_img1.Rotate(90);
	new_img1.Writebmp("90.bmp");
	//˳ʱ����ת�ļ�180��
	Image new_img2(img3);
	new_img2.Rotate(180);
	new_img2.Writebmp("180.bmp");
	//˳ʱ����ת�ļ�270��
	Image new_img3(img3);
	new_img3.Rotate(270);
	new_img3.Writebmp("270.bmp");
	//����ͼ��ľ�ֵ
	float m = 0, var = 0;
	img.Mean_Variance(m, var);
	cout << "ͼ��ľ�ֵΪ:" << m << ", ����Ϊ:" << var << endl;
	//��������ͼ�������
	Image img1("Baboon.bmp");
	Image img2("Lena.bmp");
	Swap(img1, img2);
	img1.Writebmp("Exchange1.bmp");
	img2.Writebmp("Exchange2.bmp");

	cout << "�ļ�����ɹ�" << endl;
	fclose(fp);
	system("pause");
	return 0;
}