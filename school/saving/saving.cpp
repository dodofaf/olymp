#include <bits/stdc++.h>

using namespace std;

void input_ar(int n, vector<int> &ar)
{
	for (int i=0;i<n;++i) {
		cin>>ar[i];
	}
}

int sum_ar(int n, vector<int> &ar)
{
	int sum = 0;
	for (int i=0;i<n;i++) {
		sum += ar[i];
	}
	return sum;
}

static int rds(int sum_gr)
{
	return (sum_gr/10 + (sum_gr%10>4))*10;
}

void mn_sum(int n, int d, int st, int &min_sum, int sum, int sum_gr, vector<int> &ar)
{
    if (min_sum <= sum-10*d) {return;}
    int s = 0;
    int rdsg = rds(sum_gr);
    for (int i=st;i<n-1;i++) {
        s+=ar[i];
        if (s%10<5 && s%10+ar[i+1]>4) {
	        int ds = rdsg-(rds(s) + rds(sum_gr-s));
	        if (ds>=0) {
	            sum -= ds;
	            if (min_sum>sum) {
	                min_sum = sum;
	            }
	            if (d != 1) {
	                mn_sum(n, d-1, i+1, min_sum, sum, sum_gr-s, ar);
	            }
	            sum += ds;
	            if (min_sum <= sum-10*d) {return;}
	        }
	    }
    }
}

int main()
{
	int n, d;
	cin>>n>>d;
	vector<int> ar(n);
	input_ar(n, ar);

	int sum0 = sum_ar(n, ar);
	int min_sum = rds(sum0);
	mn_sum(n, d, 0,  min_sum, min_sum, sum0, ar);
	cout<<min_sum<<"\n";
}