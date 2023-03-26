#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

bool check_string(int l, int r, int n,  vector<int> &q, string &line)
{
	int f = l, s = r, fq = 0, sq = n-1;
	bool flag = true;
	while (flag && s>f) {
		while (f == q[fq]) {
			f++;
			fq++;
		}
		while (s == q[sq]) {
			s--;
			sq--;
		}
		if (line[f] != line[s]) {
			flag = false;
		} else {
			s--;
			f++;
		}
	}
	return flag;
}

bool check(int l, int r, string &line)
{
	int f = l, s = r;
	bool flag = true;
	while (flag && s>f) {
		if (line[f] != line[s]) {
			flag = false;
		} else {
			s--;
			f++;
		}
	}
	return flag;
}

int main()
{
	fstream sin("string.in", sin.in);
	fstream sout("string.out", sout.out);
	string line, s;
	getline(sin, line);
	getline(sin, s);
	istringstream iss(s);
	int k;
	iss>>k;
	for (int z=0;z<k;z++) {
		getline(sin, s);
		istringstream iss1(s);
		int r, l;
		iss1>>l>>r;
		r--;
		l--;
		int n = r-l+1;
		int mx;
		string pal;
		int flag = check(l, r, line);
		if (flag) {
			for (int j=l;j<=r;j++) {
				sout<<line[j];
			}
			sout<<"\n";
		}
		for (int i=1;i<n && !flag;i++) {
			vector<int> q(i);
			for(int j=l;j<l+i;j++) {
				q[j]=j;
			}
			while (q[0] != r-i+2) {
				if (check_string(l, r, i, q, line)) {
					flag = true;
					int q_ind = 0;
					for (int j=l;j<=r;j++) {
						if (q_ind == i || j != q[q_ind]) {
							sout<<line[j];
						} else {
							q_ind++;
						}
					}
					sout<<"\n";
					break;
				}
				if (q[i-1] == r) {
					int x = i-1;
					while (q[x] == r+x-i+1 && x>0) {
						x--;
					}
					q[x]++;
					for (int j=x+1;j<i;j++) {
						q[j] = q[j-1]+1;
					}
				} else {
					q[i-1]++;
				}
			}
		}
	}
}
