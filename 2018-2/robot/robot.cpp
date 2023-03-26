#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include <string>
#include <set>

using namespace std;

int ar2[10000000] = {0};
int dp[10000000] = {0};

int ver_1(int ar[], int n, int k)
{
///	int itr = -1;
	for (int i=0;i<n;++i) ar2[i] = ar[i];
	if (k>1) {
		for (int i=n;i<2*n;++i) {
			ar2[i] = ar[2*n-i];
		}
		for (int i=2*n;i<k*n;++i) ar2[i] = ar2[i%(2*n)];
	}
//	for (int i=0;i<k*n;++i) cout<<ar2[i]<<' ';
//	cout<<'\n';
	//cout<<"1\n";
	for (int i=n*k-1;i>-1;--i) {
		int mx = 0;
		for (int j=i+1;j<n*k;++j) {
			if (ar2[j]>ar2[i] && mx<dp[j]) mx = dp[j];
		}
		dp[i] = mx+1;
		//cout<<"2\n";
	}
	//cout<<"3\n";
	int res = 0;
	for (int i=0;i<n;++i) {
		if(dp[i]>res) res = dp[i];
	}
	return res;
}

int ar[100000] = {0};

int main()
{
	string line;
	fstream sin("robot.in", sin.in);
//	fstream sin("2.tst", sin.in);
	fstream sout("robot.out", sout.out);
	getline(sin, line);
	istringstream iss(line);
	int n, k;
	iss>>n>>k;
	getline(sin, line);
	istringstream iss1(line);
	for (int i=0;i<n;++i) {
		iss1>>ar[i];
		--ar[i];
	}
//	cout<<ver_1(ar, n, k)<<'\n';
	sout<<ver_1(ar, n, k)<<'\n';
}