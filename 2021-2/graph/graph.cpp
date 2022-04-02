#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace __gnu_pbds;
using namespace std;

typedef tree<int, null_type, less<int>, rb_tree_tag,
tree_order_statistics_node_update> ordered_set;

struct Ver
{
	int p;
	vector<int> ch;
};

static void swap(int &a, int &b)
{
	int t = a;
	a = b;
	b = t;
}

static void build_tree(int q, vector<vector<int>> &zap, vector<Ver> &tree)
{
	tree[0].p = 0;
	for(int i=1;i<q;i++) {
		if (zap[i][0] == 3) {
			tree[i].p = zap[i][1];
			tree[zap[i][1]].ch.push_back(i);
		} else {
			tree[i].p = i-1;
			tree[i-1].ch.push_back(i);
		}
	}
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

static void zap_3(int x, int n, int q, vector<vector<int>> &zap, vector<int> &seg, vector<ordered_set> &segm)
{
	for (int i=0;i<n;++i) {
		segm[i].clear();
		segm[i].insert(i);
		seg[i] = i;
	}
	for (int i=0;i<=x;++i) {
		if (zap[i][0] == 2) {
			int s1 = seg[zap[i][1]], s2 = seg[zap[i][2]];
			if (s1 != s2) {
				if (segm[s1].size() > segm[s2].size()) {
					for(auto j=segm[s2].begin();j!=segm[s2].end();++j) {
						segm[s1].insert((*j));
						seg[(*j)] = s1;
					}
					segm[s2].clear();
				} else {
					for(auto j=segm[s1].begin();j!=segm[s1].end();++j) {
						segm[s2].insert((*j));
						seg[(*j)] = s2;
					}
					segm[s1].clear();
				}
			}
		}
		if (zap[i][0] == 3 && zap[i][1] != i-1) {
			zap_3(zap[i][1], n, q, zap, seg, segm);
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
		vector<ordered_set> segm(n);
		vector<int> seg(n);
		for (int i=0;i<n;++i) {
			segm[i].insert(i);
			seg[i] = i;
		}
		for (int i=0;i<q;++i) {
			if (zap[i][0] == 1) {
				int s1 = seg[zap[i][1]];
				if (segm[s1].size() > zap[i][2]) {
					cout<<(*segm[s1].find_by_order(zap[i][2]))+1<<endl;
				} else {
					cout<<-1<<endl;
				}
			}
			if (zap[i][0] == 2) {
				int s1 = seg[zap[i][1]], s2 = seg[zap[i][2]];
				if (s1 != s2) {
					if (segm[s1].size() > segm[s2].size()) {
						for(auto j=segm[s2].begin();j!=segm[s2].end();++j) {
							segm[s1].insert((*j));
							seg[(*j)] = s1;
						}
						segm[s2].clear();
					} else {
						for(auto j=segm[s1].begin();j!=segm[s1].end();++j) {
							segm[s2].insert((*j));
							seg[(*j)] = s2;
						}
						segm[s1].clear();
					}
				}
			}
			if (zap[i][0] == 3 && zap[i][1] != i-1) {
				zap_3(zap[i][1], n, q, zap, seg, segm);
			}
		}
	}
} 