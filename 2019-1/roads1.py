lawn_in = open("roads.in","r")
a = [int(x) for x in lawn_in.readline().split()]
#a = input().split()
n = a[0]
m = a[1]
d = a[2]
s = a[3]

a = [int(x) for x in lawn_in.readline().split()]
#a = lawn_in.readline().split()
#a = input.split()
#for i in range(n):
#	a[i] = int(a[i])

roads = []
for i in range(n):
	q = [0]*n
	roads.append(q)

for i in range(m):
	q = [int(x) for x in lawn_in.readline().split()]#input().split()
	roads[q[0]-1][q[1]-1] = 1
	roads[q[1]-1][q[0]-1] = 1

evtype = [2]
event = [[0, 0]]
for i in range(d):
	q = [int(x) for x in lawn_in.readline().split()]#input().split()
	evtype.append(q[0])
	if evtype[i+1] == 1:
		event.append([q[1]-1, q[2]-1])
	else:
		event.append([q[1]-1, q[2]])
#print(event)
tick = [0]*n
pairs = []
for i in range(s):
	q = [int(x) for x in lawn_in.readline().split()]#input().split()
	pairs.append([q[0]-1, q[1]-1, q[2]])
	tick[pairs[i][0]] = 1
	tick[pairs[i][1]] = 1

segments = []
