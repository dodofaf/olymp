#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <time.h>

using namespace std;

#define f first
#define s second

int random(int m) 
{
	return rand() % m + 1;
}

long long bf(pair<long, long> ar[], int n)
{
	vector<int> q(n, 1);
	long long x = 0, y = 0;
	for (int i=0;i<n;++i) {
		x+=ar[i].f;
		y+=ar[i].s;
	}
	long long mx = x*x+y*y;
	while (q[0]) {
		int i = n-1;
		while (i>0 && q[i] == 0) {
			x+=2*ar[i].f;
			y+=2*ar[i].s;
			q[i] = 1;
			--i;
		}
		q[i] = 0;
		x-=2*ar[i].f;
		y-=2*ar[i].s;
		if (mx < x*x+y*y) mx = x*x+y*y;

	} 
//	cout<<"bf "<<mx*25<<'\n';
	return mx*25;
}

bool cmp(const pair<long, long> &a, const pair<long, long> &b)
{
	if (a.f<0 && b.f>0) return false;
	if (a.f>0 && b.f<0) return true;
	if (a.f == 0) return (b.f<0);
	if (b.f == 0) return (a.f>0);
	if (a.f<0) return a.f*b.s>a.s*b.f;
	return a.f*b.s>a.s*b.f;
}

long long test(pair<long, long> ar[], int n)
{
	long long x = 0, y = 0;
	for (int i=0;i<n;++i) {
		if (ar[i].s<0 || (ar[i].s==0 && ar[i].f<0)) {
			ar[i].f = -ar[i].f;
			ar[i].s = -ar[i].s;
		}
		x+=ar[i].f;
		y+=ar[i].s;
	}
	sort(ar, ar+n, cmp);
	//for (int i=0;i<n;++i) cout<<ar[i].f<<' '<<ar[i].s<<'\n';
	long long mx = x*x+y*y;
	//cout<<mx<<'\n';
	for (int i=n;i<2*n;++i) {
		//ar[i].f = (1-2*(i/n == 1))*ar[i-n].f;
		//ar[i].s = (1-2*(i/n == 1))*ar[i-n].s;
		x-=2*ar[i%n].f;
		y-=2*ar[i%n].s;
		if (mx < x*x+y*y) mx = x*x+y*y;
	}
	for (int i=2*n;i<3*n;++i) {
		//ar[i].f = (1-2*(i/n == 1))*ar[i-n].f;
	//ar[i].s = (1-2*(i/n == 1))*ar[i-n].s;
		x+=2*ar[i%n].f;
		y+=2*ar[i%n].s;
		if (mx < x*x+y*y) mx = x*x+y*y;
	}
//	cout<<mx*25<<'\n';
	return mx*25;
}

void rand_gen_test(pair<long, long> ar[], int &n, int t)
{
//	cout<<t<<'\n';
	srand(t);
	n = 50;
	int k = 50;
	for (int i=0;i<n;++i) {
		ar[i].f = random(2*k)-k;
		ar[i].s = random(2*k)-k;
//		cout<<ar[i].f<<' '<<ar[i].s<<'\n';
	}
}

pair<long, long> ar[100000];

int main()
{
	int n;
#if 1
	cin>>n;
	for (int i=0;i<n;++i) {
		cin>>ar[i].f>>ar[i].s;
	}
#else
	int t = time(NULL);
	cout<<t<<'\n';
//	t = 1674390974;
	rand_gen_test(ar, n, t);
	int i;
	for (i = 0;i<1000000 && (bf(ar, n)==test(ar, n));++t, ++i) rand_gen_test(ar, n, t);
	cout<<i<<'\n';
	cout<<t<<'\n';
#endif
	cout<<test(ar, n)<<'\n';
}