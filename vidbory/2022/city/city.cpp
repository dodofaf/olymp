#include <vector>
#include <iostream>
#include <algorithm>
#include <random>

using namespace std;

struct City
{
    vector<int> in;
    vector<int> out;
};

bool check(int n, vector<City> &roads)
{
    vector<int> q(n+2);
    q[0] = 0;
    int x = roads[0].out[0], y = 1;
    q[y] = x;
    y++;
    while (x!=0 && y!=n+2) {
        x = roads[x].out[0];
        q[y] = x;
        y++;
    }
    if (y == n+1) {
        return true;
    } else {
        return false;
    }
}

bool delete_roads(int n, int na, vector<int> &a, vector<int> &nr, vector<int> &nrr, vector<City> &roads)
{
    int x = a[na];
    int ind = -1;
    for (int i=0;i<nr[x];i++) {
        if (nrr[roads[x].out[i]] == 1) {
            if (ind == -1) {
                ind = i;
            } else {
                return false;
            }
        }
    }
    for (int i=0;i<nr[x];i++) {
        if (i != ind) {
            nrr[roads[x].out[i]]--;
        }
    }
    int r = roads[x].out[0];
    if (ind != -1) {
        roads[x].out[0] = roads[x].out[ind];
        if (na>0) {
            if (delete_roads(n, na-1, a, nr, nrr, roads)) {
                return true;
            }
        } else {
            if (check(n, roads)) {
                return true;
            }
        }
    } else {
        for(int i=0;i<nr[x];++i) {
            roads[x].out[0] = roads[x].out[i];
            nrr[roads[x].out[0]]++;
            
            if (na>0) {
                if (delete_roads(n, na-1, a, nr, nrr, roads)) {
                    return true;
                }
            } else {
                if (check(n, roads)) {
                    return true;
                }
            }
            nrr[roads[x].out[0]]--;
        }
    }
    roads[x].out[0] = r;
    for (int i=0;i<nr[x];i++) {
        if (i != ind) {
            nrr[roads[x].out[i]]++;
        }
    }
    return false;
}

int main()
{
    int n, m;
    cin>>n>>m;
    vector<City> roads(n);
    vector<int> nr(n), nrr(n);
    for(int i=0;i<m;i++){
        int a,b;
        cin>>a>>b;
        a--;
        b--;
        if (a != b && find(roads[a].out.begin(), roads[a].out.end(), b) == roads[a].out.end()) {
            roads[a].out.push_back(b);
            roads[b].in.push_back(a);
            nr[a]++;
            nrr[b]++;
        }
    }
    bool flag = true;
    vector<int> a(n), a1;
    for(int i=0;i<n;i++) {a[i] = i;}
    a1.reserve(11);
    int pna = -1, na = n;
    while (!a.empty()) {
        a1.clear();
        if (na == pna) {
            
            flag = delete_roads(n, na-1, a, nr, nrr, roads);
            break;
        }
        for (auto it=a.begin();it!=a.end();it++) {
            int i = (*it);
            if (nr[i] == 0 || nrr[i] == 0) {
                flag = false;
                break;
            }
            bool flag1 = false, f = true;
            if (nr[i]>1) {
                int ind = -1;
                for (int j=0;j<nr[i];j++) {
                    if (nrr[roads[i].out[j]] == 1) {
                        if (!flag1) {
                            flag1 = true;
                            ind = j;
                        } else {
                            flag = false;
                            break;
                        }
                    }
                }
                if (!flag) {break;}
                if (ind == -1) {
                    a1.push_back(i);
                    f = false;
                } else {
                    ind = roads[i].out[ind];
                    for (int j=0;j<nr[i];j++) {
                        if (roads[i].out[j] != ind) {
                            nrr[roads[i].out[j]]--;
                            roads[roads[i].out[j]].in.erase(find(roads[roads[i].out[j]].in.begin(), roads[roads[i].out[j]].in.end(), i));
                        }
                    }
                    nr[i] = 1;
                    roads[i].out.resize(1);
                    roads[i].out[0] = ind;
                }
            }
            flag1 = false;
            if (!flag) {break;}
            if (nrr[i]>1) {
                int ind = -1;
                for (int j=0;j<nrr[i];j++) {
                    if (nr[roads[i].in[j]] == 1) {
                        if (!flag1) {
                            flag1 = true;
                            ind = j;
                        } else {
                            flag = false;
                            break;
                        }
                    }
                }
                if (!flag) {break;}
                if (ind == -1) {
                    if (f){
                        a1.push_back(i);
                    }
                } else {
                    ind = roads[i].in[ind];
                    for (int j=0;j<nrr[i];j++) {
                        if (roads[i].in[j] != ind) {
                            nr[roads[i].in[j]]--;
                            roads[roads[i].in[j]].out.erase(find(roads[roads[i].in[j]].out.begin(), roads[roads[i].in[j]].out.end(), i));
                        }
                    }
                    nrr[i] = 1;
                    roads[i].in.resize(1);
                    roads[i].in[0] = ind;
                }
            }
            if (!flag) {break;}
        }
        if (!flag) {break;}
        a.clear();
        a = a1;
        pna = na;
        na = a.size();
        a1.clear();
    }
    
    if (flag) {
        vector<int> q(n+2);
        q[0] = 0;
        int x = roads[0].out[0], y = 1;
        q[y] = x;
        y++;
        while (x!=0) {
            x = roads[x].out[0];
            q[y] = x;
            y++;
        }
        if (y == n+1) {
            cout<<"YES\n";
            for (int i=0;i<=n;i++) {
                cout<<q[i]+1<<' ';
            }
            cout<<"\n";

        } else {
            cout<<"NO\n";
        }
    } else {
        cout<<"NO\n";
    }
}
