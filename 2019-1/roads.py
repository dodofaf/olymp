def happiness(a, n, roads, x):
	tick = [0]*n
	line = [x]
#	print(len(line))
	ret = 0
	while  len(line) != 0:
#		print(len(line))
		y = line.pop()
		if tick[y] == 0:
			ret += a[y]
			tick[y] = 1
			for i in range(n):
				if roads[y][i] == 1 and tick[i] == 0:
					line.append(i)
	return ret

lawn_in = open("roads.in","r")
a = lawn_in.readline().split()
#a = input().split()
n = int(a[0])
m = int(a[1])
d = int(a[2])
s = int(a[3])

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
	q = lawn_in.readline().split()#input().split()
	roads[int(q[0])-1][int(q[1])-1] = 1
	roads[int(q[1])-1][int(q[0])-1] = 1

evtype = [2]
event = [[0, 0]]
for i in range(d):
	q = lawn_in.readline().split()#input().split()
	evtype.append(int(q[0]))
	if evtype[i+1] == 1:
		event.append([int(q[1])-1, int(q[2])-1])
	else:
		event.append([int(q[1])-1, int(q[2])])
#print(event)
tick = [0]*n
pairs = []
for i in range(s):
	q = lawn_in.readline().split()#input().split()
	pairs.append([int(q[0])-1, int(q[1])-1, int(q[2])])
	tick[pairs[i][0]] = 1
	tick[pairs[i][1]] = 1

day = [-1]*s
for i in range(d+1):
	if evtype[i] == 1:
#		print(event[i])
		roads[event[i][0]][event[i][1]] = 0
		roads[event[i][1]][event[i][0]] = 0
	else:
		a[event[i][0]] = a[event[i][0]] - event[i][1]

	hap = [0]*n
	for j in range(n):
		if tick[j] == 1:
			hap[j] = happiness(a, n, roads, j)
#	print(ar)
	for j in range(s):
		if hap[pairs[j][0]]+hap[pairs[j][1]]<pairs[j][2] and day[j] == -1:
			day[j] = i


lawn_out = open("roads.out","w")
for i in range(s):
	if day[i] == -1:
		lawn_out.write("%d\n" %d)
	else:
		lawn_out.write("%d\n" %(day[i]-1))
