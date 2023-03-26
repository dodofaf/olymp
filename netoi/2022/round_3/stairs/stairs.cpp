#include <iostream>
#include <cmath>

using namespace std;

int dp[1000005][2];

int main()
{
	int n, k;
	cin>>n>>k;
//	cout<<n<<' '<<k<<'\n';
	if (n == 2) cout<<"0\n";
	else {
		dp[n-1][0] = 1;
		dp[n-1][1] = 1;
		dp[n-2][0] = 1;
		dp[n-2][1] = 1e9;
		dp[n-3][0] = 3;
		dp[n-3][1] = 2;
		for (int i=0;i<k;++i) {
			int x;
			cin>>x;
			dp[x-1][0] = 1e9;
			dp[x-1][1] = 1e9;
		}
		for (int i=n-4;i>-1;--i){
			if (dp[i][0] == 1e9) continue;
			dp[i][0] = min(dp[i+1][0], dp[i+1][1])+1;
			dp[i][1] = min(dp[i+2][0], dp[i+3][0])+1;
		}
		cout<<n-min(dp[0][0], dp[0][1])-k<<'\n';
//		for (int i=0;i<n;++i) cout<<dp[i][0]<<' '<<dp[i][1]<<'\n';
	}
}
