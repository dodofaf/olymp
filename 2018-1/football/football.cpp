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
	int count;
};

auto cmp = [](const Segment &a, const Segment &b)
{
    return a.x1 < b.x1 || (a.x1 == b.x1 && a.y1 < b.y1) || (a.x1 == b.x1 && a.y1 == b.y1 && a.x2 < b.x2) || (a.x1 == b.x1 && a.y1 == b.y1 && a.x2 == b.x2 && a.y2 < b.y2);
};

int main()
{
	string line;
	fstream sin("football.in", sin.in);
//	fstream sin("2.tst", sin.in);
	getline(sin, line);
	istringstream iss(line);
	int n, m, q;
	iss>>n>>m;
	getline(sin, line);
	istringstream iss1(line);
	iss1>>q;
	vector<Segment> seg(q);
	set<Segment, decltype(cmp)> sorted_by_x1(cmp);
	long long cnt = 0;
	for (int i=0;i<q;i++) {
		getline(sin, line);
		istringstream iss(line);
		iss>>seg[i].x1>>seg[i].y1>>seg[i].x2>>seg[i].y2;
		auto itr = sorted_by_x1.find(seg[i]);
		if (itr == sorted_by_x1.end()) {
			seg[i].count = 1;
			sorted_by_x1.insert(seg[i]);
		} else {
			Segment s = (*itr);
			cnt+=s.count;
			s.count++;
			sorted_by_x1.erase(itr);
			sorted_by_x1.insert(s);
		}
	}
	fstream sout("football.out", sout.out);
	for (auto itr=sorted_by_x1.begin();itr!=sorted_by_x1.end();itr++) {
		Segment i = (*itr);
		auto itr1 = itr;
		itr1++;
		for (auto itr2=itr1;itr2!=sorted_by_x1.end() && (*itr2).x1<=i.x2;itr2++) {
			if (i.y1<=(*itr2).y2 && i.y2>=(*itr2).y1) {
				cnt+=i.count*(*itr2).count;
			}
		}
	}
	sout<<cnt<<"\n";
//	cout<<cnt<<"\n";
}