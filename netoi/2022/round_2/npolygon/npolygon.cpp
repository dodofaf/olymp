#include <iostream>
#include <math.h>

using namespace std;

int main()
{
	long long n;
	cin>>n;
	long long res = -1, s = sqrt(n);
	if (!(n&1)) res = n-2;
	else for (int i=3;i<=s;i+=2) {
		if (n%i == 0) {
			res = n-i;
			break;
		}
	}
	cout<<res<<'\n';
}