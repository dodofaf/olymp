#include <bits/stdc++.h>

using namespace std;

static void swap(int &a, int &b)
{
	int t = a;
	a = b;
	b = t;
}

static int find_root(int x, vector<int> &seg, vector<int> &pseg)
{
	int s1 = seg[x];
	while(s1 != pseg[s1]) {
		s1 = pseg[s1];
	}
	int s2 = seg[x], t;
	while (s2 != s1) {
		t = pseg[s2];
		pseg[s2] = s1;
		s2 = t;
	}
	return s1;
}

void union_lists(int x, int y, vector<int> &seg, vector<list<int>> &segm)
{
	list<int> l;
	int s1 = seg[x], s2 = seg[y];
	if (s1 != s2) { 
		auto itr1 = segm[s1].begin(), itr2 = segm[s2].begin();
		while (itr1 != segm[s1].end() || itr2 != segm[s2].end()) {
			if (itr1 != segm[s1].end()) {
				if (itr2 != segm[s2].end()) {
					if ((*itr1) < (*itr2)) {
						l.push_back((*itr1));
						++itr1;
					} else {
						l.push_back((*itr2));
						seg[(*itr2)] = s1;
						++itr2;
					}
				} else {
					l.push_back((*itr1));
					++itr1;
				}
			} else {
				l.push_back((*itr2));
				seg[(*itr2)] = s1;
				++itr2;
			}
		}
		segm[s1] = l;
		segm[s2].clear();
	}
}

static void zap_3(int x, int n, vector<vector<int>> &zap, vector<int> &seg, vector<list<int>> &segm)
{
	for (int i=0;i<n;++i) {
		segm[i].clear();
		segm[i].push_back(i);
		seg[i] = i;
	}
	for (int i=0;i<=x;++i) {
		if (zap[i][0] == 2) {
			union_lists(zap[i][1], zap[i][2], seg, segm);
		}
		if (zap[i][0] == 3 && zap[i][1] != i-1) {
			zap_3(zap[i][1], n, zap, seg, segm);
		}
	}
}

int main()
{
	int n, q, g;
	cin>>n>>q>>g;
	vector<vector<int>> zap(q, vector<int>(3));
	for (int i=0;i<q;++i) {
		cin>>zap[i][0]>>zap[i][1];
		zap[i][1]--;
		if (zap[i][0] != 3) {
			cin>>zap[i][2];
			zap[i][2]--;
		}
	}
	if (g == 4) {
		vector<int> seg(n), dep(n), pseg(n);
		for (int i=0;i<n;++i) {
			seg[i] = i;
			pseg[i] = i;
			dep[i] = 1;
		}
		for (int i=0;i<q;++i) {
			if (zap[i][0] == 1) {
				int s1 = find_root(zap[i][1], seg, pseg);
				if (dep[s1] > zap[i][2]) {
					cout<<s1 + zap[i][2]+1<<endl;
				} else {
					cout<<-1<<endl;
				}
			}
			if (zap[i][0] == 2) {
				int s1 = find_root(zap[i][1], seg, pseg), s2 = find_root(zap[i][2], seg, pseg);
				if (s1 != s2) {
					if (s2 < s1) {
						swap(s1, s2);
					}
					pseg[s2] = s1;
					dep[s1] += dep[s2];
				}
			}
		}
	} else {
		vector<list<int>> segm(n);
		vector<int> seg(n);
		for (int i=0;i<n;++i) {
			segm[i].push_back(i);
			seg[i] = i;
		}
		for (int i=0;i<q;++i) {
			if (zap[i][0] == 1) {
				int s1 = seg[zap[i][1]];
				auto itr = segm[s1].begin();
				for(int j=0;j<zap[i][2] && itr!=segm[s1].end();++j) {
					++itr;
				}
				if (itr!=segm[s1].end()) {
					cout<<(*itr)+1<<endl;
				} else {
					cout<<-1<<endl;
				}
			}
			if (zap[i][0] == 2) {
				union_lists(zap[i][1], zap[i][2], seg, segm);
			}
			if (zap[i][0] == 3 && zap[i][1] != i-1) {
				zap_3(zap[i][1], n, zap, seg, segm);
			}
		}
	}
}