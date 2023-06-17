#include <iostream>
#include <algorithm>

using namespace std;

int ar[1000005] = {0};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    
    int n;
    cin>>n;
    for (int i=0;i<n;++i) cin>>ar[i];
    
    int mx = 0;
    for (int i=0;i<n-1;++i) {
        if (ar[i]>mx) mx = ar[i];
        int mn1 = ar[i], mn2 = 2e9;
        for (int j=i+1;j<n;++j) {
            if (ar[j]<mn1) {
                mn2 = mn1;
                mn1 = ar[j];
            } else if (ar[j]<mn2) mn2 = ar[j];
            mx = max(mx, (mn1+mn2)*(j-i+1));
        }
    }
    cout<<mx<<'\n';
}
