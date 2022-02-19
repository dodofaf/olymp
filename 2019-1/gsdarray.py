from math import *

def main():
	n = int(lawn_in.readline())
	a = lawn_in.readline().split()
	for i in range(n):
		a[i] = int(a[i])
	x = max(a)
	d = 2
	dil = 1
	cnt = x*n
	for i in range(2, int(sqrt(x))):
		if x%i == 0:
			dil = i
			cn = 0
			for i in range(n):
				m = (dil - a[i]%dil)%dil
				cn += m
				a[i] += m
			mx = a[0]
			for i in range(1, n):
				if a[i]<mx:
					cn += mx-a[i]
				else:
					mx = a[i]
			if cn<cnt:
				cnt = cn
#				print(dil)
	if x ==1:
		cnt = 0
	lawn_out.write("%d\n" %cnt)
#	print(cnt)


lawn_in = open("gcdarray.in","r")
lawn_out = open("gcdarray.out","w")
t = int(lawn_in.readline())
for i in range(t):
	main()