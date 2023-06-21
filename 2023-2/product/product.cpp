#include <iostream>
#include <algorithm>
#include <stack>

using namespace std;


struct Segment
{
    int l;
    int r;
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
int lm2[1000005] = {0};

void finding_ind_left_min_for_each_el(int ar[], int n)
{
    stack<int> s1, s2, temp;
    s1.push(n-1);
    for (int i=n-2;i>-1;--i) {
        while (!s2.empty() && (ar[i]<ar[s2.top()] || ar[i]<ar[lm[s2.top()]])) {
            lm2[s2.top()] = i;
            s2.pop();
        }
        while (!s1.empty() && ar[i]<ar[s1.top()]) {
            lm[s1.top()] = i;
            temp.push(s1.top());
            s1.pop();
        }
        while (!temp.empty()) {
            s2.push(temp.top());
            temp.pop();
        }
        s1.push(i);
    }
    while (!s1.empty()) {
        lm[s1.top()] = -1;
        lm2[s1.top()] = -1;
        s1.pop();
    }
    while (!s2.empty()) {
        lm2[s2.top()] = -1;
        s2.pop();
    }
}

int rm[1000005] = {0};
int rm2[1000005] = {0};

void finding_ind_right_min_for_each_el(int ar[], int n)
{
    stack<int> s1, s2, temp;
    s1.push(0);
    for (int i=1;i<n;++i) {
        while (!s2.empty() && (ar[i]<ar[s2.top()] || ar[i]<ar[lm[s2.top()]])) {
            rm2[s2.top()] = i;
            s2.pop();
        }
        while (!s1.empty() && ar[i]<ar[s1.top()]) {
            rm[s1.top()] = i;
            temp.push(s1.top());
            s1.pop();
        }
        while (!temp.empty()) {
            s2.push(temp.top());
            temp.pop();
        }
        s1.push(i);
    }
    while (!s1.empty()) {
        rm[s1.top()] = n;
        rm2[s1.top()] = n;
        s1.pop();
    }
    while (!s2.empty()) {
        rm2[s2.top()] = n;
        s2.pop();
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
    
//    building_seg_tree(ar, n);
    
    finding_ind_left_min_for_each_el(ar, n);
    finding_ind_right_min_for_each_el(ar, n);
    
    int res = 0;
    
    for (int i=0;i<n;++i) {
        if (lm[i] != -1) {
            int l = lm2[i], r = max(rm[i]-1, i);
            res = max(res, (ar[lm[i]]+ar[i])*(r-l));
        }
        if (rm[i] != n) {
            int l = min(lm[i]+1, i), r = rm2[i];
            res = max(res, (ar[rm[i]]+ar[i])*(r-l));
        }
        if (lm[i] == -1 && rm[i] == n) {
            res = max(res, 2*ar[i]*n);
        }
    }
    cout<<res<<'\n';
}

