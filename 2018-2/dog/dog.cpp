#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include <string>
#include <set>

using namespace std;

int main()
{
	string line;
	fstream sin("dog.in", sin.in);
//	fstream sin("1.tst", sin.in);
	getline(sin, line);
	istringstream iss(line);
	int a, b, c, d;
	vector<int> ar(3);
	iss>>a>>b>>c>>d;
	getline(sin, line);
	istringstream iss1(line);
	iss1>>ar[0]>>ar[1]>>ar[2];
	fstream sout("dog.out", sout.out);
	for (int i=0;i<3;i++) {
		int cnt = 0;
		if ((ar[i]-1)%(a+b)<a){
			cnt++;
		}
		if ((ar[i]-1)%(c+d)<c){
			cnt++;
		}
		sout<<cnt<<"\n";
//		cout<<cnt<<"\n";
	}
}