#include <iostream>
#include <stack>
#include <iterator>
#include <list>
#include <vector>

using namespace std;

struct P
{
    int x1;
    int y1;
    int x2;
    int y2;
};

bool check(P p1, P p2)
{
    return ((((p1.x1<=p2.x2 && p1.x1>=p2.x1) || (p1.x2<=p2.x2 && p1.x2>=p2.x1)) && ((p1.y1<=p2.y2 && p1.y1>=p2.y1) || (p1.y2<=p2.y2 && p1.y2>=p2.y1))) 
    || ((p1.x1<=p2.x2 && p1.x1>=p2.x1) && (p1.x2<=p2.x2 && p1.x2>=p2.x1) && p1.y1<=p2.y1 && p1.y2>=p2.y2) 
    || ((p1.y1<=p2.y2 && p1.y1>=p2.y1) && (p1.y2<=p2.y2 && p1.y2>=p2.y1) && p1.x1<=p2.x1 && p1.x2>=p2.x2));
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m, k;
    cin>>n>>m>>k;
    P ar[5000];
    for (short int i=0;i<k;++i) {
        cin>>ar[i].x1>>ar[i].y1>>ar[i].x2>>ar[i].y2;
//        ar[i].ind = i;
    }
    int cross[5000][5000] = {0};
    int cnt[5000] = {0};
    for (short int i=0;i<k-1;++i) {
        for (short int j=i+1;j<k;++j) {
            if (check(ar[i], ar[j])) {
                cross[i][cnt[i]]=j;
                cross[j][cnt[j]]=i;
                ++cnt[i];
                ++cnt[j];
            }
        }
    }
    bool flag = true;
    vector<bool> tick(k, true);
    short int s[5000];
    int x, size = 0;
    bool f1, f2, f3, f4;
    for (int i=0;i<k && flag;++i) {
        if ((ar[i].x1==0 && ar[i].x2==n) || (ar[i].y1==0 && ar[i].y2==m)) flag = false;
        else if (tick[i] && (ar[i].x1==0 || ar[i].y1==0 || ar[i].x2==n || ar[i].y2==m)) {
            tick[i] = false;
            s[0] = i;
            ++size;
            f1 = (ar[i].x1==0), f2 = (ar[i].y1==0), f3 = (ar[i].x2==n), f4 = (ar[i].y2==m);
            while (size && flag) {
                --size;
                x=s[size];
                for (int itr=0;itr<cnt[x] && flag;++itr) {
                    if (tick[cross[x][itr]]) {
                        f1 = (f1 || (ar[cross[x][itr]].x1==0));
                        f2 = (f2 || (ar[cross[x][itr]].y1==0));
                        f3 = (f3 || (ar[cross[x][itr]].x2==n));
                        f4 = (f4 || (ar[cross[x][itr]].y2==m));
                        if ((f1 && f2) || (f1 && f3) || (f2 && f4) || (f3 && f4)) flag = false;
                        else s[size] = cross[x][itr], ++size, tick[cross[x][itr]]=false;
                    }
                }
            }
        }
    }
    if (flag) cout<<"YES\n";
    else cout<<"NO\n";
}