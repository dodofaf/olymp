#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main()
{
	string line;
	fstream sin("candies.in", sin.in);
	fstream sout("candies.out", sout.out);
	getline(sin, line);
	istringstream iss(line);
	int n;
	iss>>n;
	getline(sin, line);
	istringstream iss1(line);
	vector<int> types(n+1);
	for(int i=0;i<n;i++) {
		iss1>>types[i];
	}
	types[n] = -1;
	int type1 = types[0], type2 = -1, cnt = 1, max = 0, cnt_l = 1;
	for (int i=1;i<=n;i++) {
		if (types[i] == types[i-1]){
			cnt_l++;
			cnt++;
		} else{
			if (type2 == -1) {
				cnt++;
				cnt_l=1;
				type2 = types[i];
			} else {
				if (types[i] == type1 || types[i] == type2) {
					cnt_l = 1;
					cnt++;
				} else {
					if (cnt>max) {
						max = cnt;
					}
					cnt = cnt_l+1;
					cnt_l = 1;
					type1 = types[i-1];
					type2 = types[i];
				}
			}
		}
	}
	sout<<max<<"\n";
}
