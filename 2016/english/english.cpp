#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main()
{
	fstream sin("english.in", sin.in);
	fstream sout("english.out", sout.out);
	string line;
	getline(sin, line);
	istringstream iss(line);
	int n;
	iss>>n;
	for (int i=0;i<n;i++) {
		string word;
		getline(sin, word);
		int len = word.length();
		bool flag = true, flag1 = true;
		for (int j=0;j<len;j++) {
			if (!flag && word[j] != 'o') {
				flag = true;
			}
			if (word[j] == 's' && j != 0 && (j == len-1 || word[j+1] != 'h')) {
				sout<<"th";
			} else {
				if (word[j] == 'e' && j == 0) {
					sout<<"ae";
				} else {
					if (word[j] == 'E') {
						sout<<"Ae";
					} else {
						if (word[j] == 'o' && j != len-1 && word[j+1] == 'o' && flag) {
							sout<<"ou";
							j++;
							flag = false;
						} else {
							if (word[j] == 'O' && j != len-1 && word[j+1] == 'o' && flag) {
								sout<<"Ou";
								j++;
								flag = false;
							} else {
								sout<<word[j];
							}
						}
					}
				}
			}
		}
		sout<<"\n";
	}
}
