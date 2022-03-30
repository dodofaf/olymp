lawn_in = open("passat.in","r")
n = int(lawn_in.readline())
ar = []
for i in range(n):
	a = lawn_in.readline().split()
	ar.append([int(a[1]), int(a[0])])
ar.sort()
cnthol = ar[0][0]- ar[0][1]
cntfree = 0
ld = ar[0][0]
for i in range(1, n):
	cntfree = cntfree + ar[i][0] - ld - ar[i][1]
	if cntfree<0:
		cnthol += cntfree
		cntfree = 0
	ld = ar[i][0]
lawn_out = open("passat.out","w")
lawn_out.write("%d" %cnthol)
