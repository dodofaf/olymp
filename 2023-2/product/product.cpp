#include <iostream>
#include <algorithm>
#include <stack>
#include <time.h>
#include <random>

using namespace std;

struct Segment
{
    int l;
    int r;
    int mn1;
    int mn2;
};

Segment st[2000001] = {0};

int lm[1000005] = {0};
int lm1[1000005] = {0};
int lm2[1000005] = {0};

void finding_ind_left_min_for_each_el(long long ar[], int n)
{
    stack<int> s1, s2, temp;
    s1.push(n-1);
    for (int i=n-2;i>-1;--i) {
        while (!s2.empty() && ar[i]<ar[s2.top()]) {
            lm2[s2.top()] = i;
            s2.pop();
        }
        while (!s1.empty() && ar[i]<=ar[s1.top()]) {
            lm1[s1.top()] = i;
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
        lm1[s1.top()] = -1;
        lm2[s1.top()] = -1;
        s1.pop();
    }
    while (!s2.empty()) {
        lm2[s2.top()] = -1;
        s2.pop();
    }
    s1.push(n-1);
    for (int i=n-2;i>-1;--i) {
        while (!s1.empty() && ar[i]<ar[s1.top()]) {
            lm[s1.top()] = i;
            s1.pop();
        }
        s1.push(i);
    }
    while (!s1.empty()) {
        lm[s1.top()] = -1;
        s1.pop();
    }
}

int rm[1000005] = {0};
int rm1[1000005] = {0};
int rm2[1000005] = {0};

void finding_ind_right_min_for_each_el(long long ar[], int n)
{
    stack<int> s1, s2, temp;
    s1.push(0);
    for (int i=1;i<n;++i) {
        while (!s2.empty() && ar[i]<ar[s2.top()]) {
            rm2[s2.top()] = i;
            s2.pop();
        }
        while (!s1.empty() && ar[i]<=ar[s1.top()]) {
            rm1[s1.top()] = i;
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
        rm1[s1.top()] = n;
        rm2[s1.top()] = n;
        s1.pop();
    }
    while (!s2.empty()) {
        rm2[s2.top()] = n;
        s2.pop();
    }
    
    s1.push(0);
    for (int i=1;i<n;++i) {
        while (!s1.empty() && ar[i]<ar[s1.top()]) {
            rm[s1.top()] = i;
            s1.pop();
        }
        s1.push(i);
    }
    while (!s1.empty()) {
        rm[s1.top()] = n;
        s1.pop();
    }
}

long long ar[1000005] = {0};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    long long res = 0;
    int n;
    cin>>n;
    for (int i=0;i<n;++i) cin>>ar[i];
    
    finding_ind_left_min_for_each_el(ar, n);
    finding_ind_right_min_for_each_el(ar, n);
    
    res = 0;
    long long mn1 = min(ar[0], ar[1]), mn2 = max(ar[0], ar[1]);
    for (int i=2;i<n;++i) {
        if (ar[i]<mn1) {
            mn2 = mn1;
            mn1 = ar[i];
        } else if (ar[i]<mn2) mn2 = ar[i];
    }
    long long m1 = 0, m2 = 0;
    for (int i=0;i<n;++i) {
        if (lm[i] != -1) {
            long long l = lm2[i], r = max(rm[i]-1, i);
            res = max(res, (r-l)*(ar[lm1[i]]+ar[i]));
        }
        if (rm[i] != n) {
            long long l = min(lm[i]+1, i), r = rm2[i];
            res = max(res, (r-l)*(ar[rm1[i]]+ar[i]));
        }
        if (lm[i] == -1 && rm[i] == n) {
            res = max(res, (mn1+mn2)*n);
        }
    }
    cout<<res<<'\n';
}

