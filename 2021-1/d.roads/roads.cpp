#include <bits/stdc++.h>
using namespace std;

struct St
{
    int ind;
    long long sum;
    long long riz;
};

auto cmp1 = [](const St &a, const St &b)
{
    return a.sum > b.sum || (a.sum == b.sum && a.ind > b.ind);
};

auto cmp2 = [](const St &a, const St &b)
{
    return a.riz > b.riz || (a.riz == b.riz && a.ind > b.ind);
};

int random(int m)
{
    return rand()%m;
}

long long max_dist(int ncy, long long s, vector<long long> &p, vector<St> &ar, vector<long long> &h)
{
    int k = 0;
    set<St, decltype(cmp1)> set_1_1(cmp1), set_2_2(cmp1);
    set<St, decltype(cmp2)> set_2_1(cmp2), set_1_2(cmp2);
    St a;
    a.ind = -1;
    a.sum = -2e18;
    a.riz = -2e18;
    set_1_1.insert(a);
    set_2_1.insert(a);
    set_1_2.insert(a);
    set_2_2.insert(a);
    for(int i=1;i<ncy;i++) {
        if (p[i] < s-p[i]) {
            k++;
            set_1_1.insert(ar[i]);
        } else {
            set_2_1.insert(ar[i]);
        }
    }
    long long m1 = max(set_1_1.begin()->sum + ar[0].riz, set_1_2.begin()->sum+s+ar[0].riz);
    long long m2 = max(set_2_2.begin()->riz + ar[0].sum, set_2_1.begin()->riz+s+ar[0].sum);
    long long mx = max(m1, m2);
    bool b = true;
    if (k == 0) {
        k =(k+1)%ncy;
        set_2_1.erase(set_2_1.find(ar[k]));
        set_1_1.insert(ar[k]);
    }
    for (int i=1;i<ncy;i++) {
        auto iter = set_1_1.find(ar[i]);
        assert(iter != set_1_1.end());
        set_1_1.erase(iter);
        set_2_2.insert(ar[i-1]);
        while ((p[(k+1)%ncy] - p[i] + s)%s < (s - p[(k+1)%ncy] + p[i])%s && k != i-1) {
            k = (k+1)%ncy;
            if (k == 0) {
                b = false;
            }
            if (b){
                set_2_1.erase(set_2_1.find(ar[k]));
                set_1_1.insert(ar[k]);
            } else {
                set_2_2.erase(set_2_2.find(ar[k]));
                set_1_2.insert(ar[k]);
            }
        }
        m1 = max(set_1_1.begin()->sum + ar[i].riz, set_1_2.begin()->sum+s+ar[i].riz);
        m2 = max(set_2_2.begin()->riz + ar[i].sum, set_2_1.begin()->riz+s+ar[i].sum);
        long long mxt = max(m1, m2);

        if (mxt>mx) {
            mx = mxt;
        }
        if (k == i) {
            k =(k+1)%ncy;
            if (k == 0) {
                set_2_2.erase(set_2_2.find(ar[k]));
            } else {
                set_2_1.erase(set_2_1.find(ar[k]));
            }
            set_1_1.insert(ar[k]);
        }
    }
    return mx;
}

long long mdistx(int n, int x, vector<long long> &h, vector<int> &cycl, int ncy, vector<int> &croads)
{
    vector<long long> dist(n, -1);
    dist[cycl[x]] = 0;
    int z = 1;
    while (dist[cycl[(x+z)%ncy]] == -1 || dist[cycl[(x+z)%ncy]] > dist[cycl[(x+z-1+ncy)%ncy]] + croads[(x+z)%ncy]) {
        dist[cycl[(x+z)%ncy]] = dist[cycl[(x+z-1+ncy)%ncy]] + croads[(x+z-1)%ncy];
        z++;
    } 
    z = 1;
    while (dist[cycl[(x-z+ncy)%ncy]] == -1 || dist[cycl[(x-z+ncy)%ncy]] > dist[cycl[(x-z+1+ncy)%ncy]] + croads[(x-z+ncy)%ncy]) {
        dist[cycl[(x-z+ncy)%ncy]] = dist[cycl[(x-z+1+ncy)%ncy]] + croads[(x-z+ncy)%ncy];
        z++;
    } 
    long long mx = 0;
    for (int i=0; i<ncy; i++) {
        if (i != x && dist[cycl[i]] + h[cycl[i]] > mx) {
            mx = dist[cycl[i]] + h[cycl[i]];
        }
    }
    return mx+h[cycl[x]];
}



int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
#if 1
	int n, g;
    cin >> n >> g;

    vector<int> nroads(n, 0);
    vector<int> cycle(n, 1);
    vector<vector<vector<int>>> roads(n);
    for (int i=0;i<n;i++) {
        int a, b, c;
        cin>>a>>b>>c;
        roads[a-1].push_back({b-1, c});
        roads[b-1].push_back({a-1, c});
        nroads[a-1]++;
        nroads[b-1]++;
    }

#else
    int t = time(NULL);
//    t = 1646680805;
    srand(t);
    cout<<t<<endl;
    int n = 10;
//    cout<<"n="<<n<<endl;
    vector<int> nroads(n, 0);
    vector<int> cycle(n, 1);
    vector<vector<vector<int>>> roads(n);
    for (int i=n/2;i<n;i++) {
        nroads[i]++;
        nroads[(i+1)%(n/2)+n/2]++;
        int c = 1;
//        cout<<i<<' '<<c<<endl;
        roads[i].push_back({(i+1)%(n/2)+n/2, c});
        roads[(i+1)%(n/2)+n/2].push_back({i, c});
//        int r = random(2);
//        cout<<r<<endl;
//        if (r == 1) {
//        cycle[i-n/2] = 0;
        nroads[i]++;
        nroads[i-n/2]++;
        c = 1;
//            cout<<i<<' '<<c<<endl;
        roads[i].push_back({i-n/2, c});
        roads[i-n/2].push_back({i, c});
//        }
    }

#endif

    vector<long long> h(n, 0);
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
                for (int j=0; j<nroads[x]; j++) {
                    if (cycle[roads[x][j][0]] == 1) {
                        t += roads[x][j][1];
                        x = roads[x][j][0];
                        if (t+h[x] > ans) {
                            ans = t+h[x];
                        }
                        if (t<h[x]) {
                            t = h[x];
                        }
                        h[x] = 0;
                        break;
                    }
                }
            }
            nroads1[x]--;
            h[x] = t;
        }
    }

    long long s = 0;

    vector<int> cycl(ncy), croads(ncy);
    vector<long long> p(ncy+1);
    p[0] = 0;
    for (int i=0;i<n;i++) {
        if (cycle[i] == 1) {
            cycl[0] = i;
            bool b = true;
            for (int j=0;j<nroads[i];j++) {
                if (cycle[roads[i][j][0]] == 1) {
                    if (b) {
                        cycl[1] = roads[i][j][0];
                        croads[0] = roads[i][j][1];
                        s+=croads[0];
                        p[1] = s;
                        b = false;
                    } else {
                        croads[ncy-1] = roads[i][j][1];
                        s+=croads[ncy-1];
                    }
                }
            }
            break;
        }
    }
    int y = 2, x;
    while (y != ncy) {
        x = cycl[y-1];
        for (int i=0;i<nroads[x];i++) {
            if (cycle[roads[x][i][0]] == 1 && roads[x][i][0] != cycl[y-2]) {
                cycl[y] = roads[x][i][0];
                croads[y-1] = roads[x][i][1];
                s+=croads[y-1];
                p[y] = p[y-1]+croads[y-1];
                y++;
                break;
            }
        }
    }
    long long ans1 = ans;
    long long m;
    vector<St> ar(ncy);
    for (int i=0;i<ncy;i++) {
        ar[i].ind = i;
        ar[i].sum = p[i] + h[cycl[i]];
        ar[i].riz = h[cycl[i]]-p[i];
    }
    m = max_dist(ncy, s, p, ar, h);
    if (ans<m) {
        ans = m;
    }
    cout << ans << endl;

#if 0
    for (int i=0;i<ncy;i++) {
        m = mdistx(n, i, h, cycl, ncy, croads);
        if (m>ans1) {
            ans1 = m;
        }
    }
    cout<<ans1<<endl;
#endif
}