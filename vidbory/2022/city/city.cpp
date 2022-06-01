//#include <bits/stdc++.h>

#include <vector>
#include <iostream>
#include <algorithm>
#include <random>

using namespace std;

int random(int m)
{
    return rand()%m;
}


struct City
{
	vector<int> in;
	vector<int> out;
};

int main()
{
	int n, m;
	long long t = time(NULL);
	t *=t;
	t = 2736013751257260049;
	srand(t);
	cout<<"t="<<t<<endl;
//	cin>>n>>m;
	n = random(9)+2;
	m = random(min(2*n,n+20))+1;
	cout<<n<<' '<<m<<"\n";
	vector<City> roads(n);
	vector<int> nr(n, 0), nrr(n, 0);
	for(int i=0;i<m;i++){
		int a,b;
//		cin>>a>>b;
		a = random(n)+1;
		b = random(n)+1;
		while(b==a) {b = random(n)+1;}
		cout<<a<<' '<<b<<"\n";
		a--;
		b--;
		if (find(roads[a].out.begin(), roads[a].out.end(), b) == roads[a].out.end()) {
			roads[a].out.push_back(b);
			roads[b].in.push_back(a);
			nr[a]++;
			nrr[b]++;
		}
	}
	cout<<"x\n";
	bool flag = true;
	vector<int> a(n), a1;
	for(int i=0;i<n;i++) {a[i] = i;}
	a1.reserve(11);
	while (!a.empty()) {
		for (auto it=a.begin();it!=a.end();it++) {
			int i = (*it);
			if (nr[i] == 0 || nrr[i] == 0) {
				flag = false;
				break;
			}
			bool flag1 = false;
			if (nr[i]>1) {
				int ind = -1;
				for (int j=0;j<nr[i];j++) {
					if (nrr[roads[i].out[j]] == 1) {
						if (!flag1) {
							flag1 = true;
							ind = j;
						} else {
							flag = false;
							break;
						}
					}
				}
				if (!flag) {break;}
				if (ind == -1) {
					a1.push_back(i);
				} else {
					ind = roads[i].out[ind];
					for (int j=0;j<nr[i];j++) {
						if (roads[i].out[j] != ind) {
							nrr[roads[i].out[j]]--;
							roads[roads[i].out[j]].in.erase(find(roads[roads[i].out[j]].in.begin(), roads[roads[i].out[j]].in.end(), i));
						}
					}
					nr[i] = 1;
					roads[i].out.resize(1);
					roads[i].out[0] = ind;
				}
			}
			flag1 = false;
			if (nrr[i]>1) {
				int ind = -1;
				for (int j=0;j<nrr[i];j++) {
					if (nr[roads[i].in[j]] == 1) {
						if (!flag1) {
							flag1 = true;
							ind = j;
						} else {
							flag = false;
							break;
						}
					}
				}
				if (!flag) {break;}
				if (ind == -1) {
					a1.push_back(i);
				} else {
					ind = roads[i].in[ind];
					for (int j=0;j<nrr[i];j++) {
						if (roads[i].in[j] != ind) {
							nr[roads[i].in[j]]--;
							roads[roads[i].in[j]].out.erase(find(roads[roads[i].in[j]].out.begin(), roads[roads[i].in[j]].out.end(), i));
						}
					}
					nrr[i] = 1;
					roads[i].in.resize(1);
					roads[i].in[0] = ind;
				}
			}
		}
		if (!flag) {break;}
		a = a1;
		a1.clear();
		a.reserve(11);
		a1.reserve(11);
	}
	if (flag) {
		vector<int> q(n+1, -1), tick(n, 0), nr0(nr);
		int y = 1;
		q[0] = 0;
		int x;
		while(y != 0 && q[n] != 0) {
			x = q[y-1];
			int j = nr[x]-1;
			while(j != -1 && tick[roads[x].out[j]] != 0) {
				j--;
			}
			if (j!= -1) {
				q[y] = roads[x].out[j];
				nr[x]--;
				tick[q[y]]=1;
				y++;
			} else {
				y--;
				tick[q[y]] = 0;
				nr[q[y]] = nr0[q[y]];
			}
		}
		if (y == 0) {
			cout<<"NO\n";
		} else {
			cout<<"YES\n";
			for (int i=0;i<=n;i++) {
				cout<<q[i]+1<<' ';
			}
			cout<<"\n";
		}
	} else {
		cout<<"NO\n";
	}
}
