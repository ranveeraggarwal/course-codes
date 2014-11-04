#include <iostream>
using namespace std;
#define SIZE 100

int main()
{
	double x[SIZE][SIZE], y[SIZE][SIZE], z[SIZE][SIZE];
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			x[i][j] = 0;
			y[i][j] = 0;
			z[i][j] = 0;
			cout << "1 " << &x[i][j] << endl;
			cout << "1 " << &y[i][j] << endl;
			cout << "1 " << &z[i][j] << endl;
		}
		y[i][i] = 2;
		z[0][i] = i;
		cout << "1 " << &y[i][i] << endl;
		cout << "1 " << &z[0][i] << endl;
	}

	for (int i=0; i<SIZE; i++)
	{
		for (int j=0; j<SIZE; j++)
		{
			for (int k=0; k<SIZE; k++)
			{
				x[i][j] = x[i][j] + y[i][k] * z[k][j];
				cout << "0 " << &y[i][k] << endl;
				cout << "0 " << &z[k][j] << endl;
				cout << "0 " << &x[i][j] << endl;
				cout << "1 " << &x[i][j] << endl;
			}
		}
	}
}