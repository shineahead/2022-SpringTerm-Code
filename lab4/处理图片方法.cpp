#include<iostream>
#include<Windows.h>
using namespace std;

int main1()
{
	FILE *fp;
	if (fopen_s(&fp, "Fruits_480x511.bmp", "rb") != 0)
	{
		cout << "can not open the file!" << endl;
		exit(0);
	}

	long height, width;
	BITMAPFILEHEADER filehead;
	BITMAPINFOHEADER infohead;

	fread(&filehead, sizeof(BITMAPFILEHEADER), 1, fp);//�ļ�ͷ
	fread(&infohead, sizeof(BITMAPINFOHEADER), 1, fp);//��Ϣͷ
	width = infohead.biWidth;
	height = infohead.biHeight;
	cout << "Width = " << width << " Height = " << height << endl;

	//��ȱ�Ϊ�ܱ�4�����ķ���
	width = ((width * infohead.biBitCount) / 8 + 3);
	width = width / 3;

	cout << "��Ƭ��������֮��Ŀ�͸��ǣ�" << endl;
	cout << "width = " << width << " height = " << height << endl;

	char *bmpbuff = new char[width * height * 3];
	fread(bmpbuff, sizeof(char), width * height * 3, fp);
	fclose(fp);

	//д���ļ���Ϣ
	FILE *fp2;
	if (fopen_s(&fp2, "out.bmp", "wb") != 0)
	{
		cout << "can not open the file!" << endl;
		exit(0);
	}
	fwrite(&filehead, sizeof(BITMAPFILEHEADER), 1, fp2);
	fwrite(&infohead, sizeof(BITMAPINFOHEADER), 1, fp2);
	char *outbmp = bmpbuff;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width * 3; j++)		//3��ʾ����������ͨ������ģ�ռ�����ֽ�
			fwrite(outbmp++, 1, 1, fp2);
	}
	fclose(fp2);
	delete[]bmpbuff;		//�ͷ��ڴ�ռ�

	cout << "ͼƬд��ɹ�!" << endl;
	system("pause");
	return 0;
}