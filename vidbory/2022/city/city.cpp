//#include <bits/stdc++.h>

#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

struct City
{
	vector<int> in;
	vector<int> out;
};/*

bool check(int n, int na, vector<int> &a, vector<int> &nr, vector<int> &nrr, vector<City> &roads) 

void delete_roads(int n, vector<int> &a, vector<int> &nr, vector<int> &nrr, vector<City> &roads) 
{
	int x = a[0];
	if (nr[x]>1) {
		int nr0 = nr[x];
		for(int i=1;i<nr[x];++i) {
			swap(roads[x].out[0], roads[x].out[i])
			if (nrr[x]>1) {

			}
		}
	}
}
*/
int main()
{
	int n, m;
	cin>>n>>m;
	vector<City> roads(n);
	vector<int> nr(n, 0), nrr(n, 0);
	for(int i=0;i<m;i++){
		int a,b;
		cin>>a>>b;
		a--;
		b--;
		if (a != b && find(roads[a].out.begin(), roads[a].out.end(), b) == roads[a].out.end()) {
			roads[a].out.push_back(b);
			roads[b].in.push_back(a);
			nr[a]++;
			nrr[b]++;
		}
	}
	bool flag = true;
	vector<int> a(n), a1;
	for(int i=0;i<n;i++) {a[i] = i;}
	a1.reserve(11);
	int pna = -1, na = n; 
	while (!a.empty()) {
		a1.clear();
		if (na == pna) {
			int x = a[0];
			if (nr[x]>1){
				int y = roads[x].out[0];
				nr[x]--;
				nrr[y]--;
				roads[y].in.erase(find(roads[y].in.begin(), roads[y].in.end(), x));
				roads[x].out.erase(find(roads[x].out.begin(), roads[x].out.end(), y));
			} else {
				int y = roads[x].in[0];
				nrr[x]--;
				nr[y]--;
				roads[y].out.erase(find(roads[y].out.begin(), roads[y].out.end(), x));
				roads[x].in.erase(find(roads[x].in.begin(), roads[x].in.end(), y));
			}
		}
		for (auto it=a.begin();it!=a.end();it++) {
			int i = (*it);
			if (nr[i] == 0 || nrr[i] == 0) {
				flag = false;
				break;
			}
			bool flag1 = false, f = true;
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
					f = false;
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
			if (!flag) {break;}
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
					if (f){
						a1.push_back(i);
					}
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
			if (!flag) {break;}
		}
		if (!flag) {break;}
		a.clear();
		a = a1;
		pna = na;
		na = a.size();
		a1.clear();
//		a1.reserve(11);
	}
//	cout<<"x\n";
	if (flag) {
		vector<int> q(n+1); 
		q[0] = 0;
		int x = roads[0].out[0], y = 1;
		q[y] = x;
		y++;
		while (x!=0) {
			x = roads[x].out[0];
			q[y] = x;
			y++;
		}
		if (y != n+1) {
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
