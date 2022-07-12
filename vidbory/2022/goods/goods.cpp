#include <iostream>
#include <vector>
#include <set>

using namespace std;

int find_type_in_group(int gr, int type, int m, vector<int> &g) {
    for(int i=0;i<m;i++){
        if (g[i] == type){
            g[i] = -1;
            return gr*m+i;
        }
    }
    return -1;
}

int main()
{
    int n, m;
    cin>>n>>m;
    vector<vector<set<int>>> st(n, vector<set<int>>(m));
    vector<vector<int>> g(n, vector<int>(m)), tick(n, vector<int>(m));
    vector<set<int>> extra(n), ins(n), extra_gr(m);
    for (int i=0;i<n;++i) {
        for (int j=0;j<m;++j) {
            cin>>g[i][j];
            g[i][j]--;
            tick[i][g[i][j]]++;
            st[i][g[i][j]].insert(i*m+j);
            if (tick[i][g[i][j]] == 2) {
                extra[i].insert(g[i][j]);
                extra_gr[g[i][j]].insert(i);
            }
        }
    }
    for (int i=0;i<n;i++) {
        for (int j=0;j<m;j++) {
            if (tick[i][j] == 0) {
                ins[i].insert(j);
            }
        }
    }
    int cnt = 0, min_cnt=2e9;
    vector<vector<int>> moves(n*m+2, vector<int>(3, -1)), min_moves;
    int indf = n*m, q = -1;
    while(cnt>0 || min_cnt==2e9) {
        if (cnt == min_cnt) {
            moves[cnt][0] = -1;
            moves[cnt][1] = -1;
            moves[cnt][2] = -1;
            cnt--;
            continue;
        }
        auto itr_e = extra[0].begin();
        auto itr_i = ins[0].begin();
        auto itr_e_gr = extra_gr[0].begin();
        if (moves[cnt][0] != -1) {
            int x = moves[cnt][0];
            int y = moves[cnt][1];
            int type = moves[cnt][2];
            if (x!=n*m) {
                if (y!=n*m) {
                    tick[y][type]--;
                    itr_i = ins[y].insert(type).first;
                } else {
                    q = -1;
                }
                tick[x][type]++;
                itr_e = extra[x].insert(type).first;
                itr_e_gr = extra_gr[type].insert(x).first;
            } else {
                tick[y][type]--;
                itr_i = ins[y].insert(type).first;
                q = type;
            }
            indf = y;
        }
        if (q==-1) {
            int l = -1;
            int t = -1;
            if (moves[cnt][0] == -1){
                for (int i=0;i<n;i++){
                    itr_e = extra[i].begin();
                    if (itr_e != extra[i].end()){
                        l = i;
                        t = (*itr_e);
                        break;
                    }
                }
            } else {
                itr_e++;
                if (itr_e == extra[moves[cnt][0]].end()) {
                    for (int i=moves[cnt][0]+1;i<n;i++){
                        itr_e = extra[i].begin();
                        if (itr_e != extra[i].end()){
                            l = i;
                            t = (*itr_e);
                            break;
                        }
                    }
                } else {
                    l = moves[cnt][0];
                    t = (*itr_e);
                }
            }
            
            if (l == -1) {
                if (moves[cnt][0] == -1 && cnt<min_cnt) {
                    min_cnt = cnt;
                    min_moves = moves;
                }
                moves[cnt][0] = -1;
                moves[cnt][1] = -1;
                moves[cnt][2] = -1;
                cnt--;
            } else {
                moves[cnt][0] = l;
                moves[cnt][1] = indf;
                moves[cnt][2] = t;
                tick[l][t]--;
                if (tick[l][t] == 1) {
                    extra[l].erase(itr_e);
                    extra_gr[t].erase(l);
                }
                q = t;
                indf = l;
                cnt++;
            }
        } else {
            int t = moves[cnt][2];
            int l = -1;
            if (moves[cnt][0] != -1 && moves[cnt][0] != n*m) {
                itr_e_gr++;
                if (itr_e_gr != extra_gr[t].end()) {
                    l=(*itr_e_gr);
                }
            }
            if (l == -1) {
                if (moves[cnt][0] != -1){
                    itr_i++;
                } else {
                    itr_i = ins[indf].begin();
                }
                if (itr_i == ins[indf].end()) {
                    moves[cnt][0] = -1;
                    moves[cnt][1] = -1;
                    moves[cnt][2] = -1;
                    cnt--;
                    continue;
                } else {
                    t = (*itr_i);
                }
                itr_e_gr = extra_gr[t].begin();
                if (itr_e_gr != extra_gr[t].end()) {
                    l=(*itr_e_gr);
                }
            }
            if (l == -1) {
                tick[indf][t]++;
                ins[indf].erase(itr_i);
                q = -1;
                moves[cnt][0] = n*m;
                moves[cnt][1] = indf;
                moves[cnt][2] = t;
                indf = n*m;
                cnt++;
            } else {
                tick[indf][t]++;
                tick[l][t]--;
                ins[indf].erase(itr_i);
                if (tick[l][t] == 1) {
                    extra[l].erase(t);
                    extra_gr[t].erase(itr_e_gr);
                }
                moves[cnt][0] = l;
                moves[cnt][1] = indf;
                moves[cnt][2] = t;
                indf = l;
                cnt++;
            }
        }
    }
    indf = n*m;
    cout<<min_cnt<<"\n";
    for (int i=0;i<min_cnt;i++) {
        if (min_moves[i][0] == n*m) {
            cout<<n*m+1<<' '<<indf+1<<"\n";
            indf = n*m;
        } else {
//            int x = find_type_in_group(min_moves[i][0], min_moves[i][2], m, g[min_moves[i][0]]);
            int x = (*st[min_moves[i][0]][min_moves[i][2]].begin());
            st[min_moves[i][0]][min_moves[i][2]].erase(x);
            cout<<x+1<<' '<<indf+1<<"\n";
            indf = x;
        }
    }
}
