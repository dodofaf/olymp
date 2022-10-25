#include <bits/stdc++.h>
#include <cassert>
#include <ext/pb_ds/assoc_container.hpp>

using namespace __gnu_pbds;
using namespace std;

typedef tree<int, null_type, less<int>, rb_tree_tag,
tree_order_statistics_node_update> ordered_set;

#define f first
#define s second

struct Ver_1_2
{
	int p;
	int med;
	int n_city = 1;
	ordered_set reg;
};

static void build_tree_1_2(int n, vector<list<int>> &roads, vector<Ver_1_2> &tree, vector<int> &a)
{
	tree[0].p = 0;
	for (int i=0;i<n;++i) {
		tree[i].reg.insert(a[i]);
		for (auto j=roads[i].begin();j!=roads[i].end();++j) {
			if ((*j) != tree[i].p) {
				tree[(*j)].p = i;
				tree[i].n_city++;
			}
		}
		roads[i].clear();
	}
}

auto cmp_1_2 = [](const pair<int, int> &a, const pair<int, int> &b)
{
	return a.f<b.f;
};

int main()
{
	int n, k, g;
	cin>>n>>k>>g;
	vector<int> a(n);
	for (int i=0;i<n;++i) cin>>a[i];

	vector<list<int>> roads(n);
	vector<int> nroads(n, 0);
	for (int i=0;i<n-1;++i) {
		int v,u;
		cin>>v>>u;
		--v;
		--u;
		roads[v].push_back(u);
		roads[u].push_back(v);
		++nroads[u];
		++nroads[v];
	}
	int m;
	cin>>m;
	if (g == 1 || g == 2) {
		vector<Ver_1_2> tree(n);
		build_tree_1_2(n, roads, tree, a);
		map<int, int> medians;
		for (int i=1;i<n;++i) {
			if(nroads[i] == 1) {
				int x = i;
				while (tree[x].n_city == 1) {
					tree[x].med = (*tree[x].reg.find_by_order(tree[x].reg.size()/2));
					medians[tree[x].med]++;
					for (auto itr=tree[x].reg.begin();itr!=tree[x].reg.end();++itr) {
						tree[tree[x].p].reg.insert((*itr));
					}
					tree[x].reg.clear();
					x = tree[x].p;
					tree[x].n_city--;
				}
			}
		}
		for (int i=0;i<m;++i) {
			int x;
			cin>>x;
			cout<<medians[x]<<' ';
		}
		cout<<'\n';
	} else {
		for (int i=0;i<m;++i) {
			int x;
			cin>>x;
			cout<<"0 ";
		}
		cout<<'\n';
	}
}
