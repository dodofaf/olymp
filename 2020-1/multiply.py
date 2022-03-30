import random
def array(ar, n):
	for i in range(n):
		ar.append(2**random.randint(1, 10))

def mxmn(dil, x, y, mx, mn):
	for i in range(x+1, y+1):
		for j in range(10):
			if mx[j]<dil[i][j]:
				mx[j]=dil[i][j]
			if mn[j]>dil[i][j]:
				mn[j]=dil[i][j]

def cntseg(dil, x, y, s):
	cn = 0
	c = 1

	for i in range(x, y):
		mx = dil[i][:]
		mn = dil[i][:]
		for j in range(i+1,y+1):
			m = 0
			for q in range(10):
				if mx[q]<dil[j][q]:
					mx[q] = dil[j][q]
				elif mn[q]>dil[j][q]:
					mn[q] = dil[j][q]
				if mn[q]*s<mx[q]:
					m = 1
					break
			if m == 0:
				c += 1
			else:
				break
		cn += c
		c = 1
	return cn+1

def cntseg1(dil, x, y, s):
	cn = 0
	mx = dil[0][:]
	mn = mx[:]
	start = x
	end = x
	i = x+1
	while i != y+1:
		m = 0
		for q in range(10):
			if mx[q]<dil[i][q]:
				mx[q] = dil[i][q]
			elif mn[q]>dil[i][q]:
				mn[q] = dil[i][q]
			if mn[q]*s<mx[q]:
				m = 1
				break

		if m == 0:
			end += 1
		else:
			cn += end - start + 1
			start += 1
			if i== start:
				i+=1
			if start>end:
				end = start
			mx = dil[start][:]
			mn = dil[start][:]
			mxmn(dil, start, end, mx, mn)
			i = i - 1
		i += 1
	for i in range(end-start+2):
		cn+=i
	return cn

multiply_in = open("multiply.in","r")
r = multiply_in.readline().split()
n = int(r[0])
k = int(r[1])
g = int(r[2])


ar = multiply_in.readline().split()

for i in range(n):
	ar[i] = int(ar[i])

cnt = 0
cnt1 = 0

if k == 0:
	c = 1
	for i in range(1, n):
		if ar[i] == ar[i-1]:
			c = c+1
		else:
			for i in range(1, c+1):
				cnt = cnt + i
			c = 1

	for i in range(1, c+1):
		cnt = cnt+i

elif k >= 20:
	dil = []
	for i in range(n):
		q = [1]
		x = ar[i]
		d = 2
		while x != 1:
			while x//d >0 and x%d == 0:
				if q[len(q)-1] != d:
					q.append(d)
				x = x//d
			d = d +1
		dil.append(q)

	c = 1	
	for i in range(1, n):
		if ar[i] == ar[i-1]:
			c = c+1
		elif dil[i] == dil[i-1]:
			c = c + 1
		else:
			for i in range(1, c+1):
				cnt = cnt + i
			c = 1

	for i in range(1, c+1):
		cnt = cnt+i

else:
	dil = []
	q = [2, 3, 5, 7, 11, 13, 17, 19, 23, 29]
	for i in range(n):
		p = [0]*10
		x = ar[i]
		for j in range(10):
			while x%q[j] == 0:
				x = x//q[j]
				p[j] += 1
		dil.append(p)

	start = 0
	end = 0
	a = dil[0]

	s = 1
	for i in range(k):
		s = s*2

	for i in range(1, n):
		b = True
		for j in range(10):
			b = ((a[j]>0 and dil[i][j]>0) or (a[j]==0 and dil[i][j]==0))

		if b:
			end +=1
		else:
			cnt += cntseg(dil, start, end, s)
			a = dil[i]
			start = i
			end = i

	cnt += cntseg(dil, start, end, s)
lawn_out = open("multiply.out","w")
lawn_out.write("%d" %cnt)
