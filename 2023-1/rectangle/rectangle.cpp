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
    return (ans == "inside");
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



int main()
{
    int x=-1, y;
    for (int i=1;i<5 && x==-1;++i) {
        for (int j=1;j<5 && x==-1;++j) if (query(i*20, j*20)) x = i*20, y = j*20;
    }
    if (x == -1) {
        for (int j=1;j<=5 && x==-1;++j) if (query(100, j*20)) x = 100, y = j*20;
        if (x == -1) {
            for (int i=1;i<5 && x==-1;++i) if (query(i*20, 100)) x = i*20, y = 100;
        }
        if (x == -1) answer(false);
        else {
            int left = max(y-20, 0), right = y, mid;
            while (left!=right) {
                mid = (left+right)/2;
                if (!query(x, mid)) left = mid+1;
                else right = mid;
            }
            if (query(x, left+19) && !query(x, left+20)) answer(true);
            else answer(false);
        }
        
    }
    else {
        int left = max(y-20, 0), right = y, mid;
        while (left!=right) {
            mid = (left+right)/2;
            if (!query(x, mid)) left = mid+1;
            else right = mid;
        }
        y = left;

        left = max(x-20, 0);
        right = x;
        while (left!=right) {
            mid = (left+right)/2;
            if (!query(mid, y)) left = mid+1;
            else right = mid;
        }
        x = left;

//        printf("%d %d\n", x, y);

        left = 0;
        right = min(100-x, 100-y);
        while (left!=right) {
            mid = (left+right)/2;
            if (query(x+mid, y+mid)) left = mid+1;
            else right = mid;
        }
//        printf("%d\n", left);
        
        if (!query(x+left, y+left-1) && !query(x+left-1, y+left)) answer(true);
        else answer(false);
    }
}
