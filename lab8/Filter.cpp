#include "Filter.h"

Filter::Filter()
{
	filterSize = 0;
}

Filter::Filter(int size)
{
	filterSize = size;
}

Filter::~Filter()
{

}

void Filter::Resize(int new_size)
{
	filterSize = new_size;
}