import random

def check(a, n):
	for i in range(3):
		for j in range(3):
			if j != i:
				for x in range(3):
					if x!=j and x!=i:
						if a[i]**3 + a[j]**2+a[x] == n:
							lawn_out.write("%d %d %d" %(a[i], a[j], a[x]))
							return False
	return True
lawn_in = open("equation.in","r")
a = lawn_in.readline().split()
k = int(a.pop())
for i in range(3):
	a[i] = int(a[i])
lawn_out = open("equation.out","w")
m = check(a, k)
if m:
	lawn_out.write("-1 -1 -1")
