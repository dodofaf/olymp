#include <iostream> 
#include <map>

using namespace std;

long long ar[4][5];
short int x1=-1;
short int y1=0;
short int x2=-1;
short int y2=0;
map<long long, long long> mem;
long long a = 0;
int res = 2e9;
int cnt = 0;

void ch(short int x, short int y, short int d1, short int d2)
{
	long long d = (a&(7LL<<(3*(x+d1+4*(y+d2)))))>>(3*(x+d1+4*(y+d2)));
	a = (a&(~((7LL<<(3*(x+d1+4*(y+d2)))))));
	a = (a|(d<<(3*(x+4*y))));
}

void de()
{
	long long x = a;
	for (int i=0;i<5;++i) {
		for (int j=0;j<4;++j) {
			cout<<ar[j][i]<<' ';		
		}
		cout<<'\n';
	}
	cout<<'\n';
}

void bf()
{
//	cout<<cnt<<'\n';
	++cnt;
	auto i = mem.insert({a, 1000000000}).first;
	if (cnt >= res) {
		--cnt;
		return;
	}

//	de();

	if (abs(x1-x2) == 1 && y1==y2) {
		if (y1>0) {
			if (ar[x1][y1-1] == 3 && ar[x2][y2-1] == 3) {
				ch(x1, y1, 0, -1);
				swap(ar[x1][y1], ar[x1][y1-1]);
				--y1;
				ch(x2, y2, 0, -1);
				swap(ar[x2][y2], ar[x2][y2-1]);
				--y2;
				auto itr = mem.find(a);
				if (itr==mem.end()) bf();
				else if (cnt+itr->second<res) res = cnt+itr->second;
				long long x = mem[a];
				ch(x2, y2, 0, 1);
				swap(ar[x2][y2], ar[x2][y2+1]);
				++y2;
				ch(x1, y1, 0, 1);
				swap(ar[x1][y1], ar[x1][y1+1]);
				++y1;
				i->second = min(i->second, x+1);
			}
			if (ar[x1][y1-1] == 4 && ar[x2][y2-1] == 4) {
				ch(x1, y1, 0, -2);
				swap(ar[x1][y1], ar[x1][y1-2]);
				y1-=2;
				ch(x2, y2, 0, -2);
				swap(ar[x2][y2], ar[x2][y2-2]);
				y2-=2;
				auto itr = mem.find(a);
				if (itr==mem.end()) bf();
				else if (cnt+itr->second<res) res = cnt+itr->second;
				long long x = mem[a];
				ch(x2, y2, 0, 2);
				swap(ar[x2][y2], ar[x2][y2+2]);
				y2+=2;
				ch(x1, y1, 0, 2);
				swap(ar[x1][y1], ar[x1][y1+2]);
				y1+=2;
				i->second = min(i->second, x+1);
			}
		}
		if (y1<3) {
			if (ar[x1][y1+1] == 3 && ar[x2][y2+1] == 3) {
				ch(x1, y1, 0, 1);
				swap(ar[x1][y1], ar[x1][y1+1]);
				++y1;
				ch(x2, y2, 0, 1);
				swap(ar[x2][y2], ar[x2][y2+1]);
				++y2;
				auto itr = mem.find(a);
				if (itr==mem.end()) bf();
				else if (cnt+itr->second<res) res = cnt+itr->second;
				long long x = mem[a];
				ch(x2, y2, 0, -1);
				swap(ar[x2][y2], ar[x2][y2-1]);
				--y2;
				ch(x1, y1, 0, -1);
				swap(ar[x1][y1], ar[x1][y1-1]);
				--y1;
				i->second = min(i->second, x+1);
			}
			if (ar[x1][y1+1] == 4 && ar[x2][y2+1] == 4) {
				ch(x1, y1, 0, 2);
				swap(ar[x1][y1], ar[x1][y1+2]);
				y1+=2;
				ch(x2, y2, 0, 2);
				swap(ar[x2][y2], ar[x2][y2+2]);
				y2+=2;
				long long x;
				if (((a>>3)&(36LL)) == 36) {
//					cout<<"-------------\n";
//					for (long long i=0, f=a;i<64;++i) cout<<(f&1), f>>=1;
//					cout<<'\n';
					if (res>cnt) res = cnt;
					x = 0;
					mem.insert({a, 0LL});
					--cnt;
					ch(x2, y2, 0, -2);
					swap(ar[x2][y2], ar[x2][y2-2]);
					y2-=2;
					ch(x1, y1, 0, -2);
					swap(ar[x1][y1], ar[x1][y1-2]);
					y1-=2;
					i->second = min(i->second, x+1);
					return;
				} else {
					auto itr = mem.find(a);
					if (itr==mem.end()) bf();
					else if (cnt+itr->second<res) res = cnt+itr->second;
					x = mem[a];
				}
				ch(x2, y2, 0, -2);
				swap(ar[x2][y2], ar[x2][y2-2]);
				y2-=2;
				ch(x1, y1, 0, -2);
				swap(ar[x1][y1], ar[x1][y1-2]);
				y1-=2;
				i->second = min(i->second, x+1);
			}
		}
	}
	if (abs(y1-y2) == 1 && x1==x2) {
		if (y1>0) {
			if (ar[x1-1][y1] == 3 && ar[x2-1][y2] == 3) {
				ch(x1, y1, -1, 0);
				swap(ar[x1][y1], ar[x1-1][y1]);
				--x1;
				ch(x2, y2, -1, 0);
				swap(ar[x2][y2], ar[x2-1][y2]);
				--x2;
				auto itr = mem.find(a);
				if (itr==mem.end()) bf();
				else if (cnt+itr->second<res) res = cnt+itr->second;
				long long x = mem[a];
				ch(x2, y2, 1, 0);
				swap(ar[x2][y2], ar[x2+1][y2]);
				++x2;
				ch(x1, y1, 1, 0);
				swap(ar[x1][y1], ar[x1+1][y1]);
				++x1;
				i->second = min(i->second, x+1);
			}
			if (ar[x1-1][y1] == 4 && ar[x2-1][y2] == 4) {
				ch(x1, y1, -2, 0);
				swap(ar[x1][y1], ar[x1-2][y1]);
				x1-=2;
				ch(x2, y2, -2, 0);
				swap(ar[x2][y2], ar[x2-2][y2]);
				x2-=2;
				long long x;
				if (((a>>3)&(36LL)) == 36) {
//					cout<<"-------------\n";
//					for (long long i=0, f=a;i<64;++i) cout<<(f&1), f>>=1;
//					cout<<'\n';
					if (res>cnt) res = cnt;
					x = 0;
					mem.insert({a, 0LL});
					--cnt;
					ch(x2, y2, 2, 0);
					swap(ar[x2][y2], ar[x2+2][y2]);
					x2+=2;
					ch(x1, y1, 2, 0);
					swap(ar[x1][y1], ar[x1+2][y1]);
					x1+=2;
					i->second = min(i->second, x+1);
					return;
				} else {
					auto itr = mem.find(a);
					if (itr==mem.end()) bf();
					else if (cnt+itr->second<res) res = cnt+itr->second;
					x = mem[a];
				}
				ch(x2, y2, 2, 0);
				swap(ar[x2][y2], ar[x2+2][y2]);
				x2+=2;
				ch(x1, y1, 2, 0);
				swap(ar[x1][y1], ar[x1+2][y1]);
				x1+=2;
				i->second = min(i->second, x+1);
			}
		}
		if (y1<3) {
			if (ar[x1+1][y1] == 3 && ar[x2+1][y2] == 3) {
				ch(x1, y1, 1, 0);
				swap(ar[x1][y1], ar[x1+1][y1]);
				++x1;
				ch(x2, y2, 1, 0);
				swap(ar[x2][y2], ar[x2+1][y2]);
				++x2;
				auto itr = mem.find(a);
				if (itr==mem.end()) bf();
				else if (cnt+itr->second<res) res = cnt+itr->second;
				long long x = mem[a];
				ch(x2, y2, -1, 0);
				swap(ar[x2][y2], ar[x2-1][y2]);
				--x2;
				ch(x1, y1, -1, 0);
				swap(ar[x1][y1], ar[x1-1][y1]);
				--x1;
				i->second = min(i->second, x+1);
			}
			if (ar[x1+1][y1] == 4 && ar[x2+1][y2] == 4) {
				ch(x1, y1, 2, 0);
				swap(ar[x1][y1], ar[x1+2][y1]);
				x1+=2;
				ch(x2, y2, 2, 0);
				swap(ar[x2][y2], ar[x2+2][y2]);
				x2+=2;
				long long x;
				if (((a>>3)&(36LL)) == 36) {
//					cout<<"-------------\n";
//					for (long long i=0, f=a;i<64;++i) cout<<(f&1), f>>=1;
//					cout<<'\n';
					if (res>cnt) res = cnt;
					x = 0;
					mem.insert({a, 0LL});
					--cnt;
					ch(x2, y2, -2, 0);
					swap(ar[x2][y2], ar[x2+2][y2]);
					x2-=2;
					ch(x1, y1, -2, 0);
					swap(ar[x1][y1], ar[x1-2][y1]);
					x1-=2;
					i->second = min(i->second, x+1);
					return;
				} else {
					auto itr = mem.find(a);
					if (itr==mem.end()) bf();
					else if (cnt+itr->second<res) res = cnt+itr->second;
					x = mem[a];
				}
				ch(x2, y2, -2, 0);
				swap(ar[x2][y2], ar[x2-2][y2]);
				x2-=2;
				ch(x1, y1, -2, 0);
				swap(ar[x1][y1], ar[x1-2][y1]);
				x1-=2;
				i->second = min(i->second, x+1);
			}
		}
	}

	if (x1>0) {
		if (ar[x1-1][y1] == 2) {
			ch(x1, y1, -2, 0);
			swap(ar[x1][y1], ar[x1-2][y1]);
			x1-=2;
			auto itr = mem.find(a);
			if (itr==mem.end()) bf();
			else if (cnt+itr->second<res) res = cnt+itr->second;
			long long x = mem[a];
			ch(x1, y1, 2, 0);
			swap(ar[x1][y1], ar[x1+2][y1]);
			x1+=2;
			i->second = min(i->second, x+1);
		}
		if (ar[x1-1][y1] == 1) {
			ch(x1, y1, -1, 0);
			swap(ar[x1][y1], ar[x1-1][y1]);
			--x1;
			auto itr = mem.find(a);
			if (itr==mem.end()) bf();
			else if (cnt+itr->second<res) res = cnt+itr->second;
			long long x = mem[a];
			ch(x1, y1, 1, 0);
			swap(ar[x1][y1], ar[x1+1][y1]);
			++x1;
			i->second = min(i->second, x+1);
		}
	}
	if (x1<3) {
		if (ar[x1+1][y1] == 2) {
			ch(x1, y1, 2, 0);
			swap(ar[x1][y1], ar[x1+2][y1]);
			x1+=2;
			auto itr = mem.find(a);
			if (itr==mem.end()) bf();
			else if (cnt+itr->second<res) res = cnt+itr->second;
			long long x = mem[a];
			ch(x1, y1, -2, 0);
			swap(ar[x1][y1], ar[x1-2][y1]);
			x1-=2;
			i->second = min(i->second, x+1);
		}
		if (ar[x1+1][y1]== 1) {
			ch(x1, y1, 1, 0);
			swap(ar[x1][y1], ar[x1+1][y1]);
			++x1;
			auto itr = mem.find(a);
			if (itr==mem.end()) bf();
			else if (cnt+itr->second<res) res = cnt+itr->second;
			long long x = mem[a];
			ch(x1, y1, -1, 0);
			swap(ar[x1][y1], ar[x1-1][y1]);
			--x1;
			i->second = min(i->second, x+1);
		}
	}
	if (x2>0) {
		if (ar[x2-1][y2] == 2) {
			ch(x2, y2, -2, 0);
			swap(ar[x2][y2], ar[x2-2][y2]);
			x2-=2;
			auto itr = mem.find(a);
			if (itr==mem.end()) bf();
			else if (cnt+itr->second<res) res = cnt+itr->second;
			long long x = mem[a];
			ch(x2, y2, 2, 0);
			swap(ar[x2][y2], ar[x2+2][y2]);
			x2+=2;
			i->second = min(i->second, x+1);
		}
		if (ar[x2-1][y2] == 1) {
			ch(x2, y2, -1, 0);
			swap(ar[x2][y2], ar[x2-1][y2]);
			--x2;
			auto itr = mem.find(a);
			if (itr==mem.end()) bf();
			else if (cnt+itr->second<res) res = cnt+itr->second;
			long long x = mem[a];
			ch(x2, y2, 1, 0);
			swap(ar[x2][y2], ar[x2+1][y2]);
			++x2;
			i->second = min(i->second, x+1);
		}
	}
	if (x2<3) {
		if (ar[x2+1][y2] == 2) {
			ch(x2, y2, 2, 0);
			swap(ar[x2][y2], ar[x2+2][y2]);
			x2+=2;
			auto itr = mem.find(a);
			if (itr==mem.end()) bf();
			else if (cnt+itr->second<res) res = cnt+itr->second;
			long long x = mem[a];
			ch(x2, y2, -2, 0);
			swap(ar[x2][y2], ar[x2-2][y2]);
			x2-=2;
			i->second = min(i->second, x+1);
		}
		if (ar[x2+1][y2] == 1) {
			ch(x2, y2, 1, 0);
			swap(ar[x2][y2], ar[x2+1][y2]);
			++x2;
			auto itr = mem.find(a);
			if (itr==mem.end()) bf();
			else if (cnt+itr->second<res) res = cnt+itr->second;
			long long x = mem[a];
			ch(x2, y2, -1, 0);
			swap(ar[x2][y2], ar[x2-1][y2]);
			--x2;
			i->second = min(i->second, x+1);
		}
	}
	if (y1>0) {
		if (ar[x1][y1-1] == 2) {
			ch(x1, y1, 0, -2);
			swap(ar[x1][y1], ar[x1][y1-2]);
			y1-=2;
			auto itr = mem.find(a);
			if (itr==mem.end()) bf();
			else if (cnt+itr->second<res) res = cnt+itr->second;
			long long x = mem[a];
			ch(x1, y1, 0, 2);
			swap(ar[x1][y1], ar[x1][y1+2]);
			y1+=2;
			i->second = min(i->second, x+1);
		}
		if (ar[x1][y1-1] == 1) {
			ch(x1, y1, 0, -1);
			swap(ar[x1][y1], ar[x1][y1-1]);
			--y1;
			auto itr = mem.find(a);
			if (itr==mem.end()) bf();
			else if (cnt+itr->second<res) res = cnt+itr->second;
			long long x = mem[a];
			ch(x1, y1, 0, 1);
			swap(ar[x1][y1], ar[x1][y1+1]);
			++y1;
			i->second = min(i->second, x+1);
		}
	}
	if (y1<3) {
		if (ar[x1][y1+1] == 2) {
			ch(x1, y1, 0, 2);
			swap(ar[x1][y1], ar[x1][y1+2]);
			y1+=2;
			auto itr = mem.find(a);
			if (itr==mem.end()) bf();
			else if (cnt+itr->second<res) res = cnt+itr->second;
			long long x = mem[a];
			ch(x1, y1, 0, -2);
			swap(ar[x1][y1], ar[x1][y1-2]);
			y1-=2;
			i->second = min(i->second, x+1);
		}
		if (ar[x1][y1+1] == 1) {
			ch(x1, y1, 0, 1);
			swap(ar[x1][y1], ar[x1][y1+1]);
			++y1;
			auto itr = mem.find(a);
			if (itr==mem.end()) bf();
			else if (cnt+itr->second<res) res = cnt+itr->second;
			long long x = mem[a];
			ch(x1, y1, 0, -1);
			swap(ar[x1][y1], ar[x1][y1-1]);
			--y1;
			i->second = min(i->second, x+1);
		}
	}
	if (y2>0) {
		if (ar[x2][y2-1] == 2) {
			ch(x2, y2, 0, -2);
			swap(ar[x2][y2], ar[x2][y2-2]);
			y2-=2;
			auto itr = mem.find(a);
			if (itr==mem.end()) bf();
			else if (cnt+itr->second<res) res = cnt+itr->second;
			long long x = mem[a];
			ch(x2, y2, 0, 2);
			swap(ar[x2][y2], ar[x2][y2+2]);
			y2+=2;
			i->second = min(i->second, x+1);
		}
		if (ar[x2][y2-1] == 1) {
			ch(x2, y2, 0, -1);
			swap(ar[x2][y2], ar[x2][y2-1]);
			--y2;
			auto itr = mem.find(a);
			if (itr==mem.end()) bf();
			else if (cnt+itr->second<res) res = cnt+itr->second;
			long long x = mem[a];
			ch(x2, y2, 0, 1);
			swap(ar[x2][y2], ar[x2][y2+1]);
			++y2;
			i->second = min(i->second, x+1);
		}
	}
	if (y2<3) {
		if (ar[x2][y2+1] == 2) {
			ch(x2, y2, 0, 2);
			swap(ar[x2][y2], ar[x2][y2+2]);
			y2+=2;
			auto itr = mem.find(a);
			if (itr==mem.end()) bf();
			else if (cnt+itr->second<res) res = cnt+itr->second;
			long long x = mem[a];
			ch(x2, y2, 0, -2);
			swap(ar[x2][y2], ar[x2][y2-2]);
			y2-=2;
			i->second = min(i->second, x+1);
		}
		if (ar[x2][y2+1] == 1) {
			ch(x2, y2, 0, 1);
			swap(ar[x2][y2], ar[x2][y2+1]);
			++y2;
			auto itr = mem.find(a);
			if (itr==mem.end()) bf();
			else if (cnt+itr->second<res) res = cnt+itr->second;
			long long x = mem[a];
			ch(x2, y2, 0, -1);
			swap(ar[x2][y2], ar[x2][y2-1]);
			--y2;
			i->second = min(i->second, x+1);
		}
	}

	--cnt;
}

int main()
{
	for (int i=0;i<5;++i) {
		for (int j=0;j<4;++j) {
			cin>>ar[j][i];
			a = (a|(ar[j][i]<<(3*(j+(4*i)))));
			if (ar[j][i] == 0) {
				if (x1==-1) {
					x1 = j;
					y1 = i;
				} else {
					x2 = j;
					y2 = i;
				}
			}
		}
	}
	bf();
	auto itr = mem.find(a);
	if (res > 1e9) cout<<"-1\n";
	else cout<<res<<'\n';
}
