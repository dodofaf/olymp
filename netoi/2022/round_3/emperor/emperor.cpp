#include <utility>
#include <iostream>
#include <vector>
#include <list>

using namespace std;

#define f first
#define s second




int main()
{
	int n;
	cin>>n;
	vector<pair<pair<int, int>, int>> ar(n);
	for (int i=0;i<n;++i)  {
		cin>>ar[i].f.f>>ar[i].f.s;
		ar[i].s = i;
	}
	cout<<"2\n";
}