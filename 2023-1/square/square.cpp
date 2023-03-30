#include <iostream>
#include <iterator>
#include <cstdio>
#include <map>
#include <cstdint>

#define f first
#define s second

using namespace std;

__int128_t gcd(__int128_t a, __int128_t b)
{
    while (a!=0 && b!=0) {
        if (a>=b) a%=b;
        else b%=a;
    }
    return a+b;
}

pair<__int128_t, __int128_t> ar[1000][1000];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    int n;
    cin>>n;
    
    for (int i=0;i<n;++i) {
        int a;
        cin>>a;
        ar[i][i].f = a;
        ar[i][i].s=1;
    }
    
    for (int i=0;i<n-1;++i) {
        int a;
        cin>>a;
        ar[i+1][i].f = a;
        ar[i+1][i].s=1;
    }
    
    int p, q;
    cin>>p>>q;
    __int128_t g;
    if (p<q) {
        for (int i=0;i<q-p;++i){
            for (int x=p-1, y=p+i;y<q;++y, ++x) {
                ar[x][y].f = ar[x+1][y].f * ar[x][y-1].f * ar[x+1][y-1].s;
                ar[x][y].s = ar[x+1][y].s * ar[x][y-1].s * ar[x+1][y-1].f;
                g = gcd(ar[x][y].f, ar[x][y].s);
                ar[x][y].f/=g;
                ar[x][y].s/=g;
            }
        }
    }
    else if (p>q+1) {
        for (int i=1;i<p-q;++i){
            for (int x=q+i, y=q-1;x<p;++y, ++x) {
                ar[x][y].f = ar[x-1][y].f * ar[x][y+1].f * ar[x-1][y+1].s;
                ar[x][y].s = ar[x-1][y].s * ar[x][y+1].s * ar[x-1][y+1].f;
                g = gcd(ar[x][y].f, ar[x][y].s);
                ar[x][y].f/=g;
                ar[x][y].s/=g;
            }
        }
    }
    
    if (ar[p-1][q-1].f == 1 && ar[p-1][q-1].s == 1) cout<<"1 1\n";
    else {
        map<int, int> m;
        if (ar[p-1][q-1].f!=1) {
            int cnt = 0;
            while (!(ar[p-1][q-1].f&1)) {
                cnt++;
                ar[p-1][q-1].f>>=1;
            }
            if (cnt) m[2] = cnt;
            for (long long i=3;i*i<=ar[p-1][q-1].f;i+=2) {
                cnt = 0;
                while (ar[p-1][q-1].f%i==0) {
                    cnt++;
                    ar[p-1][q-1].f/=i;
                }
                if (cnt) m[(int)i] = cnt;
            }
            if (ar[p-1][q-1].f!=1) m[(int)ar[p-1][q-1].f] = 1;
        }
        
        if (ar[p-1][q-1].s!=1) {
            int cnt = 0;
            while (!(ar[p-1][q-1].s&1)) {
                cnt++;
                ar[p-1][q-1].s>>=1;
            }
            if (cnt) m[2] = -cnt;
            for (long long i=3;i*i<=ar[p-1][q-1].s;i+=2) {
                cnt = 0;
                while (ar[p-1][q-1].s%i==0) {
                    cnt++;
                    ar[p-1][q-1].s/=i;
                }
                if (cnt) m[(int)i] = -cnt;
            }
            if (ar[p-1][q-1].s!=1) m[(int)ar[p-1][q-1].s] = -1;
        }
        
        for (const auto& [k, v] : m) cout<<k<<' '<<v<<'\n';
    }
}
