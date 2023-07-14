#include <iostream>

using namespace std;

int res[5] = {100000, 100000, 100000, 100000, 100000};
int ar[5][10001] = {0};
int l[5] = {0};
int a[10001] = {0};

bool bf(int n, int k, int x)
{
    int start = 0;
    for (int i=0;a[i] != 0;++i, ++start);
    
    for (int i=0;i<k;++i) {
        if (res[i]!=100000) continue;
        a[start] = 1;
        bool flag = true, check = false;
        for (int j=1;j<l[i] && flag;++j) {
            if (start+ar[i][j]>=n) {
                flag = false;
            } else {
                if (a[start+ar[i][j]]) flag = false;
                else a[start+ar[i][j]] = i+1;
            }
        }
        if (flag) {
            res[i] = start-ar[i][0]+1;
            if (x == k) check = true;
            else check = bf(n, k, x+1);
        }
        for (int j=1;j<l[i] && flag;++j) {
            if (start+ar[i][j]>=n) {
                flag = false;
            } else {
                if (a[start+ar[i][j]] != i+1) flag = false;
                else a[start+ar[i][j]] = 0;
            }
        }
        a[start] = 0;
        if (check) return true;
        res[i] = 100000;
    }
    return false;
}


int main()
{
    int n, k;
    cin>>n>>k;
    
    for (int i=0;i<k;++i) {
        cin>>l[i];
        for (int j=0; j<l[i]; ++j) {
            cin>>ar[i][j];
        }
        sort(ar[i], ar[i]+l[i]);
        for (int j=1; j<l[i]; ++j) {
            ar[i][j]-=ar[i][0];
        }
    }
    if (bf(n, k, 1)) {
        cout<<"Yes\n";
        for (int i=0;i<k;++i) cout<<res[i]<<' ';
        cout<<'\n';
    } else cout<<"No\n";
}
