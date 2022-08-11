#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main()
{
	string line;
	fstream sin("number.in", sin.in);
	fstream sout("number.out", sout.out);
	getline(sin, line);
	istringstream iss(line);
	long long n;
	iss>>n;
	int cnt = 0;
	while (n != 1) {
		if (n%2 == 0) {
			n /= 2;
			cnt++;
		} else {
			n--;
		}
	}
	long long res = 1;
	for (int i=0;i<cnt;i++) {
		res *= 2;
	}
	cout<<res<<"\n";
	sout<<res<<"\n";
}
