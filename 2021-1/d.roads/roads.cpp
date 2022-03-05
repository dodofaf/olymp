#include <bits/stdc++.h>
using namespace std;

long long mdistx(int n, int x, vector<long long> &tails, vector<int> &cycl, int ncy, vector<int> &croads)
{
//    int y;
    vector<long long> dist(n, -1);
    dist[cycl[x]] = 0;
    int z = 1;
    while (dist[cycl[(x+z)%ncy]] == -1 || dist[cycl[(x+z)%ncy]] > dist[cycl[(x+z-1+ncy)%ncy]] + croads[(x+z)%ncy]) {
        dist[cycl[(x+z)%ncy]] = dist[cycl[(x+z-1+ncy)%ncy]] + croads[(x+z-1)%ncy];
        z++;
//        cout<<x<<" 1:";
//        for (int i=0;i<ncy;i++) {
//            cout<<dist[cycl[i]]<<' ';
//        }
//        cout<<endl;
    } 
    z = 1;
    while (dist[cycl[(x-z+ncy)%ncy]] == -1 || dist[cycl[(x-z+ncy)%ncy]] > dist[cycl[(x-z+1+ncy)%ncy]] + croads[(x-z+ncy)%ncy]) {
        dist[cycl[(x-z+ncy)%ncy]] = dist[cycl[(x-z+1+ncy)%ncy]] + croads[(x-z+ncy)%ncy];
        z++;
//        cout<<x<<" 2:";
//        for (int i=0;i<ncy;i++) {
//            cout<<dist[cycl[i]]<<' ';
//        }
//        cout<<endl;
    } 
    long long mx = 0;
    for (int i=0; i<ncy; i++) {
//        cout<<dist[i]<<' ';
        if (i != x && dist[cycl[i]] + tails[cycl[i]] > mx) {
            mx = dist[cycl[i]] + tails[cycl[i]];
        }
    }
//    cout<<endl;
    return mx+tails[cycl[x]];
}



int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

	int n, g;
    cin >> n >> g;

    vector<int> nroads(n, 0);
    vector<vector<vector<int>>> roads(n);
    for (int i=0;i<n;i++) {
        int a, b, c;
        cin>>a>>b>>c;
        roads[a-1].push_back({b-1, c});
        roads[b-1].push_back({a-1, c});
        nroads[a-1]++;
        nroads[b-1]++;
    }

    vector<long long> tails(n, 0);
    vector<int> cycle(n, 1);
    vector<int> nroads1(nroads);

    long long ans = 0;
    int ncy = n;

    for (int i=0; i<n; i++) {
        if (nroads1[i] == 1) {
            int x = i;
            long long t = 0;
            while (nroads1[x] < 3) {
                cycle[x] = 0;
                ncy--;
//                cout<<'x'<<x<<endl;
                for (int j=0; j<nroads[x]; j++) {
//                    cout<<'r'<<roads[x][j][0]<<endl;
                    if (cycle[roads[x][j][0]] == 1) {
//                        cout<<'j'<<j<<endl;
                        t += roads[x][j][1];
                        x = roads[x][j][0];
                        if (t+tails[x] > ans) {
                            ans = t+tails[x];
                        }
                        if (t<tails[x]) {
                            t = tails[x];
                        }
                        tails[x] = 0;
                        break;
                    }
                }
  //              cout<<t<<endl;
            }
//            cout<<x<<endl;
            nroads1[x]--;
            tails[x] = t;
        }
    }


    vector<int> cycl(ncy), croads(ncy);
    for (int i=0;i<n;i++) {
        if (cycle[i] == 1) {
            cycl[0] = i;
            bool b = true;
            for (int j=0;j<nroads[i];j++) {
                if (cycle[roads[i][j][0]] == 1) {
                    if (b) {
                        cycl[1] = roads[i][j][0];
                        croads[0] = roads[i][j][1];
                        b = false;
                    } else {
                        croads[ncy-1] = roads[i][j][1];
                    }
                }
            }
            break;
        }
    }
//    cout<<ncy<<endl;
    int y = 2, x;
    while (y != ncy) {
        x = cycl[y-1];
        for (int i=0;i<nroads[x];i++) {
            if (cycle[roads[x][i][0]] == 1 && roads[x][i][0] != cycl[y-2]) {
                cycl[y] = roads[x][i][0];
                croads[y-1] = roads[x][i][1];
                y++;
//                cout<<y<<endl;
                break;
            }
        }
    }
    long long m;
    for (int i=0;i<ncy;i++) {
        m = mdistx(n, i, tails, cycl, ncy, croads);
        if (m>ans) {
            ans = m;
        }
    }
    for (int i=0;i<n;i++) {
    //   cout<<tails[i]<<' ';
    }
//    cout<<endl;

    cout << ans << endl;

}