lawn_in = open("room.in","r")
a = lawn_in.readline().split()
n = int(a[0])
m = int(a[1])
p = int(a[2])
#print(n, m, p)
lawn_out = open("room.out","w")
if p%2 == 1 or p <= 2*(n+m) or n+m<4:
	lawn_out.write("NO\n")
#	print('NO')
else:
	if p - 4*n - 2*m < 2*m and p - 4*n - 2*m>0 and n>1:
		lawn_out.write("YES\n")
#		print('YES')
		x = (p - 4*n - 2*m)//2
		y = n-1
#		print(0)
		lawn_out.write("%d %d\n" %(x,y))
		lawn_out.write("%d %d\n" %(x,1))
		lawn_out.write("%d %d\n" %(m-x,n))
#		print(x, y)
#		print(x, 1)
#		print(m-x, n)
	elif p - 4*m - 2*n < 2*n and p - 4*m - 2*n>0 and m>1:
		lawn_out.write("YES\n")
#		print('YES')
		x = (p - 4*m - 2*n)//2
		y = m-1
#		print(1)
		lawn_out.write("%d %d\n" %(x,y))
		lawn_out.write("%d %d\n" %(x,1))
		lawn_out.write("%d %d\n" %(n-x,m))
#		print(x, y)
#		print(x, 1)
#		print(n-x, m)
	elif p - 6*n - 2*m==0 and m>2:
		lawn_out.write("YES\n")
		lawn_out.write("%d %d\n" %(1, n))
		lawn_out.write("%d %d\n" %(1, n))
		lawn_out.write("%d %d\n" %(m-2, n))
	elif p - 6*m - 2*n==0 and n>2:
		lawn_out.write("YES\n")
		lawn_out.write("%d %d\n" %(m,1))
		lawn_out.write("%d %d\n" %(m,1))
		lawn_out.write("%d %d\n" %(m,n-2))
	else:
		lawn_out.write("NO\n")
#		print('NO')