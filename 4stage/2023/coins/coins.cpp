#include <iostream>
#include <vector>

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

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, k, g;
    cin>>n>>k>>g;
    if (g <= 1) g1(n, k);
    if (g == 2) g2(n, k);
    if (g == 3) g3(n, k);
    if (g>3) answer(1);
}
