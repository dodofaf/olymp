from random import *
def fi(ar, n, a, b):
	for i in range(n):
		if a==ar[i][0] and b==ar[i][1]:
			return True
		if a==ar[i][1] and b==ar[i][0]:
			return True
	return False

out = open("roads.tst", "w")
n = 10000
m = 10000
d = 10000
s = 10000
out.write("%d %d %d %d\n" %(n, m, d, s))
ar1 = []
for i in range(n):
	a =randint(1, 1000000)
	ar1.append(a)
	out.write("%d " %a)
out.write("\n")
ar = []
for i in range(m):
	a = randint(1, n)
	b = randint(1, n)
	while a == b:
		b = randint(1, n)
	while fi(ar, i, a, b):
		a = randint(1, n)
		b = randint(1, n)
		while a == b:
			b = randint(1, n)
	ar.append([a, b])
	out.write("%d %d\n" %(a, b))
for i in range(d):
	if randint(1, 3) == 1 and len(ar) > 0:
		x = randint(0, len(ar)-1)
		out.write("1 %d %d\n" %(ar[x][0], ar[x][1]))
		ar.pop(x)
	else:
		x = randint(0, n-1)
		if ar1[x] > 1:
			dl = randint(1, ar1[x]-1)
		ar1[x] -= dl; 
		out.write("2 %d %d\n" %(x+1, dl))
for i in range(s):
	a = randint(1, n)
	b = randint(1, n)
	out.write("%d %d %d\n" %(a, b, randint(1000, 1000000000)))