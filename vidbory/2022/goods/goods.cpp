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
    for (int i=0;i<n;++i) {
        for (int j=0;j<m;++j) {
            cin>>g[i][j];
            g[i][j]--;
            tick[i][g[i][j]]++;
            st[i][g[i][j]].insert(i*m+j);
        }
    }
    int cnt = 0, min_cnt=2e9;
    vector<vector<int>> moves(n*m+2, vector<int>(3, -1)), min_moves;
    int indf = n*m, q = -1;
    while(cnt>0 || min_cnt==2e9) {
        if (cnt == min_cnt) {
            moves[cnt][0] = -1;
            moves[cnt][1] = -1;
            moves[cnt][1] = -1;
            cnt--;
            continue;
        }
        if (moves[cnt][0] != -1) {
            int x = moves[cnt][0];
            int y = moves[cnt][1];
            int type = moves[cnt][2];
            if (x!=n*m) {
                if (y!=n*m) {
                    tick[y][type]--;
                } else {
                    q = -1;
                }
                tick[x][type]++;
            } else {
                tick[y][type]--;
                q = type;
            }
            indf = y;
        }
        if (q==-1) {
            int l = -1;
            int t = -1;
            if (moves[cnt][0] == -1){
                for (int i=0;i<n;i++){
                    for (int j=0;j<m;j++) {
                        if (tick[i][j] > 1) {
                            l = i;
                            t = j;
                            break;
                        }
                    }
                    if (l!=-1){break;}
                }
            } else {
                for (int i=moves[cnt][2]+1;i<m;i++) {
                    if (tick[moves[cnt][0]][i] > 1) {
                        l = moves[cnt][0];
                        t = i;
                        break;
                    }
                }
                if (l == -1) {
                    for (int i=moves[cnt][0]+1;i<n;i++){
                        for (int j=0;j<m;j++) {
                            if (tick[i][j] > 1) {
                                l = i;
                                t = j;
                                break;
                            }
                        }
                        if (l!=-1){break;}
                    }
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
                q = t;
                indf = l;
                cnt++;
            }
        } else {
            int t = moves[cnt][2];
            int l = -1;
            if (moves[cnt][0] != -1) {
                for (int i=moves[cnt][0]+1;i<n;i++) {
                    if (tick[i][moves[cnt][2]] > 1) {
                        l = i;
                    }
                }
            }
            if (l == -1) {
                for (int i=t+1;i<m;++i) {
                    if (tick[indf][i] == 0) {
                         t = i;
                         break;
                    }
                }
                if (t == moves[cnt][2]) {
                    moves[cnt][0] = -1;
                    moves[cnt][1] = -1;
                    moves[cnt][2] = -1;
                    cnt--;
                    continue;
                }
                for (int i=0;i<n;++i) {
                    if (tick[i][t]>1) {
                        l = i;
                        break;
                    }
                }
            }
            if (l == -1) {
                tick[indf][q]++;
                q = -1;
                moves[cnt][0] = n*m;
                moves[cnt][1] = indf;
                moves[cnt][2] = t;
                indf = n*m;
                cnt++;
            } else {
                tick[indf][t]++;
                tick[l][t]--;
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
