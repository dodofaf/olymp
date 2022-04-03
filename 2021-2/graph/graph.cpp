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
}

static void swap(int &a, int &b)
{
	int t = a;
	a = b;
	b = t;
}

static int zap_1(int x, int k, vector<int> &seg, vector<ordered_set> &segm)
{
	int s1 = seg[x];
	if (segm[s1].size() > k) {
		return (*segm[s1].find_by_order(k))+1;
	} else {
		return -1;
	}
}


static void marge(int x, int y, vector<int> &seg, vector<ordered_set> &segm)
{
	int s1 = seg[x], s2 = seg[y];
	if (s1 != s2) {
		if (segm[s1].size() < segm[s2].size()) {
			swap(s1, s2);
		}
		for(auto j=segm[s2].begin();j!=segm[s2].end();++j) {
			segm[s1].insert((*j));
			seg[(*j)] = s1;
		}
		segm[s2].clear();
	}
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
		}
	}

	vector<Ver> tree(q+1);
	build_tree(q, zap, tree);

	vector<ordered_set> segm(n);
	vector<int> seg(n);
	for (int i=0;i<n;++i) {
		segm[i].insert(i);
		seg[i] = i;
	}

	vector<vector<int>> m_seg(q+1);
	vector<vector<ordered_set>> m_segm(q+1);

	vector<int> res(q, -2);
	int x = 0;
	while (!tree[0].ch.empty()){
		if (!(m_seg[x].empty() && m_segm[x].empty())) {
			seg = m_seg[x];
			segm = m_segm[x];
			if (tree[x].ch.begin()++ == tree[x].ch.end()) {
				m_seg[x].clear();
				m_segm[x].clear();
			}
		}
		if (x != 0) {
			if (res[x-1] == -2 && zap[x][0] == 1) {
				res[x-1] = zap_1(zap[x][1], zap[x][2], seg, segm);
			}
			if (res[x-1] == -2 && zap[x][0] == 2) {
				marge(zap[x][1], zap[x][2], seg, segm);
				res[x-1] = -3;
			}
		}
		if (g != 4 && g!=5 && !tree[x].ch.empty() && tree[x].ch.begin()++ != tree[x].ch.end()) {
			m_seg[x] = seg;
			m_segm[x] = segm;
		}
		int p = tree[x].p;
		if (tree[x].ch.empty()) {
			tree[p].ch.pop_front();
			x = p;
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