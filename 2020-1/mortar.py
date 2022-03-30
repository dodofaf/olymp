mortar_in = open("mortar.in","r")
r = mortar_in.readline().split()
n = int(r[0])
ar = [int(x) for x in mortar_in.readline().split()]
cnt = 0
x = 0
y = 0
while x != n-1:
	x = x + 1
	y = y + 1
	if y >= ar[x]:
		x = x-1
		y = 0
		cnt = cnt + 1

mortar_out = open("mortar.out","w")
mortar_out.write("%d\n" %(cnt+1))
