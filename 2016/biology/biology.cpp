#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main()
{
	string line;
	fstream sin("biology.in", sin.in);
	fstream sout("biology.out", sout.out);
	getline(sin, line);
	istringstream iss(line);
	int n, m;
	iss>>n>>m;
	vector<string> pic(n);
	int res = 0;
	for (int i=0;i<n;i++) {
		int cnt = 0;
		getline(sin, pic[i]);
		for (int j=0;j<m;j++) {
			if (pic[i][j] == '.') {
				cnt++;
			} else {
				res += cnt*(cnt-1)/2;
				cnt = 0;
			}
		}
		res += cnt*(cnt-1)/2;
	}
	for (int i=0;i<m;i++) {
		int cnt = 0;
		for (int j=0;j<n;j++) {
			if (pic[j][i] == '.') {
				cnt++;
			} else {
				res += cnt*(cnt-1)/2;
				cnt = 0;
			}
		}
		res += cnt*(cnt-1)/2;
	}
	sout<<res;
}
