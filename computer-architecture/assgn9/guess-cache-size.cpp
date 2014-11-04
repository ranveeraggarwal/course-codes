#include <iostream>
#include <stdlib.h>
#include <sys/time.h>

using namespace std;

int main(int argc, char const *argv[])
{
	int guess_size = atoi(argv[1]);
	for (int i = 0; i < 27; ++i)
	{
		int *arr = new int[guess_size];
		int index = 0;
		struct timeval tim, tim1;
		double t1, t2;
		int j;
		gettimeofday(&tim, NULL);
		t1 = 1000000.0*tim.tv_sec + tim.tv_usec;
		for (j = 0; j < 100000; j++)
		{
			arr[index] = 0;
			index = (index + 97)%guess_size;
		}
		gettimeofday(&tim1, NULL);
		t2 = 1000000.0*tim1.tv_sec + tim1.tv_usec;
		cout << i << ", " << (t2 - t1)/100<< endl;
		guess_size = guess_size*2;
	}
}