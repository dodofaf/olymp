#include <bits/stdc++.h>
using namespace std;

struct Color
{
    int color;
    int count;
};

auto cmp = [](const Color &a, const Color &b) 
{
    return a.count > b.count || (a.count == b.count && a.color < b.color);
};

int main() 
{
    int n, k, g;
    cin>>n>>k>>g;;

    vector<int> col(n);
    vector<Color> cols(k);
    set<Color, decltype(cmp)> colors(cmp);

    for (int i=0;i<k;i++) {
        cols[i] = {i, 0};
    }
    for (int i=0;i<n;i++) {
        cin>>col[i];
        col[i]--;
    //        cout<<col[i]<<' ';
        cols[col[i]].count++;
    }
    for (int i=0;i<k;i++) {
        colors.insert(cols[i]);
    }
    vector<int> road(n, -1);
    if (colors.begin()->count > n-colors.begin()->count+1 || (k == 2 && (colors.begin()->count == colors.rbegin()->count || n==5))) {
        cout<<-1<<endl;
    } else {
        int d = 2;
        if (colors.begin()->count == n-colors.begin()->count+1) {d++;}
        auto itr = colors.end();
        itr--;
        road[0] = itr->color+1;
        Color tmp = *itr;
        tmp.count--;
        colors.erase(itr);
        if (tmp.count != 0){
            colors.insert(tmp);
        }
        for (int i=1;i<n;i++) {
            if (i%2 == 0 && i != n-d) {
                auto iter = colors.end();
                iter--;
                if (iter->color+1 == road[i-1]) {
                    if (iter != colors.begin()) {
                        iter--;
                    }
                }
                road[i] = iter->color+1;
                Color tmp = *iter;
                tmp.count--;
                colors.erase(iter);
                if (tmp.count != 0){
                    colors.insert(tmp);
                }
            } else {
                auto iter = colors.begin();
                if (i != n-d && iter->color+1 == road[i-1]) {
                    iter++;
                }
                road[i] = iter->color+1;
                Color tmp = *iter;
                tmp.count--;
                colors.erase(iter);
                if (tmp.count != 0){
                    colors.insert(tmp);
                }
            }
        }
        if (d == 2) {
            cout<<n-3<<' '<<2<<endl;
            for (int i=1;i<n-2;i++) {
                cout<<road[i]<<' ';
            }
            cout<<endl<<road[0]<<endl;
            cout<<road[n-2]<<' '<<road[n-1]<<endl;
        } else {
            cout<<n-4<<' '<<3<<endl;
            for (int i=1;i<n-3;i++) {
                cout<<road[i]<<' ';
            }
            cout<<endl<<road[0]<<endl;
            cout<<road[n-3]<<' '<<road[n-2]<<' '<<road[n-1]<<endl;

        }
    }
}
