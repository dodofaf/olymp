#include <iostream>
#include <math.h>

using namespace std;

int cnt[10000] = {0};

int main()
{
	long long n, res = 1;
	cin>>n;
	for (int i=2;i<=n;++i) {
		int x = i;
		while (!(x&1)) {
			cnt[2]++;
			x>>=1;
		}
		for (int j=3;j<=sqrt(x);j+=2) {
			while (x%j==0) {
				cnt[j]++;
				x/=j;
			}
		}
		if (x!=1) cnt[x]++;
	}
	for (int i=2;i<=n;++i) {
		res = (res*(cnt[i]+1))%1000000007;
	}
	cout<<res<<'\n';
}