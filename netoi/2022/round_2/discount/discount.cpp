#include <iostream>
#include <algorithm>

using namespace std;

long long ar[123460] = {0}, dp[123460];

int main()
{
	int n;
	cin>>n;
	for (int i=0;i<n;++i) cin>>ar[i];
	sort(ar, ar+n);
	dp[0] = ar[0];
	dp[1] = ar[1]+ar[0];
	dp[2] = ar[2]+ar[1];
	dp[3] = ar[3]+ar[2]+ar[0];
	dp[4] = min(ar[4]+ar[3]+ar[2], ar[4]+ar[3]+dp[1]);
	for (int i=5;i<n;++i) {
		dp[i] = min(ar[i]+ar[i-1]+ar[i-2]+dp[i-5], ar[i]+ar[i-1]+dp[i-3]);
	}
	cout<<dp[n-1]<<'\n';
}
