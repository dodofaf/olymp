#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main()
{
	string line;
	fstream sin("strings.in", sin.in);
	fstream sout("strings.out", sout.out);
	getline(sin, line);
	istringstream iss(line);
	int n;
	iss>>n;
	string s;
	getline(sin, s);
	vector<int> dp(n, 0);
	for (int i=n-2;i>-1;i--) {
		int mx = 0;
		for (int j=n-1;j>i;j--) {
			int x = (j-i)*abs((int)s[i]-(int)s[j]) + dp[j];
			if (x>mx) {
				mx = x;
			}
			dp[i] = mx;
		}
	}
	sout<<dp[0]<<"\n";
}
