#include <bits/stdc++.h>

using namespace std;

struct Sum
{
	int rs;
	int ind;
}; 
struct St
{
	int rss;
	vector<Sum> ar;
}; 

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

void mn_sum(int d, int st, int &min_sum, int sum, vector<St> &arr)
{
	int md = rds(4*(d+1));
	if (min_sum <= sum-md) {return;}
	int rdsg = arr[st].rss;
	for (auto i=arr[st].ar.begin();i!=arr[st].ar.end();i++) {
		int ds = rdsg-(i->rs + arr[i->ind+1].rss);
		sum -= ds;
		if (min_sum>sum) {
			min_sum = sum;
		}
		if (d != 1) {
			mn_sum(d-1, i->ind+1, min_sum, sum, arr);
		}
		sum += ds;
		if (min_sum <= sum-md) {return;}
	}
}

int main()
{
	int n, d;
	cin>>n>>d;
	vector<int> ar(n);
	input_ar(n, ar);
	vector<St> arr(n);
	for(int i=0;i<n;i++) {
		int s = 0;
		arr[i].ar.reserve(n);
		for(int j=i;j<n-1;j++) {
			s+=ar[j];
			int rs = rds(s);
			if (s>rs && s-rs+ar[j+1]>4) {
				Sum s1;
				s1.ind = j;
				s1.rs = rs;
				arr[i].ar.push_back(s1);
			}
		}
		s+=ar[n-1];
		arr[i].rss = rds(s);
	}
	int min_sum = rds(sum_ar(n, ar));
	mn_sum(d, 0, min_sum, min_sum, arr);
	cout<<min_sum<<"\n";
}