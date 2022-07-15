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
    int m = 0;
    fstream sout("magic.out", sout.out);
    vector<Segment> bef(n+1), af(n+1);
    bef[0].l = 1;
    bef[0].r = 1e9;
    af[n].l = 1;
    af[n].r = 1e9;
    int ind = -1;
    for(int i=1;i<n+1;i++) {
    	if (check(seg[i].l, seg[i].r, bef[i-1].l, bef[i-1].r)) {
    		bef[i].l = max(seg[i].l, bef[i-1].l);
    		bef[i].r = min(seg[i].r, bef[i-1].r);
    	} else {
    		ind = i;
    		break;
    	}
    }
    for(int i=n-1;i>-1;i--) {
    	if (check(seg[i].l, seg[i].r, af[i+1].l, af[i+1].r)) {
    		af[i].l = max(seg[i].l, af[i+1].l);
    		af[i].r = min(seg[i].r, af[i+1].r);
    	} else {
    		ind = i;
    		break;
    	}
    }
    if (ind == -1) {
    	for (int i=0;i<n+1;i++) {
			if (check(af[i].l, af[i].r, bef[i].l, bef[i].r)) {
				sout<<i+1<<"\n";
				break;
	    	}
	    }
    } else {
    	sout<<ind+1<<"\n";
    }
}

