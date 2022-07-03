#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int n, m;
    cin>>n>>m;
    vector<vector<int>> g(n, vector<int>(m)), tick(n, vector<int>(m));
    for (int i=0;i<n;++i) {
        for (int j=0;j<m;++j) {
            cin>>g[i][j];
            g[i][j]--;
            tick[i][g[i][j]]++;
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
        if (moves[cnt][0] != -1) {
            int x = moves[cnt][0];
            int y = moves[cnt][1];
            if (x!=n*m) {
                if (y!=n*m) {
                    tick[y/m][g[y/m][y%m]]--;
                    g[x/m][x%m] = g[y/m][y%m];
                    g[y/m][y%m] = -1;
                } else {
                    g[x/m][x%m] = q;
                    q = -1;
                }
                indf = y;
                tick[x/m][g[x/m][x%m]]++;
            } else {
                tick[y/m][g[y/m][y%m]]--;
                q = g[y/m][y%m];
                g[y/m][y%m]=-1;
                indf = y;
            }
        }
        if (q==-1) {
            int l = -1;
            for (int i=moves[cnt][0]+1;i<n*m;++i) {
                if (tick[i/m][g[i/m][i%m]]>1 && g[i/m][i%m] != g[moves[cnt][0]/m][moves[cnt][0]%m]) {
                    l = i;
                    break;
                }
            }
            if (l == -1) {
                if (moves[cnt][0] == -1 && cnt<min_cnt) {
                    min_cnt = cnt;
                    min_moves = moves;
                }
                moves[cnt][0] = -1;
                moves[cnt][1] = -1;
                cnt--;
            } else {
                moves[cnt][0] = l;
                moves[cnt][1] = indf;
                cnt++;
                tick[l/m][g[l/m][l%m]]--;
                q = g[l/m][l%m];
                g[l/m][l%m] = -1;
                indf = l;
            }
        } else {
            int l = indf/m, x=-1;
            if (moves[cnt][0]!=-1 && moves[cnt][0]!=n*m) {
                x = g[moves[cnt][0]/m][moves[cnt][0]%m];
            } else if (moves[cnt][0]==n*m) {
                x = q;
            }
            for (int i=x+1;i<m;++i) {
                if (tick[l][i] == 0) {
                     x = i;
                     break;
                }
            }
            if (x == -1 || (moves[cnt][0]==n*m && x == q) || (moves[cnt][0]!=-1 && moves[cnt][0]!=n*m && x == g[moves[cnt][0]/m][moves[cnt][0]%m])) {
                moves[cnt][0] = -1;
                moves[cnt][1] = -1;
                cnt--;
                continue;
            }
            int l1 = -1;
            for (int in=0;in<n*m;++in) {
                int i = in/m,j =in%m;
                if (tick[i][x]>1 && g[i][j] == x) {
                    l1 = in;
                    break;
                }
            }
            if (l1 == -1) {
                g[l][indf%m]=q;
                tick[l][q]++;
                q = -1;
                moves[cnt][0] = n*m;
                moves[cnt][1] = indf;
                indf = n*m;
                cnt++;
            } else {
                int i = l1/m,j = l1%m;
                tick[l][x]++;
                tick[i][x]--;
                g[l][indf%m]=x;
                g[i][j]=-1;
                moves[cnt][0] = i*m+j;
                moves[cnt][1] = indf;
                indf = i*m+j;
                cnt++;
                l1 = i;
            }
        }
    }
    cout<<min_cnt<<"\n";
    for (int i=0;i<min_cnt;i++) {
        cout<<min_moves[i][0]+1<<' '<<min_moves[i][1]+1<<"\n";
    }
}
