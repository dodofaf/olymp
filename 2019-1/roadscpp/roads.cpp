#include <bits/stdc++.h>

using namespace std;

struct Segm
{
	int l;
	int r;
	vector<int> ar;
};

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

static void swap(int &a, int &b)
{
	int t = a;
	a = b;
	b = t;
}
static void union_seg(int a, int b, vector<long long> &hseg, vector<int> &pseg, vector<int> &rank)
{
	if (a != b) {
		if (rank[a] < rank[b]) {
			swap(a, b);
		}
		pseg[b] = a;
		hseg[a] += hseg[b];
		if (rank[a] == rank[b]) {
			++rank[a];
		}
	}
}

static void check_ar(int k, vector<int> &ar, vector<int> &ar1, vector<int> &ar2, int n, int m, int d, int s, int nseg,
 vector<vector<int>> &ev, vector<vector<long long>> &zap, vector<long long> hseg, vector<int> seg, vector<int> pseg)
{
	vector<int> rank(nseg, 0);
	for (int i=d-1;i>k-1;i--) {
		if (ev[i][0] == 1) {
			int a = find_root(ev[i][1], seg, pseg),b = find_root(ev[i][2], seg, pseg);
			union_seg(a, b, hseg, pseg, rank);

		} else {
			int s1 = find_root(ev[i][1], seg, pseg);
			hseg[s1]+=ev[i][2];
		}
	}
	int siz = ar.size();
	for (int i=0;i<siz;i++) {
		int x = zap[ar[i]][0], y = zap[ar[i]][1], z = zap[ar[i]][2];
		int s1 = find_root(x, seg, pseg), s2 = find_root(y, seg, pseg);
		if (hseg[s1] + hseg[s2] >= z) {
			ar2.push_back(ar[i]);
		} else {
			ar1.push_back(ar[i]);
		}
	}
}

int main()
{
	int n, m, d, s;
	cin>>n>>m>>d>>s;
	vector<int> resid(n);
	for (int i=0;i<n;i++) {
		cin>>resid[i];
	}
	vector<set<int>> roads(n);
	for (int i=0;i<m;i++) {
		int a,b;
		cin>>a>>b;
		roads[a-1].insert(b-1);
		roads[b-1].insert(a-1);
	}
	vector<vector<int>> ev(d, vector<int>(3));
	for (int i=0;i<d;i++) {
		cin>>ev[i][0]>>ev[i][1]>>ev[i][2];
		ev[i][1]--;
		if (ev[i][0] == 1) {
			ev[i][2]--;
			roads[ev[i][1]].erase(ev[i][2]);
			roads[ev[i][2]].erase(ev[i][1]);
		} else {
			resid[ev[i][1]]-=ev[i][2];
		}
	}
	vector<vector<long long>> zap(s, vector<long long>(3));
	for (int i=0;i<s;i++) {
		cin>>zap[i][0]>>zap[i][1]>>zap[i][2];
		zap[i][0]--;
		zap[i][1]--;
	}
	int nseg = 0;
	vector<int> seg(n, -1), pseg;
	vector<long long>  hseg;
	for (int i=0;i<n;i++) {
		if (seg[i] == -1) {
			int p= 1, cnt = 1;
			vector<int> q(n);
			q[0] = i;
			seg[q[0]] = nseg;
			long long h1=resid[q[0]];
			while (p != 0) {
				p--;
				int x = q[p];
				for (auto j=roads[x].begin();j!=roads[x].end();++j) {
					if (seg[(*j)] == -1) {
						h1 += resid[(*j)];
						seg[(*j)] = nseg;
						q[p] = (*j);
						p++;
					}
				}
			}
			hseg.push_back(h1);
			pseg.push_back(nseg);
			nseg++;
		}
	}
	vector<int> res(s, -2), ar(s);
	vector<Segm> q(1);
	q[0].l = -1;
	q[0].r = d+1;
	for(int i=0;i<s;i++) {
		ar[i] = i;
	}
	q[0].ar = ar;
	int p = 1;
	while(p != 0) {
		p--;
		int r = q[p].r, l = q[p].l;
		if (r == l+1) {
			int siz = q[p].ar.size();
			for(int i=0;i<siz;i++) {
				res[q[p].ar[i]] = l;
			}
		} else {
			vector<int> ar1, ar2;
			check_ar((l+r)/2, q[p].ar, ar1, ar2, n, m, d, s, nseg, ev, zap, hseg, seg, pseg);
			if (ar1.size() > 0) {
				q[p].l = l;
				q[p].r = (l+r)/2;
				q[p].ar = ar1;
				p++;
				if (ar2.size() > 0) {
					if (p == q.size()) {
						Segm segm;
						segm.r = r;
						segm.l = (r+l)/2;
						segm.ar = ar2;
						q.push_back(segm);
						p++;
					} else {
						q[p].r = r;
						q[p].l = (l+r)/2;
						q[p].ar = ar2;
						p++;
					}
				}
			} else {
				q[p].r = r;
				q[p].l = (l+r)/2;
				q[p].ar = ar2;
				p++;
			}
		}
 	}


	for (int i=0;i<s;i++) {
		cout<<res[i]<<endl;
 	}		
}