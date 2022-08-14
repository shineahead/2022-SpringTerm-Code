#pragma once
#ifndef MATRIX_H
#define MATRIX_H

class Matrix {
public:
	Matrix();
	Matrix(int h, int w);
	Matrix(int h, int w, double val);
	Matrix(const Matrix &m);
	virtual ~Matrix();

	void ReadText(const char filename[]);//���ı��ļ��ж����������
	void WriteText(const char filename[]);//���������ݱ���Ϊ�ı��ļ�
	void Zeros(int h, int w);//���ݲ�������h��w�е�ȫ�����
	void Ones(int h, int w);//���ݲ�������h��w�е�ȫ1����
	void Random(int h, int w);//����h��w�е�������󣬾����Ԫ��Ϊ��0��1��֮������ʵ��
	void Identity(int n);//���ݲ�������n��n�еĵ�λ����

	int Height() const;//��ȡ���������
	int Width() const;//��ȡ���������
	Matrix MajorDiagonal();//��������Խ����ϵ�Ԫ�أ����һ��N��1�еľ���
	//NΪ���Խ���Ԫ�صĸ���
	Matrix MinoDiagonal();//�����ĸ��Խ����ϵ�Ԫ�أ����һ��N��1�еľ���
	//NΪ���Խ�����Ԫ�صĸ���
	Matrix Column(int n);//���ؾ����n���ϵ�Ԫ�أ����һ��N��1�еľ������
	//NΪ��n����Ԫ�صĸ���

	void Transpose();//������ת��

	double &At(int row, int col);//��ȡ��row�е�col�еľ���Ԫ�ص�ֵ
	void Set(int row, int col, double value);//���õ�row��col�о���Ԫ�ص�ֵΪvalue
	void Set(double value);//���þ�������Ԫ��Ϊͬһֵvalue

	void Normalize();//�ú����Ѿ�����������Ե���������0��1�����䣬���ѵ�ǰ�����
	//����Ԫ�ص���Сֵmin���0�����ֵmax��Ϊ1������Ԫ�ص�ֵ���Եı䵽��0��1�����䣬��ʽΪ��
	//t` = (t - min) / max, ע���������������������ͬ����Ĵ���

	void Reshape(int h, int w);//�ھ���Ԫ���������������£����������б�Ϊ���������Ĵ�С
	bool IsEmpty();//�жϾ����Ƿ�Ϊ��
	bool IsSquare();//�жϾ����Ƿ�Ϊ����
	void CopyTo(Matrix &m);//�������Ƹ�m
	void Mult(double s);//�����ÿ��Ԫ�ض����Բ���s
	void Cat(Matrix &m, int code);//�������뵱ǰ�������ƴ�ӣ�code����
	//ƴ�ӵķ�ʽ����mƴ�ӵ���ǰ������ϣ��£�����

	friend Matrix Add(const Matrix &m1, const Matrix &m2);//��Ԫ������������m1��m2���
	//���������Ϊ�����ķ���ֵ
	friend Matrix Sub(const Matrix &m1, const Matrix &m2);//��Ԫ������������m1��m2���
	//���������Ϊ�����ķ���ֵ

	friend void Swap(Matrix &a, Matrix &b);//��Ԫ������������������
	void text(const char filename[]);
protected:
	int height;
	int width;
	double **data;
};

#endif