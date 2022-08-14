#include<iostream>
using namespace std;

int main2()
{
	int ***p = new int **[2];
	for (int i = 0; i < 2; i++)
	{
		p[i] = new int *[3];
		for (int j = 0; j < 3; j++)
			p[i][j] = new int[4];
	}

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			for (int k = 0; k < 4; k++)
				cin >> p[i][j][k];
		}
	}

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			for (int k = 0; k < 4; k++)
				cout << p[i][j][k] << " ";
		}
		cout << endl;
	}

	for (int i = 0; i < 2; i++)		//É¾³ýÖ¸ÕëÊý×é
	{
		for (int j = 0; j < 3; j++)
			delete []p[i][j];
		delete[]p[i];
	}
	delete[]p;
	system("pause");
	return 0;
}

