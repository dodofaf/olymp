#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include <string>
#include <random>

using namespace std;

int main()
{
	string line;
	fstream sin("maximum.in", sin.in);
	fstream sout("maximum.out", sout.out);
	getline(sin, line);
	istringstream iss(line);
	int n;
	iss>>n;
	getline(sin, line);
	istringstream iss1(line);
	vector<int> a(n+1);
	for (int i=0;i<n;i++) {
		iss1>>a[i];
	}
	a[n] = 0;
	int max_n = 0, n_bef_f = 0, n_af_l = 0, ind_f = -1, ind_l = -1, cnt = 0, r = -1, l, znak = 1, st = 0;
	for (int i=0;i<=n;i++) {
		if (a[i] == 2 || a[i] == -2) {
			cnt++;
			if (ind_f == -1) {
				n_bef_f++;
			}
			n_af_l++;
		}
		if (a[i] < 0) {
			znak *= -1;
			if (ind_f == -1) {
				ind_f = i;
			}
			ind_l = i;
			n_af_l = 0;
			if (a[i] == -2) {
				n_af_l++;
			}
		}
		if (a[i] == 0) {
			if (znak == 1) {
				if (cnt>max_n) {
					max_n = cnt;
					l = st+1;
					r = i;
				}
			} else {
				if (n_bef_f>=n_af_l) {
					if (cnt-n_af_l>max_n && st<ind_l) {
						max_n = cnt-n_af_l;
						l = st+1;
						r = ind_l;
					}
				} else {
					if (cnt-n_bef_f>max_n && ind_f+2<i) {
						max_n = cnt-n_bef_f;
						l = ind_f+2;
						r = i;
					}
				}
			}
			ind_f = -1;
			ind_l = -1;
			znak = 1;
			cnt = 0;
			n_bef_f = 0;
			n_af_l = 0;
			st=i+1;
		}
	}
	if (r == -1) {
		for (int i=0;i<n;i++) {
			if (a[i] == 1) {
				r = i+1;
				l = i+1;
				break;
			}
		}
		if (r == -1) {
			for (int i=0;i<n;i++) {
				if (a[i] == 0) {
					r = i+1;
					l = i+1;
					break;
				}
			}
		}
	}
	sout<<l<<' '<<r<<"\n";
}
