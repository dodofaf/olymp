#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include <string>
#include <set>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cassert>

using namespace std;


auto cmp1 = [](const vector<int> &a, const vector<int> &b)
{
    return a[0] < b[0] || (a[0] == b[0] && a[1] < b[1]) || (a[0] == b[0] && a[1] == b[1] && a[2] < b[2]);
};

auto cmp2 = [](const vector<int> &a, const vector<int> &b)
{
    return a[1] < b[1] || (a[1] == b[1] && a[2] < b[2]);
};

int random(int m) 
{
	return rand() % m + 1;
}

void bf(int k, int n, vector<vector<int>> &seg)
{
	int res = 2e9;
	vector<int> q(k), ress;
	for (int i=0;i<k;i++) {
		q[i] = i;
	}
	while (q[k-1] != n) {
		int mn = 1e9, mx = 0;
		for (int i=0;i<k;i++) {
			assert(q[k-2]<n);
			assert(q[i]<n);
			if (seg[q[i]][0]<mn) {
				mn = seg[q[i]][0];
			}
			if (seg[q[i]][1]>mx) {
				mx = seg[q[i]][1];
			}
		}
		if (res>mx-mn) {
			res = mx-mn;
			ress = q;
		}
		int x = k-1;
		while (q[x] == n-k+x && x>0) {
			x--;
		}
		q[x]++;
		for (int i=x+1;i<k;i++) {
			q[i] = q[i-1]+1;
		}
	}
	cout<<"bf"<<res<<"\n";
	for (int i=0;i<k;i++) {
//		cout<<ress[i]<<' ';
	}
	cout<<"\n";
}


int main()
{ 
#if 1
	int t = time(NULL);
//	t = 1661849431;
//	t = 1661849016;
//	t = 1661848662;
//	t = 1661848663;
//	t = 1661800600;
//	t = 1661773188;
	cout<<t<<"\n";
	srand(t);
	int n = 10000, k = random(n);

	cout<<n<<' '<<k<<"\n\n";
	set<vector<int>, decltype(cmp1)> seg_sort_by_mn(cmp1);
	vector<vector<int>> seg(n);
	for (int i=0;i<n;i++) {
		vector<int> a(3);
		a[2] = i;
		int x = random(20), y = random(20);
//		cout<<x<<' '<<y<<"\n";
		a[0] = min(x, y);
		a[1] = max(x, y);
		seg[i] = a;
		seg_sort_by_mn.insert(a);

	}
	fstream sout("pencil.out", sout.out);
#else
	fstream sin("pencil.in", sin.in);
	fstream sout("pencil.out", sout.out);
	string line;
	getline(sin, line);
	istringstream iss(line);
	int n, k;
	iss>>n>>k;
	set<vector<int>, decltype(cmp1)> seg_sort_by_mn(cmp1);
	vector<vector<int>> seg(n);
	for (int i=0;i<n;i++) {
		getline(sin, line);
		istringstream iss1(line);
		vector<int> a(3);
		a[2] = i;
		a[0] = 1e9;
		int x;
		while (iss1>>x) {
			if (x<a[0]) {
				a[0] = x;
			}
			if (x>a[1]) {
				a[1] = x;
			}
		}
		seg[i] = a;
		seg_sort_by_mn.insert(a);

	}
#endif
//	bf(k, n, seg);
//	for (int i=0;i<n;i++) {
//		cout<<seg[i][0]<<' '<<seg[i][1]<<"\n";
//	}
	set<vector<int>, decltype(cmp2)> sort_by_mx(cmp2);
	for (auto i=seg_sort_by_mn.begin();i!=seg_sort_by_mn.end();i++) {
		sort_by_mx.insert((*i));
	}
	int res = 2e9;
//	vector<int> q(k), ress;
	for(auto i=seg_sort_by_mn.begin();i!=seg_sort_by_mn.end() && n>=k;i++) {
//		cout<<"1\n";
		sort_by_mx.erase((*i));
//		q[0] = (*i)[2];
//		cout<<"2\n";
		n--;
//		cout<<"3\n";
		if (k > 1) {
			auto it = sort_by_mx.begin();
//		cout<<"4\n";
			for (int j=0;j<k-2;j++) {
				it++;
			}
			int mn = (*i)[0];
			int mx = max((*it)[1], (*i)[1]);
			if (res>mx-mn) {
				res = mx-mn;
			}
		} else {
			int mn = (*i)[0];
			int mx = (*i)[1];
			if (res>mx-mn) {
				res = mx-mn;
			}
		}
	}
	cout<<res<<"\n";
	sout<<res;
}
