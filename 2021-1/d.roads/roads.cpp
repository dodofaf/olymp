#include <bits/stdc++.h>
using namespace std;

long long mdistx(int n, int x, vector<int> &nroads, vector<vector<vector<int>>> &roads, vector<long long> &tails, vector<int> &cycle)
{
    long long mx = 0, z;
    long long y;
    vector<long long> dist(n, -1);
    dist[x] = 0;
    vector<int> q(n, -1);
    y = 1;
    q[0] = x;
    while (y!=0) {
        z = q[y-1];
        y--;
        for (int i=0; i<nroads[z]; i++) {
            if (((dist[roads[z][i][0]] == -1) || (dist[roads[z][i][0]] > dist[z]+roads[z][i][1])) && cycle[roads[z][i][0]] == 1) {
                q[y] = roads[z][i][0];
                y++;
                dist[roads[z][i][0]] = dist[z]+roads[z][i][1];
            }  
        }
    }
    for (int i=0; i<n; i++) {
//        cout<<dist[i]<<' ';
        if (dist[i] + tails[i] > mx &&  dist[i]> 0) {
            mx = dist[i] + tails[i];
        }
    }
//    cout<<endl;
    return mx+tails[x];
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

    for (int i=0; i<n; i++) {
        if (nroads1[i] == 1) {
            int x = i;
            long long t = 0;
            while (nroads1[x] < 3) {
                cycle[x] = 0;
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


    long long m;
    for (int i=0;i<n;i++) {
        if (cycle[i] == 1){
            m = mdistx(n, i, nroads, roads, tails, cycle);
            if (m>ans) {
                ans = m;
            }
        }
    }
    for (int i=0;i<n;i++) {
    //   cout<<tails[i]<<' ';
    }
//    cout<<endl;

    cout << ans << endl;

}
