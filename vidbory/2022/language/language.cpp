#include <bits/stdc++.h>

using namespace std;

struct Word
{
	int st;
	int fn;
};

int main()
{
	string line;
	getline(cin, line);
	int q;
	cin>>q;
	vector<vector<int>> zap(q, vector<int>(2));
	for(int i=0;i<q;i++) {
		cin>>zap[i][0]>>zap[i][1];
		zap[i][0]--;
		zap[i][1]--;
	}
	vector<Word> words;
	int st = 0;
	int fn = 0;
	int n = line.length();
	int nw = 0;
	for (int i=1;i!=n;i++) {
		if ((line[i] != line[i-1]) && !(line[i] == 'b' && line[i-1] == 'a') && !(line[i] == 'c' && line[i-1] == 'b') && !(line[i] == 'c' && line[i-1] == 'a')) {
			Word w;
			w.st = st;
			w.fn = fn;
			words.push_back(w);
			st = i;
			fn = i;
			nw++;
		} else {
			fn++;
		}
	}
	Word w;
	w.st = st;
	w.fn = fn;
	words.push_back(w);
	nw++;
	for(int i=0;i<q;i++) {
		st = zap[i][0];
		fn = zap[i][1];
		int l=0;
		for (int j=0;j!=nw;j++) {
			if(((words[j].st >= st) && (words[j].fn <= fn))){
				l++;
			} else {
				if (fn < words[j].fn && fn >= words[j].st) {
					l++;
					break;
				}
				if (st>words[j].st && st<=words[j].fn) {
					l++;
				}
			}
		}
		cout<<l<<"\n";
	}
}