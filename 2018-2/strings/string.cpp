#include <bits/stdc++.h>

using namespace std;

int random(int m) 
{
	return rand() % m;
}

void bf(int n, string &s)
{
	vector<int> dp(n, 0);
    vector<int> dp1(n, 0);
	for (int i=n-2;i>-1;i--) {
		int mx = 0;
		for (int j=n-1;j>i;j--) {
			int x = (j-i)*abs((int)s[i]-(int)s[j]) + dp[j];
			if (x>mx) {
				mx = x;
                dp1[i] = j;
			}
		}
        dp[i] = mx;
	}
	cout<<"dp"<<dp[0]<<"\n"; 
}

int main()
{
#if 0
	int  t = time(NULL);
//	t = 1662215361;
	cout<<t<<"\n";
	srand(t);
	int n = 100000;

	string s;
	for (int i=0;i<n;i++) {
		s = s + (char)(random(26) + (int)'a');
	}
//    for (int i=0;i<n;i++) {
//        cout<<s[i];
//    }
//    cout<<"\ns\n";
//	fstream sout("strings.out", sout.out);
#else
	string line;
	fstream sin("strings.in", sin.in);
	fstream sout("strings.out", sout.out);
	getline(sin, line);
	istringstream iss(line);
	int n;
	iss>>n;
	string s;
	getline(sin, s);
#endif

	//bf(n, s);

	vector<int> pref(n, 0);
	vector<vector<int>> best(26, vector<int>(26, -1));

	for (int i=0;i<26;++i) {
		best[i][(int)(s[0]-'a')] = 0;
	}
	for (int i=1;i<n;++i) {
		int ind = (int)s[i]-(int)'a';
		for (int j=0;j<26;j++) {
			if (best[ind][j] != -1) {
				pref[i] = max(pref[i], (i-best[ind][j])*abs(ind-j)+pref[best[ind][j]]);
			}
		}
		for (int j=0;j<26;j++) {
			if (best[j][ind] == -1 || (i-best[j][ind])*abs(ind-j)+pref[best[j][ind]] < pref[i]) {
				best[j][ind] = i;
			}
		}
	}
	sout<<pref[n-1]<<'\n';

}
