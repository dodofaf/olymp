#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int query(int l1, int l2, int a1[], int a2[])
{
    cout<<"? "<<l1<<' '<<l2;
    for (int i=0;i<l1;++i) cout<<' '<<a1[i];
    for (int i=0;i<l2;++i) cout<<' '<<a2[i];
    cout<<'\n';
    cout.flush();
    int res;
    cin>>res;
    return res;
}

int query2(int l1, int l2, int s1, int s2)
{
    cout<<"? "<<l1<<' '<<l2;
    for (int i=0;i<l1;++i) cout<<' '<<s1+i;
    for (int i=0;i<l2;++i) cout<<' '<<s2+i;
    cout<<'\n';
    cout.flush();
    int res;
    cin>>res;
    return res;
}

int query3(int l1, int l2, int s1, int s2, int d1, int d2)
{
    cout<<"? "<<l1<<' '<<l2;
    for (int i=0;i<l1;++i) cout<<' '<<s1+i*d1;
    for (int i=0;i<l2;++i) cout<<' '<<s2+i*d2;
    cout<<'\n';
    cout.flush();
    int res;
    cin>>res;
    return res;
}

int query4(int s1, int f1, int s2, int f2)
{
    cout<<"? "<<f1-s1+1<<' '<<f1-s1+1;
    for (int i=s1;i<=f1;++i) cout<<' '<<i;
    for (int i=s2;i<=f2;++i) cout<<' '<<i;
    cout<<'\n';
    cout.flush();
    int res;
    cin>>res;
    return res;
}


void answer(int ans)
{
    cout<<"! "<<ans<<'\n';
    cout.flush();
}

int a1[10000] = {0};
int a2[10000] = {0};

void g1(int n, int k)
{
    a1[0] = 1;
    a2[0] = n;
    if (query(1, 1, a1, a2) == 2) return answer(1);
    for (int i=2;i<n;++i) {
        a2[0] = i;
        if (query(1, 1, a1, a2) == 1) return answer(i);
    }
    answer(n);
}

void g2(int n, int k)
{
    int l = 1, r = n, m, q;
    while (r>l) {
        m = (r-l+1)/2;
        q = query2(m, m, l, r-m+1);
        if (q == 1) l = r-m+1;
        else if (q == 2) r = l+m-1;
        else {
            l = l+m;
            r = l;
        }
    }
    answer(l);
}

void g3(int n, int k)
{
    int l = 1, r = n, m, q;
    while (r>l) {
        m = (r-l+2)/3;
        q = query2(m, m, l, r-m+1);
        if (q == 1) l = r-m+1;
        else if (q == 2) r = l+m-1;
        else {
            l = l+m;
            r = r-m;
        }
    }
    answer(l);
}

void g4(int n, int k)
{
    int d = (n-1)/k;
    int l = 0, r = d, m, q;
    while (r>l) {
        m = (r-l+2)/3;
        q = query3(m, m, l*k+1, (r-m+1)*k+1, k, k);
        if (q == 1) l = r-m+1;
        else if (q == 2) r = l+m-1;
        else {
            l = l+m;
            r = r-m;
        }
    }
    if (r != 0) {
        r = r*k+1;
        l = r-k+1;
        int real = 1;
        while (r>l) {
            m = (r+l)/2;
            q = query2(1, 1, real, m);
            if (q == 1) r = m;
            if (q == 0) l = m+1;
        }
        answer(l);
    } else answer(1);
}

void g5(int n, int k)
{
    int d = (n-1)/k;
    int l = 0, r = d, m, q;
    while (r>l) {
        m = (r-l+2)/3;
        q = query3(m, m, l*k+1, (r-m+1)*k+1, k, k);
        if (q == 1) l = r-m+1;
        else if (q == 2) r = l+m-1;
        else {
            l = l+m;
            r = r-m;
        }
    }
    
    if (r != 0) {
        r = r*k+1;
        l = r-k+1;
        a1[0] = 1;
        a1[1] = r;
        while (r>l) {
            m = (r-l+2)/3;
            a2[0] = l+m-1;
            a2[1] = r-m+1;
            if (a2[1] == a1[1]) {
                if (a2[0] == a1[1]-1) {
                    q = query2(1, 1, a1[1]-1, a1[1]+1);
                    if (q == 1) return answer(a1[1]);
                    else return answer(a1[1]-1);
                } else --a2[1];
            }
            
            q = query(2, 2, a1, a2);
            if (q == 0) {
                l = a2[0]+1;
                r = a2[1];
            } else if (q == 1) {
                r = a2[0]-1;
            } else l = a2[1]+1;
        }
        answer(l);
    } else answer(1);
    //c-l=d-c=r-d
    //2c-l+d=2d=r+c
}

void g6(int n, int k)
{
    int l=1, r=n, m, q;
    while (r>l+k) {
        m = ceil((r-k-l+1)/3.0);
        q = query4(l, l+m-1, r-m+1, r);
        if (q == 0) {
            l = l+m;
            r=r-m;
        } else if (q == 1) l = r-m+1-k+1;
        else r = l+m-1+k-1;
    }
    int temp;
    if (l>1) temp = 1;
    else temp = n;
    q = query2(1, 1, temp, l);
    if (q == 1) answer(l);
    else answer(l+1);

}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, k, g;
    cin>>n>>k>>g;
/*
    if (g <= 1) g1(n, k);
    if (g == 2) g2(n, k);
    if (g == 3) g3(n, k);
    if (g == 4) g4(n, k);
    if (g == 5) g6(n, k);
    if (g == 6) g6(n, k);
*/
    g6(n, k);
}
