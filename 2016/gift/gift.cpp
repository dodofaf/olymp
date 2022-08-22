#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include <string>
#include <set>

#define f first
#define s second

using namespace std;

auto cmp = [](const pair<int, int> a, const pair<int, int> b)
{
	return a.f<b.f || (a.f==b.f && a.s<b.s);
};

int main()
{
	string line;
	fstream sin("gift.in", sin.in);
	fstream sout("gift.out", sout.out);
	getline(sin, line);
	istringstream iss(line);
	int n, x;
	iss>>n>>x;
	set<pair<int, int>, decltype(cmp)> sorted(cmp);
	getline(sin, line);
	istringstream iss1(line);
	for (int i=0;i<n;i++) {
		pair<int, int> p;
		iss1>>p.f;
		p.s = i;
		sorted.insert(p);
	}
	int res = 0;
	for (auto i=sorted.begin();i!=sorted.end();i++) {
		pair<int, int> p;
		p.f = x-(*i).f;
		p.s = n;
		auto itr = sorted.upper_bound(p);
		if (itr == sorted.begin()) {continue;}
		itr--;
		if ((*itr).s == (*i).s) {
			if (itr == sorted.begin()) {continue;}
			itr--;
		}
		int r = (*i).f + (*itr).f;
		if (r>res) {
			res = r;
		}
	}
	sout<<res;
}
