from math import *

lawn_in = open("mafia.in","r")
inp = lawn_in.readline().split()
#inp = input().split()
n = int(inp[0])
a = int(inp[1])
b = int(inp[2])
lawn_out = open("mafia.out","w")

i = 0
if b == 0:
	i = n//a
	if n%a>0:
		i+=1
else:
	while n > i*(a + b*(i-1)):
		i += 1

#print(i)
lawn_out.write("%d" %i)
