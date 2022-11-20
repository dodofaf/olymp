#include <iostream>
#include <list>
#include <vector>

using namespace std;

int main()
{
	int n, m;
	cin>>n>>m;
	vector<list<int>> in(n), out(n);
	for (int i=0;i<m;++i) {
		int x, y;
		cin>>x>>y;
		x--;
		y--;
		out[x].push_back(y);
		in[y].push_back(x);
	}
	for (int i=0;i<n;++i) {
		if (in[i].empty() && !out[i].empty()) cout<<"1 ";
		else if (!in[i].empty() && out[i].empty()) cout<<"-1 ";
		else cout<<"0 ";
	}
	cout<<'\n';
}