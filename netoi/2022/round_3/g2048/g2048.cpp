#include <iostream>
#include <cmath>

using namespace std;

int main()
{
	int res = 0;
	for (int i=0;i<16;++i) {
		int x;
		cin>>x;
		res+=(x*((int)log2(x)-1));
	}
	cout<<res<<'\n';
}
