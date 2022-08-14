#ifndef MEDIANFILTER_H
#define MEDIANFILTER_H

#include "Filter.h"
class MedianFilter : public Filter
{
public:
	MedianFilter(int size);
	virtual ~MedianFilter();
	//��ֵ�˲�����
	virtual Matrix Filtering(const Matrix &input);
	void Resize(int new_size); //�ı��˲����Ĳ����߶�
	int cmp(double a, double b);
};


#endif