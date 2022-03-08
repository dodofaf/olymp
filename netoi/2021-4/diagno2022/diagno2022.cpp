#include <bits/stdc++.h>

using namespace std;

int main()
{
	long long n, k;
	cin>>n>>k;
	long long cnt = 0;
	while (n != 1 && k != 1) {
		if (n%(k+1) != 0) {
			n = n/(k+1) + 1;
		} else {
			n /= k+1;
		}
		k--;
		cnt++;
	}
	if (k == 1) {
		cnt += n-1;
	}
	cout<<cnt<<endl;
}
/*
Тест	Результат	Час роботи
00	PASSED (+0)	0.01 с
000	PASSED (+0)	0.01 с
01	PASSED (+5)	0.01 с
02	PASSED (+5)	0.01 с
03	PASSED (+5)	0.01 с
04	FAILED (Wrong Answer)	0.01 с
05	PASSED (+5)	0.01 с
06	PASSED (+5)	0.01 с
07	PASSED (+5)	0.01 с
08	PASSED (+5)	0.01 с
09	FAILED (Wrong Answer)	0.01 с
10	FAILED (Wrong Answer)	0.01 с
11	FAILED (Wrong Answer)	0.01 с
12	FAILED (Wrong Answer)	0.01 с
13	FAILED (Wrong Answer)	0.01 с
14	FAILED (Wrong Answer)	0.01 с
15	FAILED (Wrong Answer)	0.01 с
16	FAILED (Wrong Answer)	0.01 с
17	FAILED (Wrong Answer)	0.01 с
18	PASSED (+5)	0.01 с
19	PASSED (+5)	0.01 с
20	FAILED (Wrong Answer)	0.01 с

Прошло тестов: 11 из 22.

Набрано баллов: 45 из 100.
*/