#include <bits/stdc++.h>

using namespace std;

struct City
{
	vector<int> in;
	vector<int> out;
};

int main()
{
	int n, m;
	cin>>n>>m;
	vector<City> roads(n);
	vector<int> nroads(n, 0), nrroads(n, 0);
	for(int i=0;i<m;i++){
		int a,b;
		cin>>a>>b;
		a--;
		b--;
		roads[a].out.push_back(b);
		roads[b].in.push_back(a);
		nroads[a]++;
		nrroads[b]++;
	}
	if (nrroads[0] > 0) {
		vector<int> q(n+1, -1), q1(n+1, -1), tick(n, 0), nroads0(nroads), nrroads0(nrroads);
		int y = 1, y1 = 1;
		q[0] = 0;
		q1[0] = 0;
		int x, x1;
		while(y != 0 || y1!=0) {
			if (y != 0) {
				x = q[y-1];
			}
			if (y1!=0) {
				x1 = q1[y1-1];
			}
			if ((y+y1 == n+2 && x == x1) || (y == n+1) || (y1 == n+1)) {
				break;
			}
			int j = nroads[x]-1;
			while(j != -1 && tick[roads[x].out[j]] != 0 && (roads[x].out[j] != 0 && nroads[roads[x].out[j]]==0)) {
				j--;
			}
			int j1 = nrroads[x1]-1;
			while(j1 != -1 && !(tick[roads[x1].in[j1]] == 0 || roads[x1].in[j1] == x) && (roads[x1].in[j1] != 0 && nrroads[roads[x1].in[j1]]==0)) {
				j1--;
			}
			if (j!= -1) {
				q[y] = roads[x].out[j];
				nroads[x]--;
				tick[q[y]]=1;
				y++;
			} else {
				y--;
				tick[q[y]] = 0;
				nroads[q[y]] = nroads0[q[y]];
			}

			if (j1!= -1) {
				q1[y1] = roads[x1].in[j1];
				nrroads[x1]--;
				tick[q1[y1]]=1;
				y1++;
			} else {
				y1--;
				tick[q1[y1]] = 0;
				nrroads[q1[y1]] = nrroads0[q1[y1]];
			}
		}
		if (y == 0 || y1==0) {
			cout<<"NO\n";
		} else {
			cout<<"YES\n";
			if (y+y1 == n+2 && x == x1) {
				cout<<1<<"\n";
				for (int i=0;i<y-2;i++) {
					cout<<q[i]+1<<' ';
				}
				cout<<q[y-1]+1<<' ';
				for (int i=y1-2;i>-1;i--) {
					cout<<q1[i]+1<<' ';
				}
			} else {
				if (y == n+1) {
					cout<<2<<"\n";
					for (int i=0;i<y;i++) {
						cout<<q[i]+1<<' ';
					}
				} else {
					cout<<3<<"\n";
					for (int i=y1-1;i>-1;i--) {
						cout<<q1[i]+1<<' ';
					}
				} 

			}
			cout<<"\n";
		}
	} else {
		cout<<"NO\n";
	}
}

