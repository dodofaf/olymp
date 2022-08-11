#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main()
{
	string line1, line2;;
	fstream sin("degree.in", sin.in);
	fstream sout("degree.out", sout.out);
	getline(sin, line1);
	getline(sin, line2);
	int res = 0, l1 = line1.length(), l2 = line2.length();
	vector<vector<int>> cnt(26, vector<int>(26, 0));
	for (int i=0;i<l1-1;i++) {
		cnt[(int)line1[i] - (int)'A'][(int)line1[i+1] - (int)'A']++;
	}
	for (int i=0;i<l2-1;i++) {
		if (cnt[(int)line2[i] - (int)'A'][(int)line2[i+1] - (int)'A'] > 0) {
			res+=cnt[(int)line2[i] - (int)'A'][(int)line2[i+1] - (int)'A'];
			cnt[(int)line2[i] - (int)'A'][(int)line2[i+1] - (int)'A'] = 0;
		}
	}
	sout<<res<<"\n";
}
