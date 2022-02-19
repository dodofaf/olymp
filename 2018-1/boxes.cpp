#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>
#include <memory.h>

using namespace std;


int main(int argc, char**argv) 
{
	string line;

  	fstream sin("boxes.in", sin.in);

	getline(sin, line);
	istringstream iss(line);

	int n, m;
	iss >> n >> m;
	vector<int> k;
	k.resize(m);
	for (int i=0;i<m;i++) {
		getline(sin, line);
		istringstream iss(line);
    	iss>>k[i];
	}

    sort(k.begin(), k.end(), [](int a, int b) {
        return a < b;
    });

    bool b = true;
    int i = 0;

    while (b && i<m) {
    	if (k[i]<= n){
    		n -= k[i];
    	} else {b=false;}
    	i++;
    }

    fstream sout("boxes.out", sout.out);
    sout<<i-!b<<endl;

	return 0;
}