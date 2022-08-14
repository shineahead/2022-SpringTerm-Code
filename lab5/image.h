#pragma once
#ifndef IMAGE_H
#define IMAGE_H
#include<Windows.h>
class Image
{
	public:
		Image();//�޲����Ĺ��캯�����������ж�Ϊ���Image����
		Image(int h, int w);//���캯�����أ�����h�У�w�е�Image����
		Image(int h, int w, unsigned char val);//���캯�����أ�������ͼ������ֵ��Ϊval
		Image(const char ImageName[]);//���캯�����أ������ļ�����Ӳ�̼���ͼ���ļ���ΪImage����
		Image(unsigned char *m, int rows, int cols);//���캯�����أ���һά��̬�����д���Image����ͼ��������������ɺ���������������
		Image(unsigned char m[][100], int rows);//���캯�����أ��Ӿ�̬��ά���鴴��Image����ͼ���������rows����
		Image(unsigned char **m, int h, int w);//���캯�����أ��Ӷ�̬���飨��άָ�룩����Image����ͼ��������������ɺ���������������
		Image(const Image& im);//���ƹ��캯��
		~Image();//��������

		void Readbmp(const char filename[]);//��BMP�ļ��ж���ͼ������
		void Writebmp(const char filename[]);//��ͼ�����ݱ���ΪBMPͼ���ļ�
		void ReadText(const char filename[]);//���ı��ļ��ж���ͼ������
		void WriteText(const char filename[]);//��ͼ�����ݱ���Ϊ�ı��ļ�
		unsigned char& At(int row, int col);//��ȡ��row��col�е����ص��ֵ
		void Set(int row, int col, unsigned char value);//��������(row, col)Ϊĳֵ
		void Set(unsigned char value);//����ͼ����������Ϊͬһֵ
		void Filp(int code);//ͼ��ķ�ת������code��ֵ:0�����ҷ�ת�� 1�����·�ת
		void Resize(int code);//ͼ������ţ�����code��ֵ��0����Сһ����1���Ŵ�һ��
		void Crop(int x1, int y1, int x2, int y2);//�ü���(x1, y1)����(x2,y2)��ͼ��
		void Rotate(int degree);//ͼ����ת�ĺ�������ת�Ƕ�Ϊ90�ȵ���������
		void Mean_Variance(float &m, float &var);//��ͼ��ľ�ֵ�ͷ�����ò������

		friend void Swap(Image &a, Image &b);//ʹ����Ԫ������������Image���������

	private:
		int width, height;
		unsigned char **data;
		BITMAPFILEHEADER filehead;
		BITMAPINFOHEADER infohead;
};

#endif