
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
			if ((seg[i].x1<=seg[j].x2 && seg[i].x2>=seg[j].x1) && (seg[i].y1<=seg[j].y2 && seg[i].y2>=seg[j].y1)) {
				cnt++;
			}
		}
	}
	sout<<cnt/2<<"\n";
//	cout<<cnt/2<<"\n";
}