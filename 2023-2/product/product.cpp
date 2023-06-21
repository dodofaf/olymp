#include <iostream>
#include <algorithm>
#include <stack>

using namespace std;


struct Segment
{
    int l;
    int r;
    int mn;
    int mn1;
    int mn2;
};

Segment st[2000001] = {0};

void building_seg_tree(int ar[], int n)
{
    st[1].l = 0;
    st[1].r = n-1;
    
    for (int i=1;i<n;++i) {
        st[i<<1].l = st[i].l;
        st[i<<1].r =((st[i].l + st[i].r)>>1);
        
        st[(i<<1)|1].l = st[i<<1].r+1;
        st[(i<<1)|1].r = st[i].r;
    }
    
    for (int i=n;i<2*n;++i) {
        st[i].mn1 = ar[st[i].l];
        st[i].mn2 = 2e9;
    }
    
    for (int i=n-1;i>-1;--i) {
        st[i].mn1 = min(st[i<<1].mn1, st[(i<<1)|1].mn1);
        st[i].mn2 = min(max(st[i<<1].mn1, st[(i<<1)|1].mn1), min(st[i<<1].mn2, st[(i<<1)|1].mn2));
    }
}

int lm[1000005] = {0};

void finding_ind_left_min_for_each_el(int ar[], int n)
{
    stack<int> s;
    s.push(n-1);
    for (int i=n-2;i>-1;--i) {
        while (!s.empty() && ar[i]<ar[s.top()]) {
            lm[s.top()] = i;
            s.pop();
        }
        s.push(i);
    }
    while (!s.empty()) {
        lm[s.top()] = -1;
        s.pop();
    }
}

int rm[1000005] = {0};

void finding_ind_right_min_for_each_el(int ar[], int n)
{
    stack<int> s;
    s.push(0);
    for (int i=1;i<n;++i) {
        while (!s.empty() && ar[i]<ar[s.top()]) {
            rm[s.top()] = i;
            s.pop();
        }
        s.push(i);
    }
    while (!s.empty()) {
        rm[s.top()] = n;
        s.pop();
    }
}

bool check(int x, int i) // check if st[i] include x
{
    return (st[i].l <= x && st[i].r >= x);
}

int ar[1000005] = {0};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    
    int n;
    cin>>n;
    for (int i=0;i<n;++i) cin>>ar[i];
    
    building_seg_tree(ar, n);
    
    finding_ind_left_min_for_each_el(ar, n);
    finding_ind_right_min_for_each_el(ar, n);
    
    int mn1 = min(ar[0], ar[1]), mn2 = max(ar[0], ar[1]);
    for (int i=2;i<n;++i) {
        if (ar[i]<mn1) {
            mn2 = mn1;
            mn1 = ar[i];
        } else if (ar[i]<mn2) mn2 = ar[i];
    }
    
    int res = 0;
    
    for (int i=1;i<n;++i) {
        if (ar[i] == mn1) res = max(res, (mn1+mn2)*n);
        if (lm[i] == -1) continue;
        int l = lm[i], r = max(rm[i]-1, i);
        if (l != 0) {
            for (int j=1;;) {
                if (st[(j<<1)|1].l==st[(j<<1)|1].r && st[(j<<1)|1].mn<ar[i]) {
                    l = min(l, min(st[(j<<1)|1].l+1, i));
                    break;
                }
                if (st[j<<1].l==st[j<<1].r && st[j<<1].mn<ar[i]) {
                    l = min(l, min(st[j<<1].l+1, i));
                    break;
                }
                if (st[j<<1].l==st[j<<1].r && st[j<<1].l==0) {
                    l = 0;
                    break;
                }
                
                if (st[(j<<1)|1].l<l && ((check(l, (j<<1)|1) && st[(j<<1)|1].mn2<ar[i]) || (!check(l, (j<<1)|1) && st[(j<<1)|1].mn1<ar[i]))) {
                    j<<=1;
                    ++j;
                } else {
                    j<<=1;
                }
            }
        }
        res = max(res, (ar[lm[i]]+ar[i])*(r-l+1));
    }
    cout<<res<<'\n';
}

