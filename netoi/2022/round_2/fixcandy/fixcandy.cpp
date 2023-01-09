#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

long long bf(long long ar[], long long n, long long k, long long l)
{
	long long cnt = 0, t = 0;
	while (cnt < l) {
		++t;
		for (int i=0;i<n;++i) {
			++ar[i];
			if (ar[i] == k) {
				ar[i] = 0;
				++cnt;
			}
		}
	}
	long long sum = 0;
	for (int i=0;i<n;++i) {
		sum+=ar[i];
	}
	long long mn = sum, ind = 0;
	for (int i=1;i<k;++i) {
		sum+=n;
		for (int j=0;j<n;++j) {
			++ar[j];
			if (ar[j] == k) sum-=k;
		}
		if (sum<mn) {
			mn = sum;
			ind = i;
		}
	}
	return t+ind;
}



long long ar[1000001] = {0};
//long long b[1000005] = {0};

int main()
{
	ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

	long long n, k, l;
	cin>>n>>k>>l;
	long long mn, sum = 0; 
	for (long long i=0;i<n;++i) {
		cin>>ar[i];
//		b[i] = ar[i];
		sum+=ar[i];
	}
	sort(ar, ar+n);
//	cout<<"bf = "<<bf(b, n, k, l)<<'\n';
	long long mn_ind = 0, d = 0, f = l%n;
	long long res = 0;
	bool flag = l<n;
	ar[n] = k;
	if (l>=n) {
		sum = 0;
		res = k-ar[0];
		long long mn = ar[0]; 
		for (long long i=0;i<n;++i) {
			ar[i] -= mn;
			sum+=ar[i];
		}
		l-=n;
	}
	mn = sum;
	for (long long i=n-1;i>-1;--i) {
		sum+=n*(ar[i+1]-ar[i])-k;
		while (i>0 && ar[i-1] == ar[i]) {
			sum-=k;
			--i;
		}
		if (mn>sum) mn = sum, mn_ind = k-ar[i], d = n-i;
		else if (mn == sum && d<f && n-i>=f) mn_ind = k-ar[i], d = n-i;
	}
	res += (l/n)*k + (f>d)*k + mn_ind;
	cout<<res<<'\n';
}
