import random

def tst(n, ar):
	cnt  = 0

	for i in range(n):
		for j in range(n):
			for x in range(n):
				if (ar[i]>=j) and (ar[i]>=x) and (ar[j]>=i) and (ar[j]>=x) and (ar[x]>=j) and (ar[x]>=i):
					cnt += 1

	return cnt

def arr(a, n, ar):
	ar = []
	for k in range(n):
		ar.append([])
		for l in range(n):
			c = 0
			for z in range(n):
				if a[z] >= k and l>= z:
					c += 1
			ar[k].append(c)

def array(a, n, ar):
	for k in range(n):
		ar.append([0]*n)
		if a[0]>=k:
			ar[k][0] = 1
	for k in range(n):
		for l in range(1, n):
			ar[k][l] = ar[k][l-1]
			if a[l]>= k:
				ar[k][l] += 1

def inmin(a, x, y):
	if a[x]>a[y]:
		return y
	else:
		return x

lawn_in = open("calendar.in","r")
n = int(lawn_in.readline())
a = lawn_in.readline().split()
for i in range(n):
	a[i] = int(a[i])-1

ar = []
array(a, n, ar)

cnt  = 0
lawn_out = open("calendar.out","w")

for i in range(n):
	for j in range(n):
		if a[i]>=j and a[j]>=i:
			cnt +=  ar[max(i, j)][min(a[i], a[j])]
lawn_out.write("%d\n" %cnt)
