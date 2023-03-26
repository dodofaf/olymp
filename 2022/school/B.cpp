#include <iostream>
#include <string>
#include <time.h>

using namespace std;

int random(int m) 
{
	return rand() % m;
}

int bf(string s)
{
	int n = s.length(), res = n;
	for (int i=0;i<n;++i) {
		if (s[i] == 'F') continue;
		int cnt = 0;
		for (int j=i;j<n;++j) {
			if (s[i] == 'F') cnt++;
			else if (res>i+2*cnt+n-j) res = i+2*cnt+n-j;
		}
		if (s[n-1] == 'P' && res>i+2*cnt) res = i+2*cnt;
	}
	return res;
}

int ar[100000001] = {0};

int main()
{
#if 1
	string s;
	getline(cin, s);
	int n = s.length();
#else
	int t = time(NULL);
	cout<<t<<'\n';
	srand(t);
	string s;
	int n = 10;
	for (int i=0;i<n;++i) {
		if (random(2)-1) s.push_back('P');
		else s.push_back('F');
	}
	cout<<"bf: "<<bf(s)<<'\n';
#endif
	cout<<"bf: "<<bf(s)<<'\n';
	int cnt = 0;
	ar[0] = 0;
	for (int i=1;i<=n;++i) {
		if (s[i-1] == 'F') ++cnt;
		ar[i] = min(ar[i-1], i-2*cnt);
	}
	int res = n;
	for (int i=n;i>1;--i) {
		if (s[i-1] == 'F') --cnt;
		if (res>ar[i-1]+n-i+2*cnt) res = ar[i-1]+n-i+2*cnt;
	}
	cout<<res<<'\n';
	return 0;
}
