#include <iostream>
#include <sstream>
#include <fstream>
#include <functional>
#include <random>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;


int random(int m) 
{
	return rand() % m + 1;
}

int main()
{
	int t = time(NULL);
	cout<<t<<'\n';
	srand(t);
	fstream sout("rand.tst", sout.out);
	long long n = 15, k = 1e1, l = random(5e1)+n;
	sout<<n<<' '<<k<<' '<<l<<'\n';
#if 1	
	for (int i=0;i<n;++i) {
		sout<<random(k)-1<<' ';
	}
#endif
#if 0	
	for (int i=0;i<n;++i) {
		sout<<random(k)-1<<' ';
	}
#endif
}
