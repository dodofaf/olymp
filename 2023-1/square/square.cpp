#include <iostream>
#include <iterator>
#include <list>
#include <cstdio>

#define f first
#define s second

using namespace std;

void mer(list<pair<int, int>> &l1, list<pair<int, int>> &l2, bool d)
{
    auto itr1 = l1.begin(), itr2 = l2.begin();
    for (;itr1!=l1.end() && itr2!=l2.end();) {
        if (itr1->f==itr2->f) {
            if (d) itr1->s += itr2->s;
            else itr1->s -= itr2->s;
            
            if (!itr1->s) {
                auto itr = itr1;
                ++itr1;
                l1.erase(itr);
            } else  ++itr1;
            ++itr2;
        } else if (itr1->f<itr2->f) ++itr1;
        else {
            if (d) l1.insert(itr1, {itr2->f, itr2->s});
            else l1.insert(itr1, {itr2->f, -(itr2->s)});
            ++itr2;
        }
    }
    for (;itr2!=l2.end();++itr2) {
        if (d) l1.insert(itr1, {itr2->f, itr2->s});
        else l1.insert(itr1, {itr2->f, -(itr2->s)});
    }
}

list<pair<int, int>> ar[1500][1500];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    int n;
    cin>>n;
    
    for (int i=0;i<n;++i) {
        int a;
        cin>>a;
        if (a!=1) {
            int cnt = 0;
            while (!(a&1)) {
                cnt++;
                a>>=1;
            }
            if (cnt) ar[i][i].push_back({2, cnt});
            for (int j=3;j*j<=a;j+=2) {
                cnt = 0;
                while (a%j==0) {
                    cnt++;
                    a/=j;
                }
                if (cnt) ar[i][i].push_back({j, cnt});
            }
            if (a!=1) ar[i][i].push_back({a, 1});
        }
    }
    for (int i=0;i<n-1;++i) {
        int a;
        cin>>a;
        if (a!=1) {
            int cnt = 0;
            while (!(a&1)) {
                cnt++;
                a>>=1;
            }
            if (cnt) ar[i+1][i].push_back({2, cnt});
            for (int j=3;j*j<=a;j+=2) {
                cnt = 0;
                while (a%j==0) {
                    cnt++;
                    a/=j;
                }
                if (cnt) ar[i+1][i].push_back({j, cnt});
            }
            if (a!=1) ar[i+1][i].push_back({a, 1});
        }
    }
    
    int p, q;
    cin>>p>>q;
    if (p<q) {
        for (int i=0;i<q-p;++i){
            for (int x=p-1, y=p+i;x<q;++y, ++x) {
                ar[x][y] = ar[x][y-1];
                mer(ar[x][y], ar[x+1][y], true);
                mer(ar[x][y], ar[x+1][y-1], false);
                ar[x+1][y-1].clear();
            }
        }
    }
    else if (p>q+1) {
        for (int i=1;i<p-q;++i){
            for (int x=q+i, y=q-1;x<p;++y, ++x) {
                ar[x][y] = ar[x][y+1];
                mer(ar[x][y], ar[x-1][y], true);
                mer(ar[x][y], ar[x-1][y+1], false);
                ar[x-1][y+1].clear();
            }
        }
    }
    if (ar[p-1][q-1].empty()) cout<<"1 1\n";
    else for (auto itr=ar[p-1][q-1].begin();itr!=ar[p-1][q-1].end();++itr) cout<<itr->f<<' '<<itr->s<<'\n';
}
