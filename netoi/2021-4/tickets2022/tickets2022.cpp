#include <bits/stdc++.h>

using namespace std;

int random(int m)
{
    return rand()%m;
}

static void solutio_nnk(const int k, const  int n, const  vector<vector<int>> train, const  vector<int> aces)
{
	long long cnt = 0;
	for (int i=0;i<n-2;i++) {
		if (aces[i] != 0){
			vector<int> free;
			free.reserve(k);
			int y = 0;
			for (int j=0;j<k;j++) {
				if (train[j][i] == 0) {
					free.push_back(j);
					y++;
				}
			}
			bool b = false; 
			for (int j=i+1;j<n;j++) {
				if (b) {
					cnt++;
				} else {
					for (int x=0;x<y;x++) {
						if (train[free[x]][j] == 1) {
							int tmp = free[x];
							free[x] = free[y-1];
							free[y-1] = tmp;
							y--;
							x--;	
						}
					}
//					cout<<i<<' '<<j<<' '<<y<<endl;
					if (y == 0) {
						b = true;
					}
				}
				if (aces[j] == 0) {
					break;
				}
			}
		}
	}
	cout<<cnt<<endl;
}

int main()
{
	int k, n, t;
#if 1
	cin>>k>>n>>t;
	vector<vector<int>> train(k, vector<int>(n, 0));
	vector<int> aces(n, k);
	for (int i=0;i<t;i++) {
		int p, s, f;
		cin>>p>>s>>f;
		p--;
		s--;
		f--;
		for(int j=s;j<f;j++) {
			train[p][j] = 1;
			aces[j]--;
		}
	}
#else
	t = time(NULL);
	t=1647098597;
	srand(t);
	cout<<"t="<<t<<endl;
	n = 3+random(12);
	k = 3+random(7);
	t = random(30);
	cout<<n<<' '<<k<<' '<<t<<endl;
	vector<vector<int>> train(k, vector<int>(n, 0));
	vector<vector<bool>> btrain(k, vector<bool>(n, true));
	vector<int> aces(n, k);
	for (int i=0;i<t;i++) {
		int p, s, f;
		p = random(k);
		s = random(n/2);
		f = s+1 + random(n/2);
		cout<<p<<' '<<s<<' '<<f<<endl;
		for(int j=s;j<f;j++) {
			train[p][j] = 1;
			if (btrain[p][j]) {
				aces[j]--;
				btrain[p][j] = false;
			}
		}
	}
#endif
	vector<int> pp(n, -1);
	pp[n-1] = 0;
	for (int i=0;i<k;i++){
		int x = 0;
		for (int j=n-2;j>-1;j--){
			x++;
			if (train[i][j] == 0) {
				if (pp[j] < x) {
					pp[j] = x;
				}
			} else {
				x = -1;
			}
		}
	}
	bool b = false;
	for (int i=n-1;i>-1;i--) {
		if (!b && i != 0 && pp[i]>=pp[i-1]) {
			b = true;
		} else {
			if (b) {
				pp[i]++;
			}
		}
	}
	int x = 0;
	long long cnt = 0;
	for (int i=n-1;i>-1;i--) {
		if (aces[i] == 0) {
			x=0;
		} else {
			cnt += x-pp[i];
		}
		x++;
	}
	cout<<cnt<<endl;
}