#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include <string>
#include <set>

using namespace std;

void output_ar(int n, vector<int> &ar) {
	for(int i=0;i<n;i++){cout<<ar[i]<<' ';}
	cout<<"\n";
}

int main()
{
	string line;
//	fstream sin("radioactive.in", sin.in);
	fstream sin("1.tst", sin.in);
	getline(sin, line);
	istringstream iss(line);
	int n, c;
	iss>>n>>c;
	long long cnt = 1;
	int n0 = n;
	for (int i=1;i<=n0;i++) {
		n = i+1;
		vector<int> q(i+1, -1);
		int y = 0;
		while (y != -1) {
			n+=q[y]+1;
			if (q[y] == -1) {
				q[y]++;
			}
			q[y]++;
			if (q[y] < min(n, c+1)) {
				n-=q[y]+1;
				y++;
			}
			if (q[y] == min(n, c+1) || n == 0) {
				q[y] = -1;
				y--;
				cnt++;
				output_ar(i+1, q);
			}
		}
	}
	cnt-=n0;
//	fstream sout("radioactive.out", sout.out);
//	sout<<cnt<<"\n";
	cout<<cnt<<"\n";
}