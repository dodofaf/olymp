#include <iostream>
#include <vector>

using namespace std;


void input_ar(int n, vector<int> &ar)
{
	for (int i=0;i<n;++i) {
		cin>>ar[i];
	}
}

static int rds(int sum)
{
	return (sum/10 + (sum%10>4))*10;
}

int main()
{
	int n, d;
	cin>>n>>d;
	vector<int> ar(n);
	input_ar(n, ar);
	vector<vector<int>> arr(n, vector<int>(n, 0));
	for(int i=0;i<n;i++) {
		int s = 0;
		for(int j=i+1;j<n;j++) {
			s+=ar[j];
			int rs = rds(s);
			arr[i][j] = rs;
		}
	}
	vector<vector<int>> res(d+1, vector<int>(n));
	int s = 0;
	for (int i=0;i<n;++i) {
		s+=ar[i];
		res[0][i] = rds(s);
	}
	int min = res[0][n-1];
	for (int i=1;i<d+1;++i) {
		res[i][0] = res[i-1][0];
		for (int j=1;j<n;++j) {
			int mn = res[i-1][j];
			for (int j1=0;j1<j;j1++){
				if (mn>arr[j1][j]+res[i-1][j1]) {
					mn=arr[j1][j]+res[i-1][j1];
				}
			}
			res[i][j] = mn;
		}
		if (min>res[i][n-1]){
			min=res[i][n-1];
		}
	}
	cout<<min<<"\n";
}
