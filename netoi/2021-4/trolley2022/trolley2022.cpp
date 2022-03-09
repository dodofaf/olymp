#include <bits/stdc++.h>

using namespace std;

struct Zapyt
{
	int l;
	int r;
};

void perebir(int n, int m, int k, const vector<int> &zup, const vector<Zapyt> &zapyty)
{
	vector<int> day(k, k+1);
	for (int i=0;i<n;i++) {
		day[zup[i]] = 0;
	}
	for(int i=0;i<n;i++) {
		int x = zup[i];
		while(day[x]+1 < day[(x-1+k)%k]) {
			day[(x-1+k)%k] = day[x]+1;
			x = (x-1+k)%k;
		}
	}
	for (int i=0;i<m;i++) {
		long long cnt = 0;
		for(int j=zapyty[i].l;j<=zapyty[i].r;j++) {
			cnt += day[j];
		}
		cout<<cnt<<' ';
	}
	cout<<endl;
}

void ver_1(int n, int m, int k, const vector<long long> &zup, const vector<Zapyt> &zapyty)
{
	for (int i=0;i<m;i++) {
		long long cnt = 0;
		bool b1 = true, b2 = true;
		int l = zapyty[i].l;
		int r = zapyty[i].r;
		for (int j=0;j<n;j++) {
			if (zup[j] >= l) {
				if (b1){
					if (zup[j] < r) {
						cnt += (zup[j] - l)*(zup[j] - l + 1)/2;
						b1 = false;
					} else {
						cnt += (zup[j] - l)*(zup[j] - l + 1)/2 - (zup[j] - r)*(zup[j] - r - 1)/2;
						b2 = false;
						b1 = false;
						break;
					}
				} else {
					if (zup[j] < r) {
						cnt += (zup[j] - zup[j-1])*(zup[j] - zup[j-1] - 1)/2;
					} else {
						cnt += (zup[j] - zup[j-1])*(zup[j] - zup[j-1] - 1)/2 - (zup[j] - r)*(zup[j] - r - 1)/2;
						b2 = false;
						break;
					}
				}
			}
		}
		if (b2 && !b1) {
			cnt += (zup[0] + k - zup[n-1])*(zup[0] + k - zup[n-1] - 1)/2 - (zup[0] + k - r)*(zup[0] + k - r - 1)/2;
		}
		if (b1 && b2) {
			cnt+= (zup[0] + k - l)*(zup[0] + k - l - 1)/2 - (zup[0] + k - r)*(zup[0] + k - r - 1)/2;
		}
		cout<<cnt<<' ';
	}
	cout<<endl;
}

int main()
{
	int n, m, k;
	cin>>n>>m>>k;
	vector<long long> zup(n);
	for (int i=0;i<n;i++) {
		cin>>zup[i];
		zup[i]--;
	}
	vector<Zapyt> zapyty(m);
	for (int i=0;i<m;i++) {
		cin>>zapyty[i].l>>zapyty[i].r;
		zapyty[i].l--;
		zapyty[i].r--;
	}
	ver_1(n, m, k, zup, zapyty);
}