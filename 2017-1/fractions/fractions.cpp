#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int gcd(int a, int b)
{
	while (a != 0 && b!=0) {
		if (a>b) {
			a = a%b;
		} else {
			b = b%a;
		}
	}
	return a+b;
}

int main()
{
	string line;
	fstream sin("fractions.in", sin.in);
	fstream sout("fractions.out", sout.out);
	getline(sin, line);
	istringstream iss(line);
	int a, b, c, d;
	iss>>a>>b>>c>>d;
	int cnt = 0;
	bool flag = true;
	while (flag) {
		if (a*d > c*b) {
			cnt = 0;
			flag = false;
		} else {
			a++;
			b++;
			cnt++;
			int g = gcd(a, b);
			a = a/g;
			b = b/g;
			if (a == c && d == b) {
				flag = false;
			}
		}
	}
	sout<<cnt<<"\n";
}
