#include <iostream>
#include <algorithm>

using namespace std;

int ar[200000] = {0};
int sorted[200000] = {0};

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    int n;
    cin>>n;
    for (int i=0;i<n;++i) {
        cin>>ar[i];
        sorted[i] = ar[i];
    }
    sort(sorted, sorted+n);
    int med = sorted[n/2];
    int lower = 0, bigger = 0;
    for (int i=0;i<n;++i) {
        if (ar[i]<med) ++lower;
        else if (ar[i]>med) ++bigger;
    }
    int len = 0, temp_lower = 0, temp_bigger = 0;
    bool flag = false;
    for (int i=0;i<n && !flag;++i) {
        ++len;
        if (ar[i]<med) ++temp_lower;
        else if (ar[i]>med) ++temp_bigger;
        if (len%2==1 && temp_bigger<=(len-1)/2 && temp_lower<=(len-1)/2 && (bigger-temp_bigger)<=(n-i-1)/2 && (lower-temp_lower)<=(n-i-1)/2)
            flag = true;
    }
    if (flag) cout<<"Yes\n";
    else cout<<"No\n";
}
