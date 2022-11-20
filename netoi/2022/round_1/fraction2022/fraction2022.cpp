#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

long long gcd(long long a, long long b)
{
	while (a!=0 && b!=0) {
		if (a>b) a = a%b;
		else b = b%a;
	}
	return a+b;
}

unsigned long long gcdd(unsigned long long a, unsigned long long b)
{
	while (a!=0 && b!=0) {
		if (a>b) a = a%b;
		else b = b%a;
	}
	return a+b;
}

long long min(long long a, long long b)
{
	if (a<b) return a;
	else return b;
}

int main()
{
	long long x, y, n, m;
	cin>>x>>y;
	if (y == -1) {
		n = x;
		m = 1;
		while (x>0) {
			m*=10;
			x/=10;
		}
		int g = gcd(n, m);
		cout<<n/g<<' '<<m/g<<'\n';
	} else if (x == -1) {
		n = y;
		m = 1;
		while (y>0) {
			m*=10;
			y/=10;
		}
		--m;
		int g = gcd(n, m);
		cout<<n/g<<' '<<m/g<<'\n';
	} else {
		unsigned long long x1 = x, x2 = x, y1 = y;
		long long m1 = 1, m2 = 1;
		while (y!=0) {
			m1*=10;
			y/=10;
		}
		while (x!=0) {
			m2*=10;
			x/=10;
		}
		x2 = ((x1*(m1/min(m1, m2)))%((m1-1)*(m2/min(m1, m2))))*min(m1, m2)+y1-x1;
		m = ((m1-1)%x2)*(m2%x2);
		int g = gcdd(x2, m);
		if ((x1/g)!=0) cout<<x1/g;
		long long res = ((x1%g)*m1+y1-x1)/g+m1;
		string s = to_string(res);
		int len = s.length();
		for (int i=1;i<len;++i) cout<<s[i];
		cout<<' ';
		if ((m1-1)/g!=0) cout<<(m1-1)/g;
		res = ((m1-1)%g)*m2/g+m2;
		s = to_string(res);
		len = s.length();
		for (int i=1;i<len;++i) cout<<s[i];
		cout<<'\n';
	}
}