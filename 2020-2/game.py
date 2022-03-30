lawn_in = open("game.in","r")
n = int(lawn_in.readline())
m = int(lawn_in.readline())
a = lawn_in.readline()

ar = [0, 0, 0]

l0 = a[0]
l = 1

for i in range(1, m):
	if a[i] == l0:
		l += 1
	else:
		l0 = a[i]
		if l<=3:
			ar[l-1] = 1
		l = 1

if l<=3:
	ar[l-1] = 1

s = ar[0] + ar[1]  + ar[2]
lawn_out = open("game.out","w")
if s == 0:
	lawn_out.write("-1")
else:
	if s == 1:
		if ar[0] == 1:
			lawn_out.write("%d" %n)
		elif ar[1] == 1:
			if n%2 == 0:
				lawn_out.write("%d" %(n//2))
			else:
				lawn_out.write("-1")
		else:
			if n%3 == 0:
				lawn_out.write("%d" %(n//3))
			else:
				lawn_out.write("-1")
	elif s == 2:
		if ar[0] == 0:
			if n == 1:
				lawn_out.write("-1")
			elif n%3 == 0:
				lawn_out.write("%d" %(n//3))
			elif n%3 == 2:
				lawn_out.write("%d" %(n//3+1))
			elif n == 2 or n == 4:
				lawn_out.write("%d" %(n//2))
			else:
				lawn_out.write("%d" %(2+(n-4)//3))
		elif ar[1] == 0:
			lawn_out.write("%d" %((n//3)+(n%3)))
		else:
			lawn_out.write("%d" %((n//2)+(n%2)))
	else:
		if n%3 == 0:
			lawn_out.write("%d" %(n//3))
		else:
			lawn_out.write("%d" %(n//3+1))
