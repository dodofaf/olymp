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

P ar[5000];
short int cross[5000][5000];
short int cnt[5000] = {0};
short int s[5000];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m, k;
    cin>>n>>m>>k;
    for (short int i=0;i<k;++i) {
        cin>>ar[i].x1>>ar[i].y1>>ar[i].x2>>ar[i].y2;
    }
    for (short int i=0;i<k-1;++i) {
        for (short int j=i+1;j<k;++j) {
            if (check(ar[i], ar[j])) {
                cross[i][cnt[i]] = j;
                cross[j][cnt[j]] = i;
                ++cnt[i];
                ++cnt[j];
            }
        }
        ar[i].x1 = (ar[i].x1==0);
        ar[i].y1 = (ar[i].y1==0);
        ar[i].x2 = (ar[i].x2==n);
        ar[i].y2 = (ar[i].y2==m);
    }
    ar[k-1].x1 = (ar[k-1].x1==0);
    ar[k-1].y1 = (ar[k-1].y1==0);
    ar[k-1].x2 = (ar[k-1].x2==n);
    ar[k-1].y2 = (ar[k-1].y2==m);
    bool flag = true;
    vector<bool> tick(k, true);
    int x=-1, size = 0;
    for (int i=0;i<k && flag;++i) {
        if ((ar[i].x1 && ar[i].x2) || (ar[i].y1 && ar[i].y2)) flag = false;
        else if (tick[i] && (ar[i].x1 || ar[i].y1 || ar[i].x2 || ar[i].y2)) {
            tick[i] = false;
            s[0] = i;
            ++size;
            while (size && flag) {
                --size;
                x=s[size];
                for (int itr=0;itr!=cnt[x] && flag;++itr) {
                    if (tick[cross[x][itr]]) {
                        if (ar[cross[x][itr]].x1) ar[i].x1 = ar[cross[x][itr]].x1;
                        if (ar[cross[x][itr]].y1) ar[i].y1 = ar[cross[x][itr]].y1;
                        if (ar[cross[x][itr]].x2) ar[i].x2 = ar[cross[x][itr]].x2;
                        if (ar[cross[x][itr]].y2) ar[i].y2 = ar[cross[x][itr]].y2;
                        if ((ar[i].x1 && ar[i].y1) || (ar[i].x1 && ar[i].x2) || (ar[i].y1 && ar[i].y2) || (ar[i].x2 && ar[i].y2)) flag = false;
                        else {
                            s[size++] = cross[x][itr];
                            tick[cross[x][itr]]=false;
                        }
                    }
                }
            }
        }
    }
    if (flag) cout<<"YES\n";
    else cout<<"NO\n";
}
