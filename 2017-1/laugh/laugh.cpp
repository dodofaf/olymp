#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main()
{
	string line;
	fstream sin("laugh.in", sin.in);
	fstream sout("laugh.out", sout.out);
	getline(sin, line);
	istringstream iss(line);
	int n;
	iss>>n;
	string s;
	getline(sin, s);
	int max_laugh = 0, cnt = 0;
	if (s[0] == 'a' || s[0] == 'h') {
		cnt++;
	}
	for (int i=1;i<n;i++) {
		if (s[i] == 'a' || s[i] == 'h') {
			if (cnt == 0) {
				cnt++;
			} else {
				if ((s[i-1] == 'a' && s[i] == 'h') || (s[i] == 'a' && s[i-1] == 'h')) {
					cnt++;
				} else {
					if (cnt > max_laugh) {
						max_laugh = cnt;
					}
					cnt = 0;
					if (s[i] == 'a' || s[i] == 'h'){
						cnt++;
					}
				}
			}
		} else {
			if (cnt > max_laugh) {
				max_laugh = cnt;
			}
			cnt = 0;
		}
	}
	if (cnt > max_laugh) {
		max_laugh = cnt;
	}
	sout<<max_laugh<<"\n";
}
