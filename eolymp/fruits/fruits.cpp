#include <bits/stdc++.h>

using namespace std;

int main()
{
    int m, n, a, b, c, x, y, z;
    cin>>m>>n>>a>>b>>c;
    bool flag = true;
    if (n > 2) {
        if (a == c) {
            x = 1;
            if (b == c) {
                y = 1;
                z = n-2;
                if (x*a+y*b+z*c==m) {
                    cout<<x<<' '<<y<<' '<<z<<'\n';
                    flag = false;
                }
            } else {
                y = (m-c*n)/(b-c);
                z = n-x-y;
                if (y>0 && z>0 && x*a+y*b+z*c==m) {
                    cout<<x<<' '<<y<<' '<<z<<'\n';
                    flag = false;
                }
            }
        } else {
            if (b == c) {
                x = (m-c*n)/(a-c);
                if (x>0 && x<n-1) {
                    y = 1;
                    z = n-x-y;
                    if (x*a+y*b+z*c==m) {
                        cout<<x<<' '<<y<<' '<<z<<'\n';
                        flag = false;
                    }
                }
            } else {
                for (x=1;x<n-1 && flag;++x) {
                    y = ((m-c*n)-(a-c)*x)/(b-c);
                    z = n-x-y;
                    if (y>0 && z>0 && x*a+y*b+z*c==m) {
                        cout<<x<<' '<<y<<' '<<z<<'\n';
                        flag = false;
                    }
                }
            }
        }
    }
    if (flag) {
        cout<<"NO SOLUTION\n";
    }
}