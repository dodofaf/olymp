def search(ar, k, n):
	mn = k+1
	for i in range(k+2, n):
		if (ar[i][1]<=ar[mn][1]):
			mn = i
	return mn

def armn(ar, arr, n):
	arr[n-1] = ar[n-1][1]
	for i in range(n-2, -1, -1):
		arr[i] = min(arr[i+1], ar[i][1])


lawn_in = open("minions.in","r")
inp = lawn_in.readline().split()
#inp = input().split()
n = int(inp[0])


ar = []
for i in range(n):
#	a = input().split()
	a = lawn_in.readline().split()
	ar.append([int(a[1]), int(a[0])])


#ar = [int(x) for x in lawn_in.readline().split()]

ar.sort()
#print(ar)

#k = search(ar, -1, n)
#cnt = ar[k][1]
cnt = 0
lawn_out = open("minions.out","w")

armin = [0]*n
armn(ar, armin, n)
'''
#print(k, ar)
for i in range(k):
	lawn_out.write("%d\n" %cnt)
	cnt += ar[i][0]

lawn_out.write("%d\n" %cnt)
r = ar[k][1]-ar[k][0]
'''
r = ar[0][1]- ar[0][0]
#cnt += -r

for i in range(n):
	r1 = ar[i][1]- ar[i][0]
	if r1<r:
		r = r1

	if i<n-1:
		mn = armin[i]
		if mn+cnt > cnt+ar[i][0]+r:
			lawn_out.write("%d\n" %(cnt+ar[i][0]+r))
		else:
			lawn_out.write("%d\n" %(cnt+mn))
	else:
		lawn_out.write("%d\n" %(cnt+ar[i][0]+r))
	cnt+=ar[i][0]