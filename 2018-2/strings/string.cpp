#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

int random(int m) 
{
	return rand() % m;
}

void bf(int n, string &s)
{
 //   cout<<(int)'w'-(int)'m';
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
    int x=0;
    cout<<x<<' '<<s[x]<<' ';
    while (x!=n-1) {
        x = dp1[x];
        cout<<x<<' '<<s[x]<<' ';
    }
    cout<<"\n";
}

struct Letter
{
	bool tick = false;
//	char ch;
	vector<int> ends;
	vector<int> res;
	int ind = 0;
	int cnt = 0;
};

int main()
{
#if 0
	int  t = time(NULL);
	t = 1662215361;
	cout<<t<<"\n";
	srand(t);
	int n = 8;

	string s = "";
	for (int i=0;i<n;i++) {
		s = s + (char)(random(26) + (int)'a');
	}
    for (int i=0;i<n;i++) {
        cout<<s[i];
    }
    cout<<"\ns\n";
	fstream sout("strings.out", sout.out);
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

	bf(n, s);

	vector<Letter> let(26);
	int cnt = 0;
	for(int i=0;i<n-1;i++) {
		if (s[i] != s[i+1]) {
			cnt++;
			int id = (int)s[i] - (int)'a';
			let[id].tick = true;
//			let[id].ch = s[i];
			let[id].ends.push_back(i);
			let[id].res.push_back(0);
			let[id].cnt++;
		}
	}
	cnt++;
	int id = (int)s[n-1] - (int)'a';
	let[id].tick = true;
//	let[id].ch = s[i];
	let[id].ends.push_back(n-1);
	let[id].res.push_back(0);
	let[id].cnt++;
	if (cnt == 1) {
		cout<<"0\n";
		sout<<"0\n";
	} else {
		id = (int)s[0] - (int)'a';
		if (let[id].ends[0] == 0) {
			let[id].ind++;
			if (let[id].cnt == 1) {
				let[id].tick = false;
			}
		}
		int mn = n;
		int mn_ind = 0;
		for (int i=0;i<26;i++) {
			if (let[i].tick && i != id) {
				let[i].res[0] = let[i].ends[0]*abs(i-id);
				if (let[i].ends[0] < mn) {
					mn = let[i].ends[0];
					mn_ind = i;
				}
			}
		}
		int x = mn_ind;
		while (true) {
			if (let[x].ends[let[x].ind] == n-1) {
				cout<<let[x].res[let[x].ind]<<"\n";
				sout<<let[x].res[let[x].ind]<<"\n";
				break;
			}
			mn = n;
			for (int i=0;i<26;i++)
            {
				if (let[i].tick && i != x) {
					int res = (let[i].ends[let[i].ind]-let[x].ends[let[x].ind])*abs(i-x)+let[x].res[let[x].ind];
					let[i].res[let[i].ind] = max(res, let[i].res[let[i].ind]);
					if (let[i].ends[let[i].ind] < mn) {
						mn = let[i].ends[let[i].ind];
						mn_ind = i;
					}
				}
			}
			let[x].ind++;
			if (let[x].ind == let[x].cnt) {
				let[x].tick = false;
			}
			x = mn_ind;
		}
	}
}
