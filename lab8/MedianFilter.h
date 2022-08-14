#ifndef MEDIANFILTER_H
#define MEDIANFILTER_H

#include "Filter.h"
class MedianFilter : public Filter
{
public:
	MedianFilter(int size);
	virtual ~MedianFilter();
	//中值滤波函数
	virtual Matrix Filtering(const Matrix &input);
	void Resize(int new_size); //改变滤波器的操作尺度
	int cmp(double a, double b);
};


#endif