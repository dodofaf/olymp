#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace __gnu_pbds;
using namespace std;

typedef tree<int, null_type, less<int>, rb_tree_tag,
tree_order_statistics_node_update> ordered_set;



struct Ver
{
	int p;
	list<int> ch;
};

static void build_tree(int q, vector<vector<int>> &zap, vector<Ver> &tree)
{
	tree[0].p = 0;
	for(int i=1;i<q+1;i++) {
		if (zap[i][0] == 3) {
			tree[i].p = zap[i][1];
			tree[zap[i][1]].ch.push_back(i);
		} else {
			tree[i].p = i-1;
			tree[i-1].ch.push_back(i);
		}
	}
}

static void swap(int &a, int &b)
{
	int t = a;
	a = b;
	b = t;
}

static int find_root(int x, vector<int> &pseg)
{
	int s1 = x;
	while(s1 != pseg[s1]) {
		s1 = pseg[s1];
	}
	return s1;
}

static int zap_1(int x, int k, int n, int ns, int s, vector<vector<short int>> &c, vector<int> &pseg)
{
	int d = 0;
	int s1 = find_root(x, pseg);
	while (d != ns && k >= c[s1][d]) {
		k-=c[s1][d];
		d++;
	}
	if (d != ns) {
		int mx = min((d+1)*s, n);
		for (int i=d*s;i<mx;i++) {
			int si = find_root(i, pseg);
			if (si == s1) {
				k--;
			}
			if (k == -1) {
				return i+1;
			}
		}
	}
	return -1;
}


static int marge(int x, int y, int z, int ns, vector<vector<short int>> &c, vector<int> &pseg, vector<int> &rank,
 vector<int> &tick, vector<int> &res)
{
	int s1 = find_root(x, pseg), s2 = find_root(y, pseg);
	int t = 2;
	if (s1 != s2) {
		if (rank[s1]<rank[s2]) {
			swap(s1, s2);
			t = 1;
		}
		for (int i=0;i<ns;++i) {
			c[s1][i] += c[s2][i];
		}
		pseg[s2] = s1;
		res[z-1] = -3;
		tick[z] = t;
		if (rank[s1] == rank[s2]) {
			++rank[s1];
			tick[z] *= -1;
		}
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
	vector<int> pseg(n), rank(n, 1), tick(q+1, 0);
	for (int i=0;i<n;++i) {
		pseg[i] = i;
	}
	int s = sqrt(n), ns = s;
	if (s*s != n) {
		ns++;
	}
	if (n>ns*s) {
		ns++;
	}
	vector<vector<short int>> c(n, vector<short int>(ns, 0));
	for (int i=0;i<n;++i) {
		c[i][i/s] = 1;
	}

	vector<int> res(q, -2);
	int x = 0;
	while (!tree[0].ch.empty()){
		if (x != 0) {
			if (res[x-1] == -2 && zap[x][0] == 1) {
				res[x-1] = zap_1(zap[x][1], zap[x][2], n, ns, s, c, pseg);
			}
			if (zap[x][0] == 2) {
				if (res[x-1] == -2) {
					if (!tree[x].ch.empty()) {
						zap[x][0] = marge(zap[x][1], zap[x][2], x, ns, c, pseg, rank, tick, res);
					}
				} else {
					if (tree[x].ch.empty()) {
						int s2 = zap[x][abs(tick[x])];
						int s1 = pseg[s2];
						while(pseg[s1] != s1) {
							s2 = s1;
							s1 = pseg[s1];
						}
						for (int i=0;i<ns;i++) {
							c[s1][i] -= c[s2][i];
						}
						if (tick[x] < 0) {
							--rank[s1];
						}
						pseg[s2] = s2;
					}
				}
			}
		}
		if (tree[x].ch.empty()) {
			if (g == 4 || g == 5) {
				break;
			}
			x = tree[x].p;
			tree[x].ch.pop_front();
		} else {
			x = tree[x].ch.front();
		}
	}
	for (int i=0;i<q;i++) {
		if (res[i] > -2) {
			cout<<res[i]<<endl;
		} 
	}
} 