#ifndef FILTER_H
#define FILTER_H
#include "Image.h"

class Filter
{
public:
	Filter();
	Filter(int size); //构造函数
	virtual ~Filter(); //析构函数
	void Resize(int new_size); //改变滤波器的操作尺度
	//滤波函数
	virtual Matrix Filtering(const Matrix &input) = 0;
protected:
	int filterSize;
};

#endif