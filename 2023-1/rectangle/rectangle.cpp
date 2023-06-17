#include <iostream>
#include <iterator>
#include <list>
#include <cstdio>

using namespace std;

bool query(int x, int y) {
    if (x <= 0 || x > 100 || y <= 0 || y > 100)
        return false;
    cout << "? " << x << " " << y << endl;
    cout.flush();
    string ans;
    cin >> ans;
    return (ans[0] == 'i');
}

void answer(bool result) {
    if (result) {
        cout << "! square" << endl;
    } else {
        cout << "! rectangle" << endl;
    }
    cout.flush();
    exit(0);
}

void min_x(int &x, int &y)
{
    int left = max(x-19, 1), right = x, mid;
    while (left!=right) {
        mid = (left+right)/2;
        if (query(mid, y)) right = mid;
        else left = mid+1;
    }
    x = left;
}

void min_y(int &x, int &y)
{
    int left = max(y-19, 1), right = y, mid;
    while (left!=right) {
        mid = (left+right)/2;
        if (query(x, mid)) right = mid;
        else left = mid+1;
    }
    y = left;
}

int find_d(bool s[][6], int x, int y)
{
    int i=0, j=0;
    bool flag = true;
    for (int i1=0;i1<6 && flag;++i1) {
        for (int j1=0;j1<6 && flag;++j1) {
            if (s[i1][j1]) {
                i = i1;
                j = j1;
            }
        }
    }
    int d = min(i*20-x, j*20-y);
    int left = d, right = d+30, mid;
    while (left!=right) {
        mid = (left+right)/2;
        if (!query(x+mid, y+mid)) right = mid;
        else left = mid+1;
    }
    return left;
}

int main()
{
    bool s[6][6] = {0};
    int x=-1, y=-1;
    for (int i=1;i<5;++i) {
        for (int j=1;j<5;++j) s[i][j] = query(i*20, j*20);
    }
    for (int i=1;i<6 && x==-1;++i) {
        for (int j=1;j<6 && x==-1;++j) {
            if (s[i][j]) {
                x = i*20;
                y = j*20;
            }
        }
    }
    if (x == -1) {
        int cnt = 0;
        for (int i=1;i<6;++i) {
            if (query(i*20, 100)) {
                s[i][5] = true;
                ++cnt;
            }
        }
        for (int i=1;i<5;++i) {
            if (query(100, i*20)) {
                s[5][i] = true;
                ++cnt;
            }
        }
        if (cnt == 1) {
            for (int i=1;i<6 && x==-1;++i) {
                for (int j=1;j<6 && x==-1;++j) {
                    if (s[i][j]) {
                        x = i*20;
                        y = j*20;
                    }
                }
            }
            if (x == 100) {
                min_y(x, y);
                if (query(x, y+19) && !query(x, y+20)) answer(true);
                else answer(false);
            } else {
                min_x(x, y);
                if (query(x+19, y) && !query(x+20, y)) answer(true);
                else answer(false);
            }
        } else answer(false);
    } else {
        min_x(x, y);
        min_y(x, y);
        int d = find_d(s, x, y);
        if (!query(x+d, y) && !query(x, y+d)) answer(true);
        else answer(false);
    }
}
