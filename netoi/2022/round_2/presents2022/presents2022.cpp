#include <iostream>
#include <algorithm>

using namespace std;

long long bf(long long n)
{
	long long cnt = 0;
	for (long long x=1;x<n;++x) {
		for (long long y=1;y<n && (n-2*x-y)>y;++y) {
		if (x!=y && (n-2*x-y)!=x) {
			++cnt;
			}
		}
	}
	return cnt;
}

long long intel_bf(long long n)
{
	long long cnt = 0;
	for (long long i=1;i<(n>>1);++i) {
		cnt += ((n-(i<<1))>>1) - ((n-(i<<1))>i) - (((n-(i<<1))&1)==0) + (((((n-(i<<1))&1)==0))&(i==((n-(i<<1))>>1)));
	}
	return cnt;
}

int main()
{
	long long n;
	cin>>n;
	long long res = ((n/2)*(n/2-1))/2-(n/3-(n%3==0))-(n%2==0)*((n/2)-1)+(((n/2)%2==0)&(n%2==0));
	if (n) cout<<res<<'\n';
	else cout<<"0/n";
}
