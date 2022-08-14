#pragma once
#ifndef IMAGE_H
#define IMAGE_H
#include<Windows.h>
#include"Matrix.h"

class Image : public Matrix
{
public:
	Image();//�޲����Ĺ��캯�����������ж�Ϊ���Image����
	Image(int h, int w);//���캯�����أ�����h�У�w�е�Image����
	Image(int h, int w, unsigned char val);//���캯�����أ�������ͼ������ֵ��Ϊval
	Image(const char ImageName[]);//���캯�����أ������ļ�����Ӳ�̼���ͼ���ļ���ΪImage����
	Image(unsigned char m[][100], int rows);//���캯�����أ��Ӿ�̬��ά���鴴��Image����ͼ���������rows����
	Image(unsigned char **m, int h, int w);//���캯�����أ��Ӷ�̬���飨��άָ�룩����Image����ͼ��������������ɺ���������������
	Image(const Matrix &m);//���캯�����أ���Matrix�������Image�����
	Image(const Image& im);//���ƹ��캯��
	~Image();//��������

	void Readbmp(const char filename[]);//��BMP�ļ��ж���ͼ������
	void Writebmp(const char filename[]);//��ͼ�����ݱ���ΪBMPͼ���ļ�
	void Filp(int code);//ͼ��ķ�ת������code��ֵ:0�����ҷ�ת�� 1�����·�ת
	void Resize(int h, int w);//ͼ�������
	void Crop(int x1, int y1, int x2, int y2);//�ü���(x1, y1)����(x2,y2)��ͼ��
	void Rotate(int degree);//ͼ����ת�ĺ�������ת�Ƕ�Ϊ90�ȵ���������
	double Mean();//����ͼ��ľ�ֵ
	double Variance();//����ͼ��ķ���

	Image operator-();//��λͼ��ȡ�������������ص�ֵ����������0��1��֮��
	//Ȼ��ÿ��Ԫ�ض���1.0��
	Image gray2bw(double t); //������ֵt��ͼ����ж�ֵ�������ؽ������
	//���������bmp�ļ�����infohead��filehead
	void Info(const Image &m);

	BITMAPFILEHEADER filehead;
	BITMAPINFOHEADER infohead;
	
};

#endif