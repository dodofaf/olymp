#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct Paralelogram
{
	ll a;
	ll b;
	ll c;
};

auto cmp = [](const Paralelogram &a, const Paralelogram &b)
{
	return a.a < b.a || (a.a == b.a && a.b < b.b);
};

int main()
{
	ll v, s;
	cin>>v>>s;
	ll cr = cbrt(v), q = 2*v/s;
	bool bo = true;
	set<Paralelogram, decltype(cmp)> out(cmp);
	if (s%2 == 0) {
		if(cr>q) {
			for (ll a=q+1;a<=cr;a++) {
				if (v%a == 0) {
					double r = ((double)(s/2 - v/a))/(2*a);
					double b0 = r + sqrt(r*r - v/a);
					ll b = b0;
					if (b == b0 && a<=b) {
						if (v%(a*b) == 0) {
							ll c = (v/a)/b;
							if(a<=c) {
								bo = false;
								Paralelogram p;
								if (a != b && b != c && a != c) {
									p.a = a;
									p.b = b;
									p.c = c;
									out.insert(p);
									p.a = a;
									p.b = c;
									p.c = b;
									out.insert(p);
									p.a = b;
									p.b = a;
									p.c = c;
									out.insert(p);
									p.a = b;
									p.b = c;
									p.c = a;
									out.insert(p);
									p.a = c;
									p.b = a;
									p.c = b;
									out.insert(p);
									p.a = c;
									p.b = b;
									p.c = a;
									out.insert(p);
								}
								if(a == b && b == c) {
									p.a = a;
									p.b = b;
									p.c = c;
									out.insert(p);
								}
								if (a == b && b != c) {
									p.a = a;
									p.b = b;
									p.c = c;
									out.insert(p);
									p.a = a;
									p.b = c;
									p.c = b;
									out.insert(p);
									p.a = c;
									p.b = b;
									p.c = a;
									out.insert(p);
								}
								if (a == c && b != c) {
									p.a = a;
									p.b = b;
									p.c = c;
									out.insert(p);
									p.a = a;
									p.b = c;
									p.c = b;
									out.insert(p);
									p.a = b;
									p.b = a;
									p.c = c;
									out.insert(p);
								}
								if (b == c && b != a) {
									p.a = a;
									p.b = b;
									p.c = c;
									out.insert(p);
									p.a = b;
									p.b = a;
									p.c = c;
									out.insert(p);
									p.a = b;
									p.b = c;
									p.c = a;
									out.insert(p);
								}
							}
						}
					}
				} 
			}
		}
		for (auto i=out.begin();i!=out.end();++i) {
			cout<<i->a<<' '<<i->b<<' '<<i->c<<' ';
		}
	}
	if (bo)  {
		cout<<"0 0 0";
	}
	cout<<endl;
}