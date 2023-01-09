#include <stack>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main()
{
	string line;
	getline(cin, line);
	int size = line.length(), res = 0, p = 0;
	while (p!=size) {
		p = size;
		for (int i=0;i<size-1;++i) {
			if ((line[i] == '(' && line[i+1] == ')') || (line[i] == '{' && line[i+1] == '}') || (line[i] == '[' && line[i+1] == ']')) line.erase(i, 2), size-=2, i=max(i-1, 0)-1;
		}
		for (int i=0;i<size && line[i]!='(';++i){
			if (line[i] == ')') line.erase(i, 1), --size, --i, ++res;
		}
		for (int i=0;i<size && line[i]!='{';++i){
			if (line[i] == '}') line.erase(i, 1), --size, --i, ++res;
		}
		for (int i=0;i<size && line[i]!='[';++i){
			if (line[i] == ']') line.erase(i, 1), --size, --i, ++res;
		}
		for (int i=size-1;i>-1 && line[i]!=')';--i){
			if (line[i] == '(') line.erase(i, 1), --size, ++res;
		}
		for (int i=size-1;i>-1 && line[i]!='}';--i){
			if (line[i] == '{') line.erase(i, 1), --size, ++res;
		}
		for (int i=size-1;i>-1 && line[i]!=']';--i){
			if (line[i] == '[') line.erase(i, 1), --size, ++res;
		}
	}
	int n1=0, n2=0, n3=0;
	for (int i=0;i<size;++i) {
		if (line[i] == '(') n1++;
		else if (line[i] == ')') n1--;
		else if (line[i] == '{') n2++;
		else if (line[i] == '}') n2--;
		else if (line[i] == '[') n3++;
		else if (line[i] == ']') n3--;
	}

//	cout<<line<<'\n';
//	cout<<size<<'\n';
	if (!line.empty()) {
		int t = abs(n1)+abs(n2)+abs(n3);
		if (!t) t = 2;
		for (;t<=size;t+=2) {
//			cout<<"t="<<t<<'\n';
			vector<int> q(t, 0);
			for (int i=0;i<t;++i) q[i] = i;
			while (q[0]!=size-t+1) {
//				for (int i=0;i<t;++i) cout<<q[i]<<' ';
//				cout<<'\n';
				string s;
				int n = size;
				int itr = 0;
				for (int i=0;i<n;++i) {
					if (i==q[itr]) ++itr;
					else s.push_back(line[i]);
				}
				n -= t;
				for (int i=0;i<n;++i) {
					if ((s[i] == '(' && s[i+1] == ')') || (s[i] == '{' && s[i+1] == '}') || (s[i] == '[' && s[i+1] == ']')) s.erase(i, 2), n-=2, i=max(i-1, 0)-1;
				}
				if (s.empty()) {
					cout<<res+t<<'\n';
					return 0;
				} else {
					int i = t-1;
					++q[i];
					while (i>0 && q[i]==size-t+i+1) {
						--i;
						++q[i];
					}
					++i;
					for (;i<t;++i) q[i] = q[i-1]+1;
				}
			}
//			cout<<q[0]<<' '<<t<<'\n';
		}
	}
	cout<<res<<'\n';
}
