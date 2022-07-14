#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

struct Segment
{
	int l;
	int r;
};

bool check(int l1, int r1, int l2, int r2) {
	if (l1<=l2 && r1>=l2){
		return true;
	}
	if (l1>=l2 && r1<=r2) {
		return true;
	}
	if (l1<=r2 && r1>=r2) {
		return true;
	}
	return false;
}

int main()
{
#if 0
	int n
	cin>>n;
	vector<Segment> seg(n);
	for (int i=0;i<n+1;i++) {
		cin>>seg[i].l>>seg[i].r;
    }
#else
	string line;
	fstream sin("magic.in", sin.in);
	getline(sin, line);
	istringstream iss(line);
	int n;
	iss>>n;
	vector<Segment> seg(n);
	for (int i=0;i<n+1;i++) {
		getline(sin, line);
		istringstream iss(line);
    	iss>>seg[i].l;
    	iss>>seg[i].r;
    }
#endif
    fstream sout("magic.out", sout.out);
    for (int i=0;i<n+1;i++) {
    	int cnt = 0;
    	for (int j=0;j<n+1;j++) {
    		cnt += check(seg[i].l, seg[i].r, seg[j].l, seg[j].r);
    	}
    	if (cnt == n+1 || cnt<n || i == n) {
#if 0
	   		cout<<i+1<<"\n";
#else
			sout<<i+1<<"\n";
#endif
			break;
    	}
    }
}

