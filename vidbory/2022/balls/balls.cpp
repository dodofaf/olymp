#include <bits/stdc++.h>

using namespace std;

int main()
{
	int n;
	cin>>n;
	vector<int> a(n);
	for(int i=0;i<n;i++) {
		cin>>a[i];
	}
	long long cnt = a[n-1];
	n-=2;
	int d = 0, dd = 1;
	while(n!= -1 && a[n]-d>0) {
		if (a[n] == a[n+1]) {
			dd++;
		} else {
			d+=dd;
			dd=1;
			if (a[n]-d <= 0) {break;}
		}
		cnt+=a[n]-d;
		n--;
	}
	cout<<cnt<<"\n";
}