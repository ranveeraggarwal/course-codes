#include <iostream>
using namespace std;
#define SIZE 100

int main()
{
	double x[SIZE][SIZE], y[SIZE][SIZE], z[SIZE][SIZE], w[SIZE][SIZE];
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			x[i][j] = 0;
			y[i][j] = 0;
			//z[i][j] = 0;
			w[i][j] = 0;
			cout << "1 " << &x[i][j] << endl;
			cout << "1 " << &y[i][j] << endl;
			cout << "1 " << &w[i][j] << endl;
		}
		y[i][i] = 2;
		//z[0][i] = i;
		w[i][0] = i;
		cout << "1 " << &y[i][i] << endl;
		cout << "1 " << &z[i][0] << endl;
	}

	for (int i=0; i<SIZE; i++)
	{
		for (int j=0; j<SIZE; j++)
		{
			for (int k=0; k<SIZE; k++)
			{
				x[i][j] = x[i][j] + y[i][k] * w[j][k];
				cout << "0 " << &y[i][k] << endl;
				cout << "0 " << &w[j][k] << endl;
				cout << "0 " << &x[i][j] << endl;
				cout << "1 " << &x[i][j] << endl;
			}
		}
	}
}