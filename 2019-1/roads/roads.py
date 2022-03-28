def happiness(a, n, roads, x):
	tick = [0]*n
	line = [x]
	ret = 0
	while  len(line) != 0:
		y = line.pop()
		if tick[y] == 0:
			ret += a[y]
			tick[y] = 1
			for i in range(n):
				if roads[y][i] == 1 and tick[i] == 0:
					line.append(i)
	return ret

a = input().split()
n = int(a[0])
m = int(a[1])
d = int(a[2])
s = int(a[3])

a = [int(x) for x in input().split()]

roads = []
for i in range(n):
	q = [0]*n
	roads.append(q)

for i in range(m):
	q = input().split()
	roads[int(q[0])-1][int(q[1])-1] = 1
	roads[int(q[1])-1][int(q[0])-1] = 1

evtype = [2]
event = [[0, 0]]
for i in range(d):
	q = input().split()
	evtype.append(int(q[0]))
	if evtype[i+1] == 1:
		event.append([int(q[1])-1, int(q[2])-1])
	else:
		event.append([int(q[1])-1, int(q[2])])
tick = [0]*n
pairs = []
for i in range(s):
	q = input().split()
	pairs.append([int(q[0])-1, int(q[1])-1, int(q[2])])
	tick[pairs[i][0]] = 1
	tick[pairs[i][1]] = 1

day = [-1]*s
for i in range(d+1):
	if evtype[i] == 1:
		roads[event[i][0]][event[i][1]] = 0
		roads[event[i][1]][event[i][0]] = 0
	else:
		a[event[i][0]] = a[event[i][0]] - event[i][1]

	hap = [0]*n
	for j in range(n):
		if tick[j] == 1:
			hap[j] = happiness(a, n, roads, j)
	for j in range(s):
		if hap[pairs[j][0]]+hap[pairs[j][1]]<pairs[j][2] and day[j] == -1:
			day[j] = i


for i in range(s):
	if day[i] == -1:
		print(d)
	else:
		print(day[i]-1)
