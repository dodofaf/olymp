#include <bits/stdc++.h>

using namespace std;

int random(int m)
{
    return rand()%m;
}

static long long mn(long long a, long long b, long long c)
{
	if (a<=b && a<=c) {
		return a;
	}
	if (a>=b && b<=c) {
		return b;
	}
	if (c<=b && a>=c) {
		return c;
	}
	return 0;
}

static bool per(int n, int x, int k, long long &weight, vector<vector<vector<int>>> &edge)
{
	for (int i=0;i<n;++i) {
		for (int j=0;j<n;++j) {
			if (edge[i][j][0] == 0 ){
				weight -= edge[i][j][1];
				edge[i][j][0] = x;
				edge[j][i][0] = x;
			}
		}
		bool b = false;
		if (x>1) {
			b = per(n, x-1, k, weight, edge);
		} else {
//			cout<<weight<<endl;
			if (weight<=k) {
				for (int i=0;i<n;i++) {
//					for (int j=0;j<n;j++)
//						cout<<edge[i][j][0]<<' ';
//					cout<<endl;
				}
				b = true;
			}
		}
		for (int j=0;j<n;++j) {
			if (edge[i][j][0] == x){
				weight += edge[i][j][1];
				edge[i][j][0] = 0;
				edge[j][i][0] = 0;
			}
		}
		if (b)
			return true;
	}
	return false;
}

void prebir(int n, int m, long long weight, vector<vector<vector<int>>> &edge, vector<int> &checks)
{	
	for (int i=0;i<m;++i) {
		if (weight<=checks[i]) {
			cout<<0<<' ';
		} else {
			for (int j=1;j<=n;++j) {
				long long masa = weight;
				if (per(n, j, checks[i], masa, edge)) {
					cout<<j<<' ';
					break;
				}
			}
		}
	}
	cout<<endl;
}

static int bin_search(long long x, int n, vector<long long> &array)
{
	int l = 0, r = n-1, res = -1;
	if (x>=array[0]) {
		res = 0;
	}
	while (r != l+1 && res == -1) {
		if (array[(r+l)/2] < x) {
			r = (r+l)/2;
		} else {
			if (array[(r+l)/2] > x) {
				l = (r+l)/2;
			} else {
				res = (r+l)/2;
			}
		}
	}
	if (res == -1) {
		res = r;
	}
	while (res != 0 && array[res-1] == array[res]) {
		res--;
	}
 	return res;
}

int main(int argc, char**argv)
{
	int n, m, g;
#if 1
	cin>>n>>m>>g;
	vector<vector<int>> edge(n, vector<int>(n, 0));
	vector<vector<vector<int>>> edg(n);
	vector<int> cnt(n, 0);
	long long weight = 0;
	for (int i=1;i<n;i++) {
		int a,b,c;
		cin>>a>>b>>c;
		cnt[a-1]++;
		cnt[b-1]++;
		weight += c;
		edge[a-1][b-1] = c;
		edge[b-1][a-1] = c;
		edg[a-1].push_back({b-1, c});
		edg[b-1].push_back({a-1, c});
	}

	vector<int> checks(m);
	for (int i=0;i<m;i++) {
		cin>>checks[i];
	}
#else
	int t = time(NULL);
//	n =10;
//	t= 1644697365;

//	t=1644699400;
	n = 5;
	cout<<"t="<<t<<endl;
	srand(t);

	m =1;
	g =3;
	vector<vector<vector<int>>> edge(n);
	for (int i=0;i<n;i++) {
		edge[i].resize(n);
		for (int j=0;j<n;j++) {
			edge[i][j] = {0, 0};
		}
	}
	long long weight = 0;
	for (int i=1;i<n;i++) {
		int a=i,b = i+1,c = random(1000);
		cout<<"c="<<c<<endl;
		weight += c;
		edge[a-1][b-1][1] = c;
		edge[b-1][a-1][1] = c;
	}

	vector<int> checks(m);
	for (int i=0;i<m;i++) {
		checks[i] = 0;//1 + random(weight);
		cout<<"k="<<checks[i]<<endl;
	}
	prebir(n, m, weight, edge, checks);
#endif


#if 1
	vector<vector<vector<long long>>> dp(n);
	vector<vector<int>> line(n, vector<int>(2, -1));
	vector<int> cnt_ch(n, 1);
	int y = 0;
	for (int i=0;i<n;i++) {
		if (edge[0][i] != 0) {
			line[y][0] = i;
			line[y][1] = 0;
			y++;
		}
	}
	int x, p;
	while (y != 0) {
		x = line[y-1][0];
		p = line[y-1][1];
		if (cnt[x] == 1) {
			if (dp[x].size() == 0) {
				dp[x].resize(n+1, vector<long long>(2, 2e18+11));
				dp[x][0][0] = 0;
				dp[x][1][1] = 0;
			}
			if (dp[p].size() == 0) {
				dp[p].resize(n+1, vector<long long>(2, 2e18+11));
				dp[p][0][0] = 0;
				dp[p][1][1] = 0;
			}
			vector<vector<long long>> new_dp(n+1, vector<long long>(2, 2e18+11));
			for (int i=0;i<=cnt_ch[p];i++) {
				for (int j=0;j<=n-i && j<=cnt_ch[x];j++) {
					new_dp[j + i][0] = min(new_dp[j + i][0], dp[x][j][1] + dp[p][i][0]);
	                new_dp[j + i][0] = min(new_dp[j + i][0], dp[x][j][0] + dp[p][i][0] + edge[x][p]);
	                new_dp[j + i][1] = min(new_dp[j + i][1], dp[x][j][0] + dp[p][i][1]);
	                new_dp[j + i][1] = min(new_dp[j + i][1], dp[x][j][1] + dp[p][i][1]);
				}
			}
			cnt_ch[p] += cnt_ch[x];	
			dp[p] = new_dp;
			y--;
			cnt[p]--;
			dp[x].clear();
		} else {
			for (int i=0;i<edg[x].size();i++) {
				if (edg[x][i][0] != p) {
					line[y][0] = edg[x][i][0];
					line[y][1] = x;
					y++;
				}
			}
		}
	}
	vector<long long> ans(n+1, 0);
	for (int i=0;i<n+1;i++) {
		ans[i] = min(dp[0][i][0], dp[0][i][1]);
	}
	for (int i=0;i<m;i++) {
		cout<<bin_search(checks[i], n, ans)<<' ';
	}
	cout<<endl;
#endif
	return 0;
}	