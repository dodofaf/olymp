#include <iostream>
#include <math.h>

using namespace std;

int main()
{
	int t;
	cin>>t;
	for (;t>0;t--) {
		int x1, y1, r1, x2, y2, r2;
		cin>>x1>>y1>>r1>>x2>>y2>>r2;
		double d = sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
		if (r1+r2<d) cout<<"0 ";
		else if (r1<d+r2 && r2<d+r1) cout<<"1 ";
		else if (r1>d+r2) cout<<"2 ";
		else cout<<"3 ";
	}
	cout<<'\n';
}