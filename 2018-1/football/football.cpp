#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include <string>
#include <set>

using namespace std;

struct Segment
{
	int x1;
	int y1;
	int x2;
	int y2;
	int ind;
};

auto cmp = [](const Segment &a, const Segment &b)
{
    return a.x1 < b.x1 || (a.x1 == b.x1 && a.ind < b.ind);
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
	set<Segment, decltype(cmp)> sorted_by_x1(cmp);
	for (int i=0;i<q;i++) {
		getline(sin, line);
		istringstream iss(line);
		iss>>seg[i].x1>>seg[i].y1>>seg[i].x2>>seg[i].y2;
		seg[i].ind = i;
		sorted_by_x1.insert(seg[i]);
	}
	fstream sout("football.out", sout.out);
	long long cnt = 0;
	for (auto itr=sorted_by_x1.begin();itr!=sorted_by_x1.end();itr++) {
		Segment i = (*itr);
		Segment s;
		s.ind = -1;
		s.x1 = i.x2+1;
		auto itr_e = sorted_by_x1.lower_bound(s);
		auto itr1 = itr;
		itr1++;
		for (auto itr2=itr1;itr2!=itr_e;itr2++) {
			if (i.y1<=(*itr2).y2 && i.y2>=(*itr2).y1) {
				cnt++;
			}
		}
	}
	sout<<cnt<<"\n";
//	cout<<cnt<<"\n";
}