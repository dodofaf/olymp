#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace __gnu_pbds;
using namespace std;

typedef tree<int, null_type, less<int>, rb_tree_tag,
tree_order_statistics_node_update> ordered_set;

struct Node
{
	int idx;
	int dep;
};

struct Ver
{
	int p;
	list<Node> ch;
};

static void build_tree(int q, vector<vector<int>> &zap, vector<Ver> &tree)
{
	tree[0].p = 0;
	vector<int> dep(q+1, 0);
	for(int i=1;i<q+1;i++) {
		Node nd;
		nd.idx = i;
		nd.dep = 0;
		if (zap[i][0] == 3) {
			tree[i].p = zap[i][1];
			tree[zap[i][1]].ch.push_back(nd);
		} else {
			tree[i].p = i-1;
			tree[i-1].ch.push_back(nd);
		}
	}
	for(int i=q;i>0;i--) {
		if (dep[i]+1 > dep[tree[i].p]) {
			dep[tree[i].p] = dep[i]+1;
		}
	}
	for(int i=0;i<q;++i) {
		for(auto j=tree[i].ch.begin();j!=tree[i].ch.end();++j) {
			(*j).dep = dep[(*j).idx];
		}
		tree[i].ch.sort([](Node &a, Node &b) {
	        return a.dep < b.dep || (a.dep == b.dep && a.idx < b.idx);
	    });
	}
#if 0
	for(int i=0;i<q;++i) {
		cout<<i<<':';
		for(auto j=tree[i].ch.begin();j!=tree[i].ch.end();++j) {
			cout<<(*j).idx<<' ';
		}
		cout<<endl;
	}
#endif
}

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
	return s1;
}

static int zap_1(int x, int k, int n, vector<int> &seg, vector<int> &pseg)
{
	int s1 = find_root(seg[x], seg, pseg);
	for (int i=0;i<n;i++) {
		int si = find_root(seg[i], seg, pseg);
		if (si == s1) {
			k--;
		}
		if (k == -1) {
			return i+1;
		}
	}
	return -1;
}


static int marge(int x, int y, int z, vector<int> &seg, vector<int> &pseg, vector<int> &res)
{
	int s1 = find_root(seg[x], seg, pseg), s2 = find_root(seg[y], seg, pseg);
	if (s1 != s2) {
		pseg[s2] = s1;
		res[z-1] = -3;
		return 2;
	}
	return 4;
}

int main()
{
	int n, q, g;
	cin>>n>>q>>g;
	vector<vector<int>> zap(q+1, vector<int>(3));
	for (int i=1;i<=q;++i) {
		cin>>zap[i][0]>>zap[i][1];
		if (zap[i][0] != 3) {
			cin>>zap[i][2];
			zap[i][1]--;
			zap[i][2]--;
			if (zap[i][0] == 2 && zap[i][1] > zap[i][2]) {
				swap(zap[i][1], zap[i][2]);
			}
		}
	}
	vector<Ver> tree(q+1);
	build_tree(q, zap, tree);

	if (g == 4 || g == 6) {
		vector<int> seg(n), dep(n, 1), pseg(n);
		for (int i=0;i<n;++i) {
			seg[i] = i;
			pseg[i] = i;
		}
		int x = 0;
		vector<int> res(q, -2);
		while (!tree[0].ch.empty()){
			if (x != 0) {
				if (res[x-1] == -2 && zap[x][0] == 1) {
					int s1 = find_root(zap[x][1], seg, pseg);
					if (dep[s1] > zap[x][2]) {
						res[x-1] = s1 + zap[x][2]+1;
					} else {
						res[x-1] = -1;
					}
				}
				if (zap[x][0] == 2) {
					if (res[x-1] ==  -2) {
						if (!tree[x].ch.empty()) {
							int s1 = find_root(zap[x][1], seg, pseg), s2 = find_root(zap[x][2], seg, pseg);
							if (s1 != s2) {
								pseg[s2] = s1;
								dep[s1] += dep[s2];
								res[x-1] = -3;
							} else {
								zap[x][0] = 4;
							}
						}
					} else {
						if(tree[x].ch.empty()){
							int s1 = zap[x][1], s2 = zap[x][2];
							s1 = find_root(s1, seg, pseg);
							dep[s1] -= dep[s2];
							pseg[s2] = s2;
							res[x-1] = -2;
						}
 					}
				}
			}
			if (tree[x].ch.empty()) {
				x = tree[x].p;
				tree[x].ch.pop_front();
			} else {
				x = tree[x].ch.front().idx;
			}
		}
		for (int i=0;i<q;i++) {
			if (res[i] != -2) {
				cout<<res[i]<<endl;
			} 
		}
	} else {
		vector<int> seg(n), pseg(n);
		for (int i=0;i<n;++i) {
			seg[i] = i;
			pseg[i] = i;
		}

		vector<int> res(q, -2);
		int x = 0;
		while (!tree[0].ch.empty()){
			if (x != 0) {
				if (res[x-1] == -2 && zap[x][0] == 1) {
					res[x-1] = zap_1(zap[x][1], zap[x][2], n, seg, pseg);
				}
				if (zap[x][0] == 2) {
					if (res[x-1] == -2) {
						if (!tree[x].ch.empty()) {
							zap[x][0] = marge(zap[x][1], zap[x][2], x, seg, pseg, res);
						}
					} else {
						if (tree[x].ch.empty()) {
							int s = find_root(zap[x][1], seg, pseg);
							int s1 = seg[zap[x][2]];
							while(pseg[s1] != s) {
								s1 = pseg[s1];
							}
							pseg[s1] = s1;
						}
					}
				}
			} else {
				for(int i=0;i<n;i++) {
					assert(pseg[i] == i);
				}
			}
			if (tree[x].ch.empty()) {
				x = tree[x].p;
				tree[x].ch.pop_front();
			} else {
				x = tree[x].ch.front().idx;
			}
		}
		for (int i=0;i<q;i++) {
			if (res[i] > -2) {
				cout<<res[i]<<endl;
			} 
		}
	}
} 