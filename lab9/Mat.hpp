#include<iostream>
#include<Windows.h>
#ifndef MAT_HPP
#define MAT_HPP


using namespace std;

template< class T>
class Mat
{
public:
	Mat() 								 //�޲����Ĺ��캯�����������ж�Ϊ���Mat����
	{
		mydata = new myData;
		mydata->height = 0;
		mydata->width = 0;
		mydata->data = nullptr;
		mydata->num = 1;
		mydata->M_max = 0;
		mydata->M_min = 0;
	}
	Mat(int h, int w) 					 //���캯�����أ�����h�У�w�е�Mat����
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
	Mat(int h, int w, T val)   		 //���캯�����أ�����Ԫ�ص�ֵ��Ϊval;
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
	Mat(const char* ImageName) 		 //���캯�����أ������ļ�����Ӳ�̼���ͼ���ļ���ΪMat����;
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
	Mat(T **m, int h, int w)   		 //���캯�����أ��Ӷ�̬���鴴��Mat����;
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
	Mat(const Mat &m) 					 //�������캯��;
	{
		mydata = m.mydata;
		mydata->num++;
	}
	virtual ~Mat() 					 //��������;
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
		cout << "������������" << endl;
	}

	void ReadBMP(const char *filename) //��Ӳ���ļ��ж���ͼ������
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
	void WriteBMP(const char *filename) //�����ݱ���Ϊͼ���ļ�
	{
		FILE *fp = nullptr;
		fopen_s(&fp, filename, "wb");
		mydata->infohead.biHeight = mydata->height;
		mydata->infohead.biWidth = mydata->width;
		mydata->infohead.biSizeImage = mydata->height * mydata->width;

		fwrite(&mydata->filehead, sizeof(BITMAPFILEHEADER), 1, fp);
		fwrite(&mydata->infohead, sizeof(BITMAPINFOHEADER), 1, fp);
		//��ʱ����������[0, 1]֮�䣬Ӧ�Ƚ���ת��
		//ֵΪ0˵�����������û��normalize��
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

	// ����2����д�ı��ļ��ĺ�������Ҫ���ǲ�ͬ�������͵Ĵ洢
	void ReadText(const char *filename) //���ı��ļ��ж�������
	{
		FILE *fp;
		fopen_s(&fp, filename, "rb");
		fread(&mydata->height, sizeof(int), 1, fp);
		fread(&mydata->width, sizeof(int), 1, fp);

		for (int i = 0; i < mydata->height; i++)
			fread(mydata->data[i], sizeof(T) * mydata->width, 1, fp);
	}
	void WriteText(const char *filename) //�����ݱ���Ϊ�ı��ļ�
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

	int Height()						  //�õ�����߶�
	{
		return mydata->height;
	}
	int Height() const					  //�õ�����߶�
	{
		return mydata->height;
	}
	int Width()					  	  //�õ�������
	{
		return mydata->width;
	}
	int Width() const					  //�õ�������
	{
		return mydata->width;
	}

	T Min() 							  //�õ�����Ԫ�ص���Сֵ
	{
		T min = mydata->data[0][0];
		for (int i = 0; i < mydata->height; i++)
			for (int j = 0; j < mydata->width; j++)
				if (mydata->data[i][j] < min)
					min = mydata->data[i][j];
		return min;
	}
	T Min() const 						  //�õ�����Ԫ�ص���Сֵ
	{
		T min = mydata->data[0][0];
		for (int i = 0; i < mydata->height; i++)
			for (int j = 0; j < mydata->width; j++)
				if (mydata->data[i][j] < min)
					min = mydata->data[i][j];
		return min;
	}
	T Max() 							  //�õ�����Ԫ�ص����ֵ
	{
		T max = mydata->data[0][0];
		for (int i = 0; i < mydata->height; i++)
			for (int j = 0; j < mydata->width; j++)
				if (mydata->data[i][j] > max)
					max = mydata->data[i][j];
		return max;
	}
	T Max() const 						  //�õ�����Ԫ�ص����ֵ
	{
		T max = mydata->data[0][0];
		for (int i = 0; i < mydata->height; i++)
			for (int j = 0; j < mydata->width; j++)
				if (mydata->data[i][j] > max)
					max = mydata->data[i][j];
		return max;
	}

	T& At(int row, int col)      		  //��ȡĳ���ֵ
	{
		return mydata->data[row][col];
	}
	const T& At(int row, int col) const  //��ȡĳ���ֵ��const����
	{
		return mydata->data[row][col];
	}
	void Set(int row, int col, T value)  //����Ԫ��(row,col)Ϊĳֵ;
	{
		mydata->data[row][col] = value;
	}
	void Set(T value) 					  //��������Ԫ��Ϊͬһֵ;
	{
		for (int i = 0; i < mydata->height; i++)
			for (int j = 0; j < mydata->width; j++)
				mydata->data[i][j] = value;
	}

	void Flip(int code) 				  //��ת; ����code��ֵ��0:���ҷ�ת��1:���·�ת
	{
		switch (code)
		{
		case 0:	//���ҷ�ת
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
		case 1:	//���·�ת
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
		default: std::cout << "��������ȷ��codeֵ" << std::endl; break;
		}
	}
	void Resize(int code)                //���ţ�����code��ֵ��0����С1����1���Ŵ�1��
	{
		switch (code)
		{
		case 0://��Сһ��
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
		case 1://�Ŵ�һ��
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
		//�ͷ�֮ǰdata����Ŀռ�
		for (int i = 0; i < mydata->height; i++)
			delete[]mydata->data[i];
		delete[]mydata->data;
		mydata->height *= 2;
		mydata->width *= 2;
		//�Ŵ�һ��ͼƬ������data֮ǰ����Ŀռ䣬��Ӧ�����¸�data����ռ�
		mydata->data = new T*[mydata->height];
		for (int i = 0; i < mydata->height; i++)
			mydata->data[i] = new T[mydata->width];
		for (int i = 0; i < mydata->height; i++)
			for (int j = 0; j < mydata->width; j++)
				mydata->data[i][j] = temp2[i][j];
		mydata->infohead.biSizeImage *= 4;
		mydata->infohead.biHeight *= 2;
		mydata->infohead.biWidth *= 2; break; }
		default: std::cout << "��������ȷ��codeֵ" << std::endl; break;
		}
	}
	void Crop(int x1, int y1, int x2, int y2) //�ü���(x1,y1)����(x2,y2)
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
				mydata->infohead.biWidth = ((mydata->infohead.biWidth * mydata->infohead.biBitCount) / 8 + 3) / 3;	//������
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
			cout << "��������ȷ������" << endl;
	}
	void Rotate(int degree)			  //��ת��90�ȵ�������
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
			std::cout << "�����degreeֵ������Ҫ��" << std::endl;
	}
	void Transpose() 					  // ת��
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
		//�ͷŸ���ʱ����
		for (int i = 0; i < mydata->height; i++)
			delete[]temp_data[i];
		delete[]temp_data;
	}
	void Reshape(int h, int w) 		  //��Ԫ���������������£�����������б�Ϊ���������Ĵ�С
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
		//�ͷŸ���ʱ����
		for (int i = 0; i < mydata->height; i++)
			delete[]temp_data[i];
		delete[]temp_data;
	}

	bool IsEmpty()			// �ж��Ƿ�Ϊ�վ���
	{
		if (mydata->data[mydata->height - 2][mydata->width - 2])
			return false;
		else
			return true;
	}
	bool IsSquare()		// �жϾ����Ƿ�Ϊ����
	{
		return (mydata->height == mydata->width);
	}
	Mat<T>  MajorDiagonal()// �����Խ����ϵ�Ԫ�أ����һ��N��1�еľ���NΪ���Խ�����Ԫ�صĸ���
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
	Mat<T>  MinorDiagonal()// �󸱶Խ����ϵ�Ԫ�أ����һ��N��1�еľ���NΪ���Խ�����Ԫ�صĸ���
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
	Mat<T> Row(int n)// ���ؾ���ĵ�n���ϵ�Ԫ�أ����һ��1��N�еľ��������NΪ��n����Ԫ�صĸ���
	{
		T**temp = new T*[1];
		temp[0] = new T[mydata->width];
		int N = 0;
		for (int i = 0; i < mydata->width; i++)
			temp[0][N++] = mydata->data[n - 1][i];
		Mat m(temp, 1, mydata->width);
		return m;
	}
	Mat<T> Column(int n)// ���ؾ���ĵ�n���ϵ�Ԫ�أ����һ��N��1�еľ��������NΪ��n����Ԫ�صĸ���
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
	void Cat(Mat<T> &m, int code)  // ��m�뵱ǰ�������ƴ�ӣ�code����ƴ�ӵķ�ʽ
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
	void CopyTo(Mat<T> &m)		   // �������Ƹ�m��������
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
	Mat<T> Clone() 			   // �ӵ�ǰ���󿽱�����һ���µľ���������
	{
		Mat<T> temp;
		this->CopyTo(temp);
		return temp;
	}

	Mat<double> Normalize()//������Ԫ�ص�ֵ�任��0-1��Χ�ڣ���double���͵�Mat���������ע�⣺�����������޷�����Mat<double>���͵Ķ����˽�г�Աdata����Ҫ������At�������ĳ��Ԫ�ء�
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

	Mat<T>& operator=(const Mat<T> &m)  //���ظ�ֵ���������ɶ����ĸ�ֵ��ʹ�����ü�������
	{
		m.mydata->num++;
		this->mydata = m.mydata;
		return *this;
	}
	bool operator==(const Mat<T> &m)    //�ж�����Mat�����Ƿ����
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
	friend Mat<T> operator+(const Mat<T> &lhs, const Mat<T> &rhs)  //��ӦԪ�ص���ֵ��ӣ�
	{
		Mat<T> temp(lhs);
		for (int i = 0; i < temp.mydata->height; i++)
			for (int j = 0; j < temp.mydata->width; j++)
				temp.mydata->data[i][j] += rhs.mydata->data[i][j];
		return temp;
	}
	friend Mat<T> operator-(const Mat<T> &lhs, const Mat<T> &rhs)  //��ӦԪ�ص���ֵ�����
	{
		Mat<T> temp(lhs);
		for (int i = 0; i < temp.mydata->height; i++)
			for (int j = 0; j < temp.mydata->width; j++)
				temp.mydata->data[i][j] -= rhs.mydata->data[i][j];
		return temp;
	}
	Mat<T>& operator++()  				//ǰ���Լӣ�
	{
		for (int i = 0; i < this->mydata->height; i++)
			for (int j = 0; j < this->mydata->width; j++)
				++this->mydata->data[i][j];
		return *this;
	}
	Mat<T>& operator--()  			    //ǰ���Լ���
	{
		for (int i = 0; i < this->mydata->height; i++)
			for (int j = 0; j < this->mydata->width; j++)
				--this->mydata->data[i][j];
		return *this;
	}
	Mat<T> operator ++(int) 			//�����Լӣ�
	{
		Mat<T> temp = *this;
		for (int i = 0; i < temp.mydata->height; i++)
			for (int j = 0; j < temp.mydata->width; j++)
				temp.mydata->data[i][j]++;
		return temp;
	}
	Mat<T> operator --(int)  			//�����Լ���
	{
		Mat<T> temp = *this;
		for (int i = 0; i < temp.mydata->height; i++)
			for (int j = 0; j < temp.mydata->width; j++)
				temp.mydata->data[i][j]--;
		return temp;
	}
	Mat<double> operator-()  			// ȡ����ע��Ҫ�Ѿ�������ݹ�����[0,1]���������1��
	{
		this->Normalize();
		for (int i = 0; i < this->mydata->height; i++)
			for (int j = 0; j < this->mydata->width; j++)
				this->mydata->data[i][j] = 1.0 - this->mydata->data[i][j];
		return *this;
	}


	friend Mat<T> operator+(Mat<T> &m, T num) //����Ԫ�ؼ���ͬһ��ֵ;
	{
		Mat<T> temp = m;
		for (int i = 0; i < temp.mydata->height; i++)
			for (int j = 0; j < temp.mydata->width; j++)
				temp.mydata->data[i][j] += num;
		return temp;
	}
	friend Mat<T> operator-(Mat<T> &m, T num) //����Ԫ�ؼ�ȥͬһ��ֵ;
	{
		Mat<T> temp = m;
		for (int i = 0; i < temp.mydata->height; i++)
			for (int j = 0; j < temp.mydata->width; j++)
				temp.mydata->data[i][j] -= num;
		return temp;
	}
	friend Mat<T> operator*(Mat<T> &m, T num) //����Ԫ�س���ͬһ��ֵ;
	{
		Mat<T> temp = m;
		for (int i = 0; i < temp.mydata->height; i++)
			for (int j = 0; j < temp.mydata->width; j++)
				temp.mydata->data[i][j] *= num;
		return temp;
	}
	friend Mat<T> operator/(Mat<T> &m, T num) //����Ԫ�س���ͬһ��ֵ;
	{
		Mat<T> temp = m;
		for (int i = 0; i < temp.mydata->height; i++)
			for (int j = 0; j < temp.mydata->width; j++)
				temp.mydata->data[i][j] /= num;
		return temp;
	}
	
	//���⣬����Ԫ������д��һ��T���͵�����һ��Mat����ļ�,��,��,��
	friend Mat<T> operator+(T num, Mat<T> &m) //����Ԫ�ؼ���ͬһ��ֵ;
	{
		Mat<T> temp = m;
		for (int i = 0; i < temp.mydata->height; i++)
			for (int j = 0; j < temp.mydata->width; j++)
				temp.mydata->data[i][j] += num;
		return temp;
	}
	friend Mat<T> operator-(T num, Mat<T> &m) //����Ԫ�ؼ�ȥͬһ��ֵ;
	{
		Mat<T> temp = m;
		for (int i = 0; i < temp.mydata->height; i++)
			for (int j = 0; j < temp.mydata->width; j++)
				temp.mydata->data[i][j] -= num;
		return temp;
	}
	friend Mat<T> operator*(T num, Mat<T> &m) //����Ԫ�س���ͬһ��ֵ;
	{
		Mat<T> temp = m;
		for (int i = 0; i < temp.mydata->height; i++)
			for (int j = 0; j < temp.mydata->width; j++)
				temp.mydata->data[i][j] *= num;
		return temp;
	}
	friend Mat<T> operator/(T num, Mat<T> &m) //����Ԫ�س���ͬһ��ֵ;
	{
		Mat<T> temp = m;
		for (int i = 0; i < temp.mydata->height; i++)
			for (int j = 0; j < temp.mydata->width; j++)
				temp.mydata->data[i][j] /= num;
		return temp;
	}

	Mat<T> gray2bw(T t) 					//�Ը�����ֵt���ж�ֵ�������ؽ������
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

	friend void Swap(Mat<T> &a, Mat<T> &b)//ʹ����Ԫ������������Mat����
	{
		Mat<T> temp = a;
		a.mydata = b.mydata;
		b.mydata = temp.mydata;
	}


private:
	// �Լ�ʵ��һ���ṹ�壬���洢��������������������ü���������ָ��
	struct myData
	{
		BITMAPFILEHEADER filehead;
		BITMAPINFOHEADER infohead;
		int height;
		int width;
		int M_max;
		int M_min;
		T** data;
		int num;	//���ü���
	};
	// ������Ҫ����ָ��ýṹ���ָ����Ϊ���ݳ�Ա
	myData* mydata;
};
#endif // !MAT_HPP