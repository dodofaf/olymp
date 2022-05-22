#include <bits/stdc++.h>

using namespace std;

void reverse(int l, int r, vector<int> &ar)
{
	for (int i=0;i<=(r-l)/2;i++) {
		swap(ar[l+i], ar[r-i]);
	}
}

int main()
{
	int n;
	cin>>n;
	vector<int> ar(n);
	for(int i=0;i<n;i++) {
		cin>>ar[i];
	}
	vector<vector<int>> res(n);
	int np = 0;
	for (int i=0;i<n-1;i++) {
		int mn = ar[i], ind_mn = i;
		for (int j=i+1;j<n;j++) {
			if (mn>ar[j]) {
				mn = ar[j];
				ind_mn = j;
			}
		}
		if(ind_mn!=i) {
			reverse(i, ind_mn, ar);
			res[np] = {i, ind_mn};
			np++;
		}
	}
	cout<<np<<"\n";
	for (int i=0;i<np;i++) {
		cout<<res[i][0]+1<<' '<<res[i][1]+1<<"\n";
	}
}