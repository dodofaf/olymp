#include <iostream>
#include <set>
#include <vector>

using namespace std;

int main()
{
    int n, m;
    cin>>n>>m;
    vector<vector<int>> g(n, vector<int>(m)), tick(n, vector<int>(m));
    vector<set<int>> extra(m);
//    vector<bool>
    for (int i=0;i<n;++i) {
        for (int j=0;j<m;++j) {
            cin>>g[i][j];
            g[i][j]--;
            tick[i][g[i][j]]++;
            if (tick[i][g[i][j]]>1){
                extra[g[i][j]].insert(i*m+j);
            }
        }
    }
    vector<set<int>> ins(n);
    for(int i=0;i<n;i++) {
        for (int j=0;j<m;j++){
            if (tick[i][j] == 0) {
                ins[i].insert(j);
            }
        }
    }
    int cnt = 0, min_cnt=2e9;
    vector<vector<int>> moves(n*m+2, vector<int>(2, -1)), min_moves;
    int indf = n*m, q = -1;
    while(cnt>0 || min_cnt==2e9) {
        if (cnt == min_cnt) {
            moves[cnt][0] = -1;
            moves[cnt][1] = -1;
            cnt--;
            continue;
        }
        auto itr = extra[0].begin();
        auto itr2 = ins[0].begin();
        if (moves[cnt][0] != -1) {
            int x = moves[cnt][0];
            int y = moves[cnt][1];
            if (x!=n*m) {
                if (y!=n*m) {
                    tick[y/m][g[y/m][y%m]]--;
                    g[x/m][x%m] = g[y/m][y%m];
                    g[y/m][y%m] = -1;
                    itr2 = ins[y/m].insert(g[x/m][x%m]).first;
                } else {
                    g[x/m][x%m] = q;
                    q = -1;
                }
                itr = extra[g[x/m][x%m]].insert(x).first;
                indf = y;
                tick[x/m][g[x/m][x%m]]++;
            } else {
                tick[y/m][g[y/m][y%m]]--;
                q = g[y/m][y%m];
                g[y/m][y%m]=-1;
                itr2 = ins[y/m].insert(q).first;
                indf = y;
            }
        }
        if (q==-1) {
            int x = g[moves[cnt][0]/m][moves[cnt][0]%m];
            itr++;
            while (itr == extra[x].end()){
                x++;
                if (g[moves[cnt][0]/m][moves[cnt][0]%m] != m) {
                    itr = extra[x].begin();
                } else {
                    break;
                }
            }
            if (x == m) {
                if (moves[cnt][0] == -1 && cnt<min_cnt) {
                    min_cnt = cnt;
                    min_moves = moves;
                }
                moves[cnt][0] = -1;
                moves[cnt][1] = -1;
                cnt--;
                continue;
            }
            int i = (*itr);
            moves[cnt][0] = i;
            moves[cnt][1] = indf;
            cnt++;
            extra[x].erase(itr);
            ins[indf/m].erase(ins[indf/m].find(x));
            tick[i/m][g[i/m][i%m]]--;
            q = g[i/m][i%m];
            g[i/m][i%m] = -1;
            indf = i;
        } else {
            int l = indf/m, x=-1;
            if (moves[cnt][0]!=-1 && moves[cnt][0]!=n*m) {
                x = (*itr2);
                itr++;
                if (itr != extra[l].end()){
                    int i = (*itr)/m,j = (*itr)%m;
                    if (tick[i][x]>1 && g[i][j] == x) {
                        tick[l][x]++;
                        tick[i][x]--;
                        g[l][indf%m]=x;
                        g[i][j]=-1;
                        moves[cnt][0] = (*itr);
                        moves[cnt][1] = indf;
                        extra[l].erase(itr);
                        ins[l].erase(itr2);
                        indf = i*m+j;
                        cnt++;
                        break;
                    }
                }
            }
            if (g[l][indf%m] == -1) {
                if (moves[cnt][0] == -1) {
                    itr2 = ins[l].begin();
                    itr = extra[(*itr2)].begin();
                    if(itr == extra[(*itr2)].end()) {
                        g[l][indf%m]=q;
                        tick[l][q]++;
                        q = -1;
                        ins[l].erase(itr2);
                        moves[cnt][0] = n*m;
                        moves[cnt][1] = indf;
                        indf = n*m;
                        cnt++;
                    } else {
                        x = (*itr2);
                        int in = (*itr);
                        tick[l][x]++;
                        tick[in/m][x]--;
                        g[l][indf%m]=x;
                        g[in/m][in%m]=-1;
                        extra[l].erase(itr);
                        ins[l].erase(itr2);
                        moves[cnt][0] = in;
                        moves[cnt][1] = indf;
                        indf = in;
                        cnt++;
                    }
                } else {
                    itr2++;
                    if (itr2 == ins[l].end()) {
                        moves[cnt][0] = -1;
                        moves[cnt][1] = -1;
                        cnt--;
                        continue;
                    } else {
                        x = (*itr2);
                        int in = (*itr);
                        tick[l][x]++;
                        tick[in/m][x]--;
                        g[l][indf%m]=x;
                        g[in/m][in%m]=-1;
                        extra[l].erase(itr);
                        ins[l].erase(itr2);
                        moves[cnt][0] = in;
                        moves[cnt][1] = indf;
                        indf = in;
                        cnt++;
                    }
                }  
            }
        }
    }
    
    cout<<min_cnt<<"\n";
    for (int i=0;i<min_cnt;i++) {
        cout<<min_moves[i][0]+1<<' '<<min_moves[i][1]+1<<"\n";
    }
}
