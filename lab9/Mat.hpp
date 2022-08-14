#include<iostream>
#include<Windows.h>
#ifndef MAT_HPP
#define MAT_HPP


using namespace std;

template< class T>
class Mat
{
public:
	Mat() 								 //无参数的构造函数，创建行列都为零的Mat对象
	{
		mydata = new myData;
		mydata->height = 0;
		mydata->width = 0;
		mydata->data = nullptr;
		mydata->num = 1;
		mydata->M_max = 0;
		mydata->M_min = 0;
	}
	Mat(int h, int w) 					 //构造函数重载，创建h行，w列的Mat对象
	{
		mydata = new myData;
		mydata->height = h;
		mydata->width = w;
		mydata->data = new T*[mydata->height];
		for (int i = 0; i < mydata->height; i++)
			mydata->data = new T*[mydata->width];
		mydata->num = 1;
		mydata->M_max = 0;
		mydata->M_min = 0;
	}
	Mat(int h, int w, T val)   		 //构造函数重载，矩阵元素的值都为val;
	{
		mydata = new myData;
		mydata->height = h;
		mydata->width = w;
		mydata->num = 1;
		mydata->data = new T*[mydata->height];
		for (int i = 0; i < mydata->height; i++)
		{
			mydata->data = new T*[mydata->width];
			for (int j = 0; j < mydata->width; j++)
				mydata->data[i][j] = val;
		}
		mydata->M_max = 0;
		mydata->M_min = 0;
	}
	Mat(const char* ImageName) 		 //构造函数重载，利用文件名从硬盘加载图像文件成为Mat对象;
	{
		mydata = new myData;
		mydata->num = 1;
		mydata->data = new T*[mydata->height];
		for (int i = 0; i < mydata->height; i++)
			mydata->data = new T*[mydata->width];
		this->ReadBMP(ImageName);
		mydata->M_max = 0;
		mydata->M_min = 0;
	}
	Mat(T **m, int h, int w)   		 //构造函数重载，从动态数组创建Mat对象;
	{
		mydata = new myData;
		mydata->height = h;
		mydata->width = w;
		mydata->num = 1;
		mydata->data = new T*[mydata->height];
		for (int i = 0; i < mydata->height; i++)
		{
			mydata->data = new T*[mydata->width];
			for (int j = 0; j < mydata->width; j++)
				mydata->data[i][j] = m[i][j];
		}
		mydata->M_max = 0;
		mydata->M_min = 0;
	}
	Mat(const Mat &m) 					 //拷贝构造函数;
	{
		mydata = m.mydata;
		mydata->num++;
	}
	virtual ~Mat() 					 //析构函数;
	{
		if (mydata->num == 1)
		{
			for (int i = 0; i < mydata->height; i++)
				delete[]mydata->data[i];
			delete[]mydata->data;
			delete mydata;
		}
		else
			mydata->num--;
		cout << "析构函数调用" << endl;
	}

	void ReadBMP(const char *filename) //从硬盘文件中读入图像数据
	{
		FILE *fp = nullptr;
		fopen_s(&fp, filename, "rb");
		
		fread(&mydata->filehead, sizeof(BITMAPFILEHEADER), 1, fp);
		fread(&mydata->infohead, sizeof(BITMAPINFOHEADER), 1, fp);
		mydata->width = mydata->infohead.biWidth;
		mydata->height = mydata->infohead.biHeight;
		

		unsigned char temp[4];
		mydata->data = new T*[mydata->height];
		for (int i = 0; i < mydata->height; i++)
			mydata->data[i] = new T[mydata->width];
		for (int i = 0; i < mydata->height; i++)
		{
			for (int j = 0; j < mydata->width; j++)
			{
				fread(&temp, 3, 1, fp);
				mydata->data[i][j] = T((temp[0] + temp[1] + temp[2]) / 3);
			}
		}
		fclose(fp);
	}
	void WriteBMP(const char *filename) //将数据保存为图像文件
	{
		FILE *fp = nullptr;
		fopen_s(&fp, filename, "wb");
		mydata->infohead.biHeight = mydata->height;
		mydata->infohead.biWidth = mydata->width;
		mydata->infohead.biSizeImage = mydata->height * mydata->width;

		fwrite(&mydata->filehead, sizeof(BITMAPFILEHEADER), 1, fp);
		fwrite(&mydata->infohead, sizeof(BITMAPINFOHEADER), 1, fp);
		//此时矩阵数据在[0, 1]之间，应先进行转化
		//值为0说明矩阵的数据没有normalize过
		if (mydata->M_max != 0 || mydata->M_min != 0)
		{
			cout << "check" << endl;
			for (int i = 0; i < mydata->height; i++)
			{
				for (int j = 0; j < mydata->width; j++)
				{
					if (mydata->data[i][j] == 0)
						mydata->data[i][j] = mydata->M_min;
					else if (mydata->data[i][j] == 1)
						mydata->data[i][j] = mydata->M_max;
					else
						mydata->data[i][j] = mydata->data[i][j] * mydata->M_max + mydata->M_min;
				}
			}
		}


		for (int i = 0; i < mydata->infohead.biHeight; i++)
		{
			for (int j = 0; j < mydata->infohead.biWidth; j++)
			{
				unsigned char temp = 0;
				if (mydata->data[i][j] > 255)
					temp = 255;
				else if (mydata->data[i][j] < 0)
					temp = 0;
				else
					temp = static_cast<unsigned char>(mydata->data[i][j]);
				fwrite(&temp, 1, 1, fp);
				fwrite(&temp, 1, 1, fp);
				fwrite(&temp, 1, 1, fp);
			}
		}
		fclose(fp);
	}

	// 下面2个读写文本文件的函数，需要考虑不同数据类型的存储
	void ReadText(const char *filename) //从文本文件中读入数据
	{
		FILE *fp;
		fopen_s(&fp, filename, "rb");
		fread(&mydata->height, sizeof(int), 1, fp);
		fread(&mydata->width, sizeof(int), 1, fp);

		for (int i = 0; i < mydata->height; i++)
			fread(mydata->data[i], sizeof(T) * mydata->width, 1, fp);
	}
	void WriteText(const char *filename) //将数据保存为文本文件
	{
		FILE *fp = nullptr;
		fopen_s(&fp, filename, "w+");
		fprintf(fp, "%d ", this->mydata->height);
		fprintf(fp, "%d ", this->mydata->width);
		fprintf(fp, "\n");
		for (int i = 0; i < this->mydata->height; i++)
		{
			for (int j = 0; j < this->mydata->width; j++)
			{
				fprintf(fp, "%f ", this->mydata->data[i][j]);
			}
			fprintf(fp, "\n");
		}
	}

	int Height()						  //得到矩阵高度
	{
		return mydata->height;
	}
	int Height() const					  //得到矩阵高度
	{
		return mydata->height;
	}
	int Width()					  	  //得到矩阵宽度
	{
		return mydata->width;
	}
	int Width() const					  //得到矩阵宽度
	{
		return mydata->width;
	}

	T Min() 							  //得到矩阵元素的最小值
	{
		T min = mydata->data[0][0];
		for (int i = 0; i < mydata->height; i++)
			for (int j = 0; j < mydata->width; j++)
				if (mydata->data[i][j] < min)
					min = mydata->data[i][j];
		return min;
	}
	T Min() const 						  //得到矩阵元素的最小值
	{
		T min = mydata->data[0][0];
		for (int i = 0; i < mydata->height; i++)
			for (int j = 0; j < mydata->width; j++)
				if (mydata->data[i][j] < min)
					min = mydata->data[i][j];
		return min;
	}
	T Max() 							  //得到矩阵元素的最大值
	{
		T max = mydata->data[0][0];
		for (int i = 0; i < mydata->height; i++)
			for (int j = 0; j < mydata->width; j++)
				if (mydata->data[i][j] > max)
					max = mydata->data[i][j];
		return max;
	}
	T Max() const 						  //得到矩阵元素的最大值
	{
		T max = mydata->data[0][0];
		for (int i = 0; i < mydata->height; i++)
			for (int j = 0; j < mydata->width; j++)
				if (mydata->data[i][j] > max)
					max = mydata->data[i][j];
		return max;
	}

	T& At(int row, int col)      		  //获取某点的值
	{
		return mydata->data[row][col];
	}
	const T& At(int row, int col) const  //获取某点的值，const重载
	{
		return mydata->data[row][col];
	}
	void Set(int row, int col, T value)  //设置元素(row,col)为某值;
	{
		mydata->data[row][col] = value;
	}
	void Set(T value) 					  //设置所有元素为同一值;
	{
		for (int i = 0; i < mydata->height; i++)
			for (int j = 0; j < mydata->width; j++)
				mydata->data[i][j] = value;
	}

	void Flip(int code) 				  //翻转; 根据code的值：0:左右翻转，1:上下翻转
	{
		switch (code)
		{
		case 0:	//左右翻转
			T temp1;
			for (int i = 0; i < mydata->height; i++)
			{
				for (int j = 0; j <= mydata->width / 2; j++)
				{
					temp1 = mydata->data[i][j];
					mydata->data[i][j] = mydata->data[i][mydata->width - 1 - j];
					mydata->data[i][mydata->width - 1 - j] = temp1;
				}
			}; break;
		case 1:	//上下翻转
			T temp2;
			for (int i = 0; i <= mydata->height / 2; i++)
			{
				for (int j = 0; j < mydata->width; j++)
				{
					temp2 = mydata->data[mydata->height - 1 - i][j];
					mydata->data[mydata->height - 1 - i][j] = mydata->data[i][j];
					mydata->data[i][j] = temp2;
				}
			}break;
		default: std::cout << "请输入正确的code值" << std::endl; break;
		}
	}
	void Resize(int code)                //缩放；根据code的值：0：缩小1倍，1：放大1倍
	{
		switch (code)
		{
		case 0://缩小一倍
		{T **temp1 = new T*[mydata->height / 2];
		for (int i = 0; i < mydata->height / 2; i++)
			temp1[i] = new T[mydata->width / 2];
		for (int i = 0, p = 0; i < mydata->height; i = i + 2, p++)
		{
			for (int j = 0, q = 0; j < mydata->width; j = j + 2, q++)
			{
				temp1[p][q] = mydata->data[i][j];
			}
		}
		mydata->height /= 2;
		mydata->width /= 2;
		for (int i = 0; i < mydata->height; i++)
			for (int j = 0; j < mydata->width; j++)
				mydata->data[i][j] = temp1[i][j];
		mydata->infohead.biSizeImage /= 4;
		mydata->infohead.biHeight /= 2;
		mydata->infohead.biWidth /= 2; break; }
		case 1://放大一倍
		{T **temp2 = new T*[mydata->height * 2];
		for (int i = 0; i < mydata->height * 2; i++)
			temp2[i] = new T[mydata->width * 2];
		for (int i = 0, p = 0; i < mydata->height; i++, p++)
		{
			for (int j = 0, q = 0; j < mydata->width; j++, q++)
			{
				temp2[p][q++] = mydata->data[i][j];
				temp2[p][q] = mydata->data[i][j];
			}
			p++;
			for (int j = 0, q = 0; j < mydata->width; j++, q++)
			{
				temp2[p][q++] = mydata->data[i][j];
				temp2[p][q] = mydata->data[i][j];
			}
		}
		//释放之前data申请的空间
		for (int i = 0; i < mydata->height; i++)
			delete[]mydata->data[i];
		delete[]mydata->data;
		mydata->height *= 2;
		mydata->width *= 2;
		//放大一倍图片超过了data之前申请的空间，故应该重新给data申请空间
		mydata->data = new T*[mydata->height];
		for (int i = 0; i < mydata->height; i++)
			mydata->data[i] = new T[mydata->width];
		for (int i = 0; i < mydata->height; i++)
			for (int j = 0; j < mydata->width; j++)
				mydata->data[i][j] = temp2[i][j];
		mydata->infohead.biSizeImage *= 4;
		mydata->infohead.biHeight *= 2;
		mydata->infohead.biWidth *= 2; break; }
		default: std::cout << "请输入正确的code值" << std::endl; break;
		}
	}
	void Crop(int x1, int y1, int x2, int y2) //裁剪点(x1,y1)到点(x2,y2)
	{
		if (x2 > x1 && y2 > y1)
		{
			int h = y2 - y1 + 1;
			int w = x2 - x1 + 1;
			T** temp = new T*[h];
			for (int i = 0; i < h; i++)
				temp[i] = new T[w];
			for (int i = y1, p = 0; p < h, i < y2 - 1; i++, p++)
				for (int j = x1, q = 0; q < w, j < x2 - 1; j++, q++)
					temp[p][q] = mydata->data[i][j];
			for (int i = 0; i < mydata->height; i++)
				delete[]mydata->data[i];
			delete[]mydata->data;
			mydata->height = h;
			mydata->width = w;
			mydata->infohead.biHeight = h - 1;
			mydata->infohead.biWidth = w - 1;
			mydata->infohead.biSizeImage = mydata->infohead.biHeight * mydata->infohead.biWidth;
			if (mydata->infohead.biSizeImage % 4 != 0)
				mydata->infohead.biWidth = ((mydata->infohead.biWidth * mydata->infohead.biBitCount) / 8 + 3) / 3;	//补齐宽度
			else
				mydata->infohead.biWidth = mydata->infohead.biWidth;
			mydata->data = new T*[h];
			for (int i = 0; i < h; i++)
				mydata->data[i] = new T[w];
			for (int i = 0; i < h; i++)
				for (int j = 0; j < w; j++)
					mydata->data[i][j] = temp[i][j];
			for (int i = 0; i < h; i++)
				delete[]temp[i];
			delete[]temp;
		}
		else
			cout << "请输入正确的坐标" << endl;
	}
	void Rotate(int degree)			  //旋转，90度的整数倍
	{
		degree = degree > -degree ? degree : -degree;
		if (degree == 90) {
			T **temp1 = new T*[mydata->width];
			for (int i = 0; i < mydata->width; i++)
				temp1[i] = new T[mydata->height];
			for (int i = 0; i < mydata->height; i++)
				for (int j = 0; j < mydata->width; j++)
					temp1[j][mydata->height - i - 1] = mydata->data[i][j];
			for (int i = 0; i < mydata->height; i++)
				delete[]mydata->data[i];
			delete[]mydata->data;
			int t1 = mydata->width;
			mydata->width = mydata->height;
			mydata->height = t1;
			mydata->infohead.biHeight = mydata->height;
			mydata->infohead.biWidth = mydata->width;
			mydata->data = new T*[mydata->height];
			for (int i = 0; i < mydata->height; i++)
				mydata->data[i] = new T[mydata->width];
			for (int i = 0; i < mydata->height; i++)
				for (int j = 0; j < mydata->width; j++)
					mydata->data[i][j] = temp1[i][j];
		}
		else if (degree == 180) {
			double t2;
			for (int i = 0; i < mydata->height / 2; i++)
			{
				for (int j = 0; j < mydata->width; j++)
				{
					t2 = mydata->data[mydata->height - 1 - i][j];
					mydata->data[mydata->height - 1 - i][j] = mydata->data[i][mydata->width - j - 1];
					mydata->data[i][mydata->width - j - 1] = t2;
				}
			}
		}
		else if (degree == 270) {
			T **temp2 = new T*[mydata->width];
			for (int i = 0; i < mydata->width; i++)
				temp2[i] = new T[mydata->height];
			for (int i = 0; i < mydata->height; i++)
				for (int j = 0; j < mydata->width; j++)
					temp2[j][i] = mydata->data[i][j];
			for (int i = 0; i < mydata->height; i++)
				delete[]mydata->data[i];
			delete[]mydata->data;
			int t3 = mydata->width;
			mydata->width = mydata->height;
			mydata->height = t3;
			mydata->infohead.biHeight = mydata->height;
			mydata->infohead.biWidth = mydata->width;
			mydata->data = new T*[mydata->height];
			for (int i = 0; i < mydata->height; i++)
				mydata->data[i] = new T[mydata->width];
			for (int i = 0; i < mydata->height; i++)
				for (int j = 0; j < mydata->width; j++)
					mydata->data[i][j] = temp2[i][j];
		}
		else
			std::cout << "输入的degree值不符合要求" << std::endl;
	}
	void Transpose() 					  // 转置
	{
		int temp_h, temp_w;
		temp_h = mydata->width;
		temp_w = mydata->height;
		T **temp_data = new T*[temp_h];
		for (int i = 0; i < temp_h; i++)
			temp_data[i] = new T[temp_w];
		for (int i = 0, p = 0; i < mydata->height; i++, p++)
			for (int j = 0, q = 0; j < mydata->width; j++, q++)
				temp_data[q][p] = mydata->data[i][j];

		for (int i = 0; i < mydata->height; i++)
			delete[]mydata->data[i];
		delete[]mydata->data;

		mydata->height = temp_h;
		mydata->width = temp_w;
		mydata->data = new T*[mydata->height];
		for (int i = 0; i < mydata->height; i++)
			mydata->data[i] = new T[mydata->width];

		for (int i = 0; i < mydata->height; i++)
			for (int j = 0; j < mydata->width; j++)
				mydata->data[i][j] = temp_data[i][j];
		//释放该临时矩阵
		for (int i = 0; i < mydata->height; i++)
			delete[]temp_data[i];
		delete[]temp_data;
	}
	void Reshape(int h, int w) 		  //在元素总数不变的情况下，将矩阵的行列变为参数给定的大小
	{
		int temp_h, temp_w;
		temp_h = h;
		temp_w = w;
		T **temp_data = new T*[temp_h];
		for (int i = 0; i < temp_h; i++)
			temp_data[i] = new T[temp_w];
		int p = 0, q = 0;
		for (int i = 0; i < mydata->height; i++)
		{
			for (int j = 0; j < mydata->width; j++)
			{
				if (q == temp_w)
				{
					p++;
					q = 0;
				}
				temp_data[p][q] = mydata->data[i][j];
				q++;
			}
		}
		for (int i = 0; i < mydata->height; i++)
			delete[]mydata->data[i];
		delete[]mydata->data;

		mydata->height = temp_h;
		mydata->width = temp_w;
		mydata->data = new T*[mydata->height];
		for (int i = 0; i < mydata->height; i++)
			mydata->data[i] = new T[mydata->width];

		for (int i = 0; i < mydata->height; i++)
			for (int j = 0; j < mydata->width; j++)
				mydata->data[i][j] = temp_data[i][j];
		//释放该临时矩阵
		for (int i = 0; i < mydata->height; i++)
			delete[]temp_data[i];
		delete[]temp_data;
	}

	bool IsEmpty()			// 判断是否为空矩阵
	{
		if (mydata->data[mydata->height - 2][mydata->width - 2])
			return false;
		else
			return true;
	}
	bool IsSquare()		// 判断矩阵是否为方阵
	{
		return (mydata->height == mydata->width);
	}
	Mat<T>  MajorDiagonal()// 求主对角线上的元素，输出一个N行1列的矩阵，N为主对角线上元素的个数
	{
		T **temp = new T*[mydata->height];
		for (int i = 0; i < mydata->height; i++)
			temp[i] = new T[1];
		int N = 0;
		for (int i = 0; i < mydata->height; i++)
			for (int j = 0; j < mydata->width; j++)
				if (i == j)
					temp[N++][0] = mydata->data[i][j];
		T**temp_u = new T*[mydata->height];
		for (int i = 0; i < mydata->height; i++)
			temp_u[i] = new T[1];
		for (int i = 0; i < mydata->height; i++)
			temp_u[i][0] = temp[i][0];
		Mat m(temp_u, mydata->height, 1);
		return m;
	}
	Mat<T>  MinorDiagonal()// 求副对角线上的元素，输出一个N行1列的矩阵，N为副对角线上元素的个数
	{
		T **temp = new T*[mydata->height];
		for (int i = 0; i < mydata->height; i++)
			temp[i] = new T[1];
		int N = 0;
		for (int i = 0; i < mydata->height; i++)
			for (int j = 0; j < mydata->width; j++)
				if (i + j == mydata->height - 1)
					temp[N++][0] = mydata->data[i][j];
		T**temp_u = new T*[mydata->height];
		for (int i = 0; i < mydata->height; i++)
			temp_u[i] = new T[1];
		for (int i = 0; i < mydata->height; i++)
			temp_u[i][0] = temp[i][0];
		Mat m(temp_u, mydata->height, 1);
		return m;
	}
	Mat<T> Row(int n)// 返回矩阵的第n行上的元素，组出一个1行N列的矩阵输出，N为第n行上元素的个数
	{
		T**temp = new T*[1];
		temp[0] = new T[mydata->width];
		int N = 0;
		for (int i = 0; i < mydata->width; i++)
			temp[0][N++] = mydata->data[n - 1][i];
		Mat m(temp, 1, mydata->width);
		return m;
	}
	Mat<T> Column(int n)// 返回矩阵的第n列上的元素，组出一个N行1列的矩阵输出，N为第n列上元素的个数
	{
		T**temp = new T*[mydata->height];
		for (int i = 0; i < mydata->height; i++)
			temp[i] = new T[1];
		int N = 0;
		for (int i = 0; i < mydata->height; i++)
			temp[N++][0] = mydata->data[i][n - 1];
		T**temp_u = new T*[mydata->height];
		for (int i = 0; i < mydata->height; i++)
			temp_u[i] = new T[1];
		for (int i = 0; i < mydata->height; i++)
			temp_u[i][0] = temp[i][0];
		Mat m(temp_u, mydata->height, 1);
		return m;
	}
	void Cat(Mat<T> &m, int code)  // 将m与当前对象进行拼接，code代表拼接的方式
	{
		int temp_h, temp_w;
		temp_h = mydata->height;
		temp_w = mydata->width;
		double **temp_data = new double*[temp_h];
		for (int i = 0; i < temp_h; i++)
			temp_data[i] = new double[temp_w];
		for (int i = 0; i < mydata->height; i++)
			for (int j = 0; j < mydata->width; j++)
				temp_data[i][j] = mydata->data[i][j];

		for (int i = 0; i < mydata->height; i++)
			delete[]mydata->data[i];
		delete[]mydata->data;

		if (code == 1)
		{
			mydata->width += m.mydata->width;
			mydata->data = new double*[mydata->height];
			for (int i = 0; i < mydata->height; i++)
				mydata->data[i] = new double[mydata->width];
			for (int i = 0; i < temp_h; i++)
				for (int j = 0; j < temp_w; j++)
					mydata->data[i][j] = temp_data[i][j];

			for (int i = 0; i < mydata->height; i++)
				for (int j = 0; j < m.mydata->width; j++)
					mydata->data[i][j + m.mydata->width] = m.mydata->data[i][j];
		}
		else if (code == 2)
		{
			mydata->height += m.mydata->height;
			mydata->data = new double*[mydata->height];
			for (int i = 0; i < mydata->height; i++)
				mydata->data[i] = new double[mydata->width];
			for (int i = 0; i < temp_h; i++)
				for (int j = 0; j < temp_w; j++)
					mydata->data[i][j] = temp_data[i][j];

			for (int i = 0; i < m.mydata->height; i++)
				for (int j = 0; j < m.mydata->width; j++)
					mydata->data[i + m.mydata->height][j] = m.mydata->data[i][j];
		}
		else if (code == 3)
		{
			mydata->width += m.mydata->width;
			mydata->data = new double*[mydata->height];
			for (int i = 0; i < mydata->height; i++)
				mydata->data[i] = new double[mydata->width];
			for (int i = 0; i < temp_h; i++)
				for (int j = 0; j < temp_w; j++)
					mydata->data[i][j + m.mydata->width] = temp_data[i][j];

			for (int i = 0; i < m.mydata->height; i++)
				for (int j = 0; j < m.mydata->width; j++)
					mydata->data[i][j] = m.mydata->data[i][j];
		}
		else if (code == 4)
		{
			mydata->height += m.height;
			mydata->data = new double*[mydata->height];
			for (int i = 0; i < mydata->height; i++)
				mydata->data[i] = new double[mydata->width];
			for (int i = 0; i < temp_h; i++)
				for (int j = 0; j < temp_w; j++)
					data[i + m.height][j] = temp_data[i][j];

			for (int i = 0; i < m.height; i++)
				for (int j = 0; j < m.width; j++)
					data[i][j] = m.data[i][j];
		}
		else
			cout << "wrong code!" << endl;
	}
	void CopyTo(Mat<T> &m)		   // 将矩阵复制给m，完成深拷贝
	{
		if (!m.mydata)
			m.mydata = new myData;
		m.mydata->height = this->mydata->height;
		m.mydata->width = this->mydata->width;
		m.mydata->M_max = this->mydata->M_max;
		m.mydata->M_min = this->mydata->M_min;
		m.mydata->infohead = this->mydata->infohead;
		m.mydata->filehead = this->mydata->filehead;
		m.mydata->data = new T*[m.mydata->height];
		for (int i = 0; i < m.mydata->height; i++)
			m.mydata->data[i] = new T[m.mydata->width];
		m.mydata->num = 1;
		for (int i = 0; i < m.mydata->height; i++)
			for (int j = 0; j < m.mydata->width; j++)
				m.mydata->data[i][j] = this->mydata->data[i][j];
	}
	Mat<T> Clone() 			   // 从当前对象拷贝创建一个新的矩阵，完成深拷贝
	{
		Mat<T> temp;
		this->CopyTo(temp);
		return temp;
	}

	Mat<double> Normalize()//将矩阵元素的值变换到0-1范围内，以double类型的Mat对象输出。注意：在这个函数里，无法访问Mat<double>类型的对象的私有成员data，需要调用其At函数获得某个元素。
	{
		Mat<double> temp;
		temp = this->Clone();
		double max = 0, min = 0;
		for (int i = 0; i < temp.mydata->height; i++)
		{
			for (int j = 0; j < temp.mydata->width; j++)
			{
				if (temp.mydata->data[i][j] >= max)
					max = temp.mydata->data[i][j];
				if (temp.mydata->data[i][j] <= min)
					min = temp.mydata->data[i][j];
			}
		}
		temp.mydata->M_max = max;
		temp.mydata->M_min = min;
		for (int i = 0; i < temp.mydata->height; i++)
		{
			for (int j = 0; j < temp.mydata->width; j++)
			{
				if (temp.mydata->data[i][j] == min)
					temp.mydata->data[i][j] = 0;
				else if (temp.mydata->data[i][j] == max)
					temp.mydata->data[i][j] = 1;
				else
					temp.mydata->data[i][j] = (temp.mydata->data[i][j] - min) / max;
			}
		}
		return temp;
	}

	Mat<T>& operator=(const Mat<T> &m)  //重载赋值运算符，完成对象间的赋值（使用引用计数）；
	{
		m.mydata->num++;
		this->mydata = m.mydata;
		return *this;
	}
	bool operator==(const Mat<T> &m)    //判断两个Mat对象是否相等
	{
		bool flag = true;
		if (this->mydata->height != m.mydata->height || this->mydata->width != m.mydata->width)
		{
			flag = false;
		}
		else
		{
			for (int i = 0; i < this->mydata->height; i++)
				for (int j = 0; j < this->mydata->width; j++)
					if (this->mydata->data[i][j] != m.mydata->data[i][j])
					{
						flag = false;
						break;
					}
		}
		return flag;
	}
	friend Mat<T> operator+(const Mat<T> &lhs, const Mat<T> &rhs)  //对应元素的数值相加；
	{
		Mat<T> temp(lhs);
		for (int i = 0; i < temp.mydata->height; i++)
			for (int j = 0; j < temp.mydata->width; j++)
				temp.mydata->data[i][j] += rhs.mydata->data[i][j];
		return temp;
	}
	friend Mat<T> operator-(const Mat<T> &lhs, const Mat<T> &rhs)  //对应元素的数值相减；
	{
		Mat<T> temp(lhs);
		for (int i = 0; i < temp.mydata->height; i++)
			for (int j = 0; j < temp.mydata->width; j++)
				temp.mydata->data[i][j] -= rhs.mydata->data[i][j];
		return temp;
	}
	Mat<T>& operator++()  				//前置自加；
	{
		for (int i = 0; i < this->mydata->height; i++)
			for (int j = 0; j < this->mydata->width; j++)
				++this->mydata->data[i][j];
		return *this;
	}
	Mat<T>& operator--()  			    //前置自减；
	{
		for (int i = 0; i < this->mydata->height; i++)
			for (int j = 0; j < this->mydata->width; j++)
				--this->mydata->data[i][j];
		return *this;
	}
	Mat<T> operator ++(int) 			//后置自加；
	{
		Mat<T> temp = *this;
		for (int i = 0; i < temp.mydata->height; i++)
			for (int j = 0; j < temp.mydata->width; j++)
				temp.mydata->data[i][j]++;
		return temp;
	}
	Mat<T> operator --(int)  			//后置自减；
	{
		Mat<T> temp = *this;
		for (int i = 0; i < temp.mydata->height; i++)
			for (int j = 0; j < temp.mydata->width; j++)
				temp.mydata->data[i][j]--;
		return temp;
	}
	Mat<double> operator-()  			// 取反；注意要把矩阵的数据规整到[0,1]区间后，再用1减
	{
		this->Normalize();
		for (int i = 0; i < this->mydata->height; i++)
			for (int j = 0; j < this->mydata->width; j++)
				this->mydata->data[i][j] = 1.0 - this->mydata->data[i][j];
		return *this;
	}


	friend Mat<T> operator+(Mat<T> &m, T num) //所有元素加上同一数值;
	{
		Mat<T> temp = m;
		for (int i = 0; i < temp.mydata->height; i++)
			for (int j = 0; j < temp.mydata->width; j++)
				temp.mydata->data[i][j] += num;
		return temp;
	}
	friend Mat<T> operator-(Mat<T> &m, T num) //所有元素减去同一数值;
	{
		Mat<T> temp = m;
		for (int i = 0; i < temp.mydata->height; i++)
			for (int j = 0; j < temp.mydata->width; j++)
				temp.mydata->data[i][j] -= num;
		return temp;
	}
	friend Mat<T> operator*(Mat<T> &m, T num) //所有元素乘上同一数值;
	{
		Mat<T> temp = m;
		for (int i = 0; i < temp.mydata->height; i++)
			for (int j = 0; j < temp.mydata->width; j++)
				temp.mydata->data[i][j] *= num;
		return temp;
	}
	friend Mat<T> operator/(Mat<T> &m, T num) //所有元素除以同一数值;
	{
		Mat<T> temp = m;
		for (int i = 0; i < temp.mydata->height; i++)
			for (int j = 0; j < temp.mydata->width; j++)
				temp.mydata->data[i][j] /= num;
		return temp;
	}
	
	//另外，用友元函数再写出一个T类型的数和一个Mat对象的加,减,乘,除
	friend Mat<T> operator+(T num, Mat<T> &m) //所有元素加上同一数值;
	{
		Mat<T> temp = m;
		for (int i = 0; i < temp.mydata->height; i++)
			for (int j = 0; j < temp.mydata->width; j++)
				temp.mydata->data[i][j] += num;
		return temp;
	}
	friend Mat<T> operator-(T num, Mat<T> &m) //所有元素减去同一数值;
	{
		Mat<T> temp = m;
		for (int i = 0; i < temp.mydata->height; i++)
			for (int j = 0; j < temp.mydata->width; j++)
				temp.mydata->data[i][j] -= num;
		return temp;
	}
	friend Mat<T> operator*(T num, Mat<T> &m) //所有元素乘上同一数值;
	{
		Mat<T> temp = m;
		for (int i = 0; i < temp.mydata->height; i++)
			for (int j = 0; j < temp.mydata->width; j++)
				temp.mydata->data[i][j] *= num;
		return temp;
	}
	friend Mat<T> operator/(T num, Mat<T> &m) //所有元素除以同一数值;
	{
		Mat<T> temp = m;
		for (int i = 0; i < temp.mydata->height; i++)
			for (int j = 0; j < temp.mydata->width; j++)
				temp.mydata->data[i][j] /= num;
		return temp;
	}

	Mat<T> gray2bw(T t) 					//以给定阈值t进行二值化，返回结果对象
	{
		*this = this->Normalize();
		for (int i = 0; i < mydata->height; i++)
		{
			for (int j = 0; j < mydata->width; j++)
			{
				if (mydata->data[i][j] < t)
					mydata->data[i][j] = 0;
				else
					mydata->data[i][j] = 1;
			}
		}
		return *this;
	}

	friend void Swap(Mat<T> &a, Mat<T> &b)//使用友元函数交换两个Mat对象
	{
		Mat<T> temp = a;
		a.mydata = b.mydata;
		b.mydata = temp.mydata;
	}


private:
	// 自己实现一个结构体，来存储矩阵的行数、列数、引用计数和数据指针
	struct myData
	{
		BITMAPFILEHEADER filehead;
		BITMAPINFOHEADER infohead;
		int height;
		int width;
		int M_max;
		int M_min;
		T** data;
		int num;	//引用计数
	};
	// 这里需要声明指向该结构体的指针作为数据成员
	myData* mydata;
};
#endif // !MAT_HPP