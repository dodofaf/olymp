#include <iostream>
#include <math.h>

using namespace std;

bool check(string &a, string &b)
{
	int len = a.length();
	for (int i=0;i<len;++i) {
		if (a[i]>b[i]) return false;
		if (a[i]<b[i]) return true;
	}
	return true;
}

int main()
{
	string n, n0;
	getline(cin, n);
	n0 = n;
	int len = n.length();
    for (int i=(len-1)/2;i>-1;--i) {
    	n[len-i-1] = n[i];
    }
    if (check(n,n0)) {
        for (int i=(len-1)/2;i>-1;--i) {
            if (n[i] != '9') {
                n[i]++;
                n[len-i-1] = n[i];
                break;
            } else {
                n[i] = '0';
                n[len-i-1] = '0';
            }
        }
        if (n[0] == '0') {
        	n[0] = '1';
        	n = n+"1";
        	len++;
        }
    }
    for (int i=len-1;i>-1;i--) cout<<n[i];
    cout<<'\n';
}