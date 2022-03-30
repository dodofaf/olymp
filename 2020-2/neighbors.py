lawn_in = open("neighbors.in","r")
a = lawn_in.readline().split()
n = int(a[0])
m = int(a[1])
a = (m-1)//n
b = (m-1)%n+1
lawn_out = open("neighbors.out","w")
if a+1 == b:
	lawn_out.write("yes ")
else:
	lawn_out.write("no ")
if a+b == n:
	lawn_out.write("yes")
else:
	lawn_out.write("no")
