#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main()
{
	string line;
	fstream sin("lift.in", sin.in);
	fstream sout("lift.out", sout.out);
	int n, k, a, b;
	sin>>n>>k>>a>>b;
	sout<<(n+k-2)*b<<' '<<(n-1)*a;
}
