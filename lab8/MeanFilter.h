#ifndef MEANFILTER_H
#define MEANFILTER_H
#include "Filter.h"

class MeanFilter : public Filter
{
public:
	MeanFilter(int size);
	virtual ~MeanFilter();
	//均值滤波器
	virtual Matrix Filtering(const Matrix &input);
	void Resize(int new_size); //改变滤波器的操作尺度

};

#endif