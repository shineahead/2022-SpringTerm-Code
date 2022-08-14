#include<iostream>
#include<iomanip>
using namespace std;

int fun(int m)
{
	int i, t = m, sum = 0;
	do {
		if (sum >= 10)
		{
			t = sum;
			sum = 0;
		}
		while (t > 0)
		{
			sum += t % 10;
			t /= 10;
		}
	} while (sum >= 10 || sum == 0);
	return sum;
}

int main()
{
	int a[10][10] = { 0 }, i, j;
	for (i = 1; i < 10; i++)
		for (j = 1; j < 10; j++)
			a[i][j] = fun(i * j);

	for (i = 1; i < 10; i++)
	{
		for (j = 1; j < 10; j++)
		{
			cout << setw(3) << a[i][j];
		}
		cout << endl;
	}
	for (int p = 1; p < 10; p++)
	{
		cout << "µÚ" << p << "Àı:" << endl;
		for (i = 1; i < 10; i++)
			{
				for (j = 1; j < 10; j++)
				{
					if (a[i][j] == p)
						cout << " * ";
					else
						cout << "   ";
				}
				cout << endl;
			}
	}
	system("pause");
	return 0;
}