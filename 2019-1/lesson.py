lawn_in = open("lesson.in","r")
a = lawn_in.readline().split()
for i in range(4):
	a[i] = int(a[i])
#print(a)
mx = a[0]*(a[1]+a[2]-a[3])
k = 0
#print(mn)
c = a[2]*(a[0]+a[3]-a[1])
if mx<c:
	mx = c
	k = 1
#print(mn)
c = a[3]*(a[2]+a[1]-a[0])
if mx<c:
	mx = c
	k = 2
#print(mn)
c = a[1]*(a[0]+a[3]-a[2])
if mx<c:
	mx = c
	k = 3
#print(mn)
#print(k)
lawn_out = open("lesson.out","w")
lawn_out.write("%d" %k)