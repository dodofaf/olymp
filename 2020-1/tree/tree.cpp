#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <iterator>
#include <string>
#include <algorithm>
#include <memory.h>
#include <sstream>
#include <fstream>
#include <functional>
#include <random>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <set>

using namespace std;

#define f first
#define s second

int random(int m) 
{
	return rand() % m + 1;
}

void print_list(list<int> &l)
{
	for (auto i=l.begin();i!=l.end();++i) cout<<(*i)<<' ';
	cout<<'\n';
}

struct Ver_1_2
{
	int p;
	int med;
	int n_city;
	int n_sons;
	list<int> reg;
};

static void build_tree_1_2(int n, vector<list<int>> &roads, vector<Ver_1_2> &tree, vector<int> &a)
{
	tree[0].p = 0;
	for (int i=0;i<n;++i) {
		tree[i].n_sons = 0;
		tree[i].n_city = 1;
		tree[i].reg.push_back(a[i]);
		for (auto j=roads[i].begin();j!=roads[i].end();++j) {
			if ((*j) != tree[i].p) {
				tree[(*j)].p = i;
				tree[i].n_sons++;
			}
		}
		roads[i].clear();
	}
}

int merge_lists_plus_find_mediane(int &n1, int n2, list<int> &list1, list<int> &list2)
{
	int mediane = 0;
	int i = 0, med = (n1+n2)/2;
	auto itr1 = list1.begin(), itr2 = list2.begin();
	for (;(itr1 != list1.end()) && (itr2 != list2.end());++itr1, i++) {
		for (;(itr2 != list2.end()) && ((*itr2)<=(*itr1));++itr2, i++) {
			list1.insert(itr1, (*itr2));
			if (i == med) mediane = (*itr2);
		}
		if (i == med) mediane = (*itr1);
	}
	for (;itr2 != list2.end();itr2++, i++) {
		list1.insert(itr1, (*itr2));
		if (i == med) mediane = (*itr2);
	}
	for (;itr1 != list1.end();itr1++, i++) {
		if (i == med) mediane = (*itr1);
	}
	n1 += n2;
	list2.clear();
	return mediane;
}

struct Ver_bf
{
	int p;
	int med;
	int n_city;
	list<int> sons;
};

static void build_tree_bf(int n, vector<list<int>> &roads, vector<Ver_bf> &tree, vector<int> &a)
{
	tree[0].p = 0;
	list<int> pre, ve;
	pre.push_back(0);
	while (!pre.empty()) {
		for (auto itr=pre.begin();itr!=pre.end();++itr) {
			for (auto j=roads[(*itr)].begin();j!=roads[(*itr)].end();++j) {
				if (tree[(*itr)].p != (*j)) {
					tree[(*j)].p = (*itr);
					tree[(*itr)].sons.push_back((*j));
					ve.push_back((*j));
				}
			}
		}
		pre = ve;
		ve.clear();
	}
	for (int i=0;i<n;++i) print_list(tree[i].sons);
}

void bf_k0(int n, int k, int m, vector<int> a, vector<list<int>> roads, vector<int> zap)
{
	vector<Ver_bf> tree(n);
	build_tree_bf(n, roads, tree, a);
	for (int i=0;i<n;++i) {
		vector<int> reg(n+1, 2e9), q(n+1);
		int size = 1, reg_size = 0;
		q[0] = i;
		while (size!=0) {
			--size;
			int x = q[size];
			reg[reg_size] = a[x];
			++reg_size;
			for (auto itr=tree[x].sons.begin();itr!=tree[x].sons.end();++itr) {
				q[size] = (*itr);
				++size;
			}
		}
		sort(reg.begin(), reg.end());
		tree[i].med = reg[reg_size/2];
	}
	for (int i=0;i<m;++i) {
		int cnt = 0;
		for (int j=0;j<n;++j) cnt += (tree[j].med==zap[i]);
		cout<<cnt<<' ';
	}
	cout<<'\n';
}

bool check_mediane_bf(int n, int x, vector<int> &a, vector<int> &reg) 
{
	vector<int> res(n);
	for (int i=0;i<n;++i) res[i] = a[reg[i]];
	sort(res.begin(), res.end());
	return res[n/2] == x;
}

void bf(int n, int k, int m, vector<int> a, vector<list<int>> roads, vector<int> zap)
{
	fstream sout("tree.out", sout.out);
	vector<Ver_bf> tree(n);
	build_tree_bf(n, roads, tree, a);
	vector<int> qq(n+1);
	for (int i=0;i<m;++i) {
		int cnt = 0;
		for (int j=0;j<n;j++) {
			vector<int> reg(n+1);
			int size = 1, reg_size = 0;
			qq[0] = j;
			while (size!=0) {
				--size;
				int x = qq[size%(n+1)];
				reg[reg_size%(n+1)] = x;
				++reg_size;
				for (auto itr=tree[x].sons.begin();itr!=tree[x].sons.end();++itr) {
					qq[size] = (*itr);
					++size;
				}
			}
			//qq.clear();
			reg.resize(reg_size);
			if (check_mediane_bf(reg_size, zap[i], a, reg)) {
				cnt++;
			} else if (k>0) {
//				cout<<"o\n";
				int o_size = n-reg_size;
				if (o_size>0) {
//					cout<<"x\n";
					vector<int> other(o_size);
					for (int ii=0, s=0, jj = 0;ii<n;++ii) {
						if (ii==reg[jj]) ++jj;
						else {
							other[s] = ii;
							++s;
						}
					}
//					cout<<j<<':';for (int ii=0;ii<o_size;++ii) cout<<other[ii]<<' ';cout<<'\n';

					int max_q = min(k, reg_size);
					vector<pair<int, int>> q(max_q);
					bool flag = true;
					for (int size_q=1;size_q<=max_q && flag;++size_q) {
						for (int ii=0;ii<size_q;++ii) {
							q[ii].f = 0;
							q[ii].s = 0;
							swap(a[reg[q[ii].f]], a[other[q[ii].s]]);
						}
						while (flag) {
							if (check_mediane_bf(reg_size, zap[i], a, reg)) {
								++cnt;
								flag = false;
							} else {
								int x = 0;
								while (x<size_q) {
									swap(a[reg[q[x].f]], a[other[q[x].s]]);
									++q[x].s;
									if (q[x].s == o_size) {
										q[x].s = 0;
										++q[x].f;
										if(q[x].f == reg_size) {
											q[x].f = 0;
											swap(a[reg[q[x].f]], a[other[q[x].s]]);
											++x;
										} else {
											swap(a[reg[q[x].f]], a[other[q[x].s]]);
											break;
										}
									}else {
										swap(a[reg[q[x].f]], a[other[q[x].s]]);
										break;
									}
								}
								if (x == size_q) flag = false;
							}
						}
						for (int ii=0;ii<size_q;++ii) swap(a[reg[q[ii].f]], a[other[q[ii].s]]);
//						for (int ii=0;ii<n;++ii) cout<<a[ii]<<' ';
//						cout<<'\n';
					}
				}
			}
		}
//		cout<<cnt<<' ';
		sout<<cnt<<' ';
	}
//	cout<<'\n';
	sout<<'\n';
}

void rand_gen_tree(int &n, int deep, int max_width, vector<list<int>> &roads, vector<int> &nroads)
{
	n = 1;
	roads.resize(1);
	roads.reserve(deep*max_width);
	nroads.reserve(deep*max_width);
	nroads.push_back(0);
	list<int> pre, ve;
	pre.push_back(0);
	int x = 0;
	for (int i=0;i<deep-1;++i) {
		for (auto itr=pre.begin();itr!=pre.end();++itr) {
//			int r = max_width;
			int r = random(max_width+1)-1;
			for (int j=0;j<r;j++) {
				++x;
				++n;
				int u = (*itr), v = x;
				ve.push_back(v);
				roads[u].push_back(v);
				roads.push_back({u});
				++nroads[u];
				nroads.push_back(1);
			}
		}
		pre = ve;
		ve.clear();
	}
	for (int i=0;i<n;++i) {
		cout<<i<<": ";
		print_list(roads[i]);
	}
}

int mediane(int n, list<int> l)
{
	auto itr=l.begin();
	for (int i=0;i<n/2;++i, ++itr) ;
	return (*itr);
}

int main()
{
#if 0
	int t = time(NULL);
//	t = 1667759369;
//	t = 1667758455;
//	t = 1667326033;
//	t = 1667289649;
//	t = 1667253493;
//	t = 1667220045;
//	t = 1667211983;
//	t = 1667141788;
	cout<<t<<'\n';
	srand(t);
	int n, k = 0, g = 1;

	int deep = 3, max_width = 5;
	vector<list<int>> roads;
	vector<int> nroads;
	rand_gen_tree(n, deep, max_width, roads, nroads);
	cout<<"n = "<<n<<'\n';

//	k = random(6);
	cout<<k<<'\n';

	vector<int> a(n);
	for (int i=0;i<n;++i) a[i]=random(10);

//	for (int i=0;i<n;++i) cout<<a[i]<<' ';
//	cout<<'\n';

	int m = 5;
	vector<int> zap(m);
	for (int i=0;i<m;++i) zap[i]=random(10);

//	for (int i=0;i<m;++i) cout<<zap[i]<<' ';
//	cout<<'\n';
#endif
#if 0
	int n, k, g;
	cin>>n>>k>>g;
	vector<int> a(n);
	for (int i=0;i<n;++i) cin>>a[i];

	vector<list<int>> roads(n);
	vector<int> nroads(n, 0);
	for (int i=0;i<n-1;++i) {
		int v, u;
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
	vector<int> zap(m);
	for (int i=0;i<m;++i) cin>>zap[i];
#endif
#if 1
	string line;
	fstream sin("tree.in", sin.in);
	getline(sin, line);
	istringstream iss(line);
	int n, k, g;
	iss>>n>>k>>g;
	vector<int> a(n);
	getline(sin, line);
	istringstream iss1(line);
	for (int i=0;i<n;++i) iss1>>a[i];
	vector<list<int>> roads(n);
	vector<int> nroads(n, 0);
	for (int i=0;i<n-1;++i) {
		getline(sin, line);
		istringstream iss3(line);
		int v, u;
		iss3>>v>>u;
		--v;
		--u;
		roads[v].push_back(u);
		roads[u].push_back(v);
		++nroads[u];
		++nroads[v];
	}
	getline(sin, line);
	istringstream iss4(line);
	int m;
	iss4>>m;
	vector<int> zap(m);
	getline(sin, line);
	istringstream iss5(line);
	for (int i=0;i<m;++i) iss5>>zap[i];

//	for (int i=0;i<m;++i) cout<<zap[i]<<' ';
//	cout<<'\n';
#endif
	fstream sout("tree.out", sout.out);

	bf(n, k, m, a, roads, zap);
#if 0
	if (g == 1 || g == 2) {
		vector<Ver_1_2> tree(n);
		build_tree_1_2(n, roads, tree, a);
		map<int, int> medians;
		if (n == 1) {
			medians[a[0]]++;
		} else {
			for (int i=1;i<n;++i) {
				if(nroads[i] == 1) {
					int x = i;
					tree[x].med = a[x];
					while (tree[x].n_sons == 0 && x!=0) {
						medians[tree[x].med]++;
						int p = tree[x].p;
						int med = merge_lists_plus_find_mediane(tree[p].n_city, tree[x].n_city, tree[p].reg, tree[x].reg);
						tree[p].n_sons--;
						tree[p].med = med;
						x = p;
					}
				}
			}
			medians[tree[0].med]++;
		}
		for (int i=0;i<m;++i) {
			cout<<medians[zap[i]]<<' ';
			sout<<medians[zap[i]]<<' ';
		}
		cout<<'\n';
		sout<<'\n';
	} else {
		bf(n, k, m, a, roads, zap);
	}
#endif
}
