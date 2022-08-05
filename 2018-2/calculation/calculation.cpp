#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main()
{
	string line;
	fstream sin("calculation.in", sin.in);
	fstream sout("calculation.out", sout.out);
	getline(sin, line);
	istringstream iss(line);
	vector<int> ar(4), cnt(4, 0), cnt1(4, 0), nom = {5, 10, 20, 50};
	int s;
	iss>>ar[0]>>ar[1]>>ar[2]>>ar[3]>>s;
	int s1 = s;
	vector<int> ar1(ar);
	for (int i=3;i>-1;i--) {
		int m = min(s/nom[i], ar[i]);
		s-=nom[i]*m;
		cnt[i]=m;
		if (s==0) {
			sout<<cnt[0]<<' '<<cnt[1]<<' '<<cnt[2]<<' '<<cnt[3]<<' '<<cnt[0]+cnt[1]+cnt[2]+cnt[3]<<"\n";			
			break;
		}
	}
	if (s!=0) {
		ar1[3]--;
		for (int i=3;i>-1;i--) {
			int m = min(s1/nom[i], ar1[i]);
			s1-=nom[i]*m;
			cnt1[i]=m;
			if (s1==0) {
				sout<<cnt1[0]<<' '<<cnt1[1]<<' '<<cnt1[2]<<' '<<cnt1[3]<<' '<<cnt1[0]+cnt1[1]+cnt1[2]+cnt1[3]<<"\n";			
				break;
			}
		}
		if (s1 != 0) {
			sout<<"-1\n";	
		}
	}
}