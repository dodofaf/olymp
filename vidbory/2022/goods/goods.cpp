#include <iostream>
#include <vector>

using namespace std;

int main()
{
	int n, m;
	cin>>n>>m;
	vector<vector<int>> g(n, vector<int>(m)), tick(n, vector<int>(m));
	for (int i=0;i<n;++i) {
		for (int j=0;j<m;++j) {
			cin>>g[i][j];
			g[i][j]--;
			tick[i][g[i][j]]++;
		}
	}
	int cnt= 0;
	vector<pair<int, int>> moves;
	moves.reserve(n*m+2);
	while(true) {
		int indf = n*m, q;
		bool flag = true;
		for (int i=0;i<n;++i) {
			for (int j=0;j<m;j++) {
				if (tick[i][g[i][j]]>1) {
					pair <int, int> p(i*m+j, indf);
					moves.push_back(p);
					tick[i][g[i][j]]--;
					q = g[i][j];
					g[i][j] = -1;
					cnt++;
					indf = i*m+j;
					flag = false;
					break;
				}
			} 
			if (!flag){break;}
		}
		if (flag) {break;}
		while (true) {
			int l = indf/m, x;
			for (int i=0;i<m;++i) {
				if (tick[l][i] == 0) {
					 x = i;
					 break;
				}
			}
			int l1 = -1;
			for (int i=0;i<n;++i) {
				if (tick[i][x]>1){
					l1 = i;
					break;
				}
			}
			if (l1!=-1) {
				for (int i=0;i<m;i++) {
					if (g[l1][i] == x) {
						tick[l][x]++;
						tick[l1][x]--;
						g[l][indf%m]=x;
						g[l1][i]=-1;
						pair <int, int> p(l1*m+i, indf);
						moves.push_back(p);
						indf = l1*m+i;
						cnt++;
						break;
					}
				}
			} else {
				pair <int, int> p(n*m, indf);
				g[l][indf%m]=q;
				tick[l][q]++;
				moves.push_back(p);
				cnt++;
				break;
			}
		}
	}
	for (int i=0;i<n;++i) {
		for (int j=0;j<m;++j) {
			cout<<g[i][j]<<' ';
		}
		cout<<"\n";
	}
	cout<<cnt<<"\n";
	for (int i=0;i<cnt;i++) {
		cout<<moves[i].first+1<<' '<<moves[i].second+1<<"\n";
	}
}