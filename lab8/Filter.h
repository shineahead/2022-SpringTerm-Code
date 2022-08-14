#ifndef FILTER_H
#define FILTER_H
#include "Image.h"

class Filter
{
public:
	Filter();
	Filter(int size); //���캯��
	virtual ~Filter(); //��������
	void Resize(int new_size); //�ı��˲����Ĳ����߶�
	//�˲�����
	virtual Matrix Filtering(const Matrix &input) = 0;
protected:
	int filterSize;
};

#endif