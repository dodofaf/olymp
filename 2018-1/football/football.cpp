#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

struct Segment
{
	int x1;
	int y1;
	int x2;
	int y2;
};

bool check_seg(int l1, int r1, int l2, int r2) {
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

int check(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4)  
{
	if (check_seg(x1, x2, x3, x4) && check_seg(y1, y2, y3, y4)) {
		return 1;
	} else {
		return 0;
	}
}

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
	fstream sin("football.in", sin.in);
//	fstream sin("1.tst", sin.in);
	getline(sin, line);
	istringstream iss(line);
	int n, m, q;
	iss>>n>>m;
	getline(sin, line);
	istringstream iss1(line);
	iss1>>q;
	vector<Segment> seg(q);
	for (int i=0;i<q;i++) {
		getline(sin, line);
		istringstream iss(line);
    	iss>>seg[i].x1>>seg[i].y1>>seg[i].x2>>seg[i].y2;
    }
    fstream sout("football.out", sout.out);
    long long cnt = 0;
    for (int i=0;i<q;i++) {
    	cnt--;
    	for (int j=0;j<q;j++) {
    		cnt += check(seg[i].x1, seg[i].y1, seg[i].x2, seg[i].y2, seg[j].x1, seg[j].y1, seg[j].x2, seg[j].y2);
    	}
    }
	sout<<cnt/2<<"\n";
//    cout<<cnt/2<<"\n";
}