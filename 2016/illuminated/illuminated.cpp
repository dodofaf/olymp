#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main()
{
	string line;
	fstream sin("illuminated.in", sin.in);
	fstream sout("illuminated.out", sout.out);
	getline(sin, line);
	istringstream iss(line);
	int n;
	iss>>n;
	getline(sin, line);
	istringstream iss1(line);
	int mx = 0, res;
	for (int i=0;i<n;i++) {
		int h;
		iss1>>h;
		if (h>mx) {
			mx = h;
			res++;
		}
	}
	sout<<res;
}
