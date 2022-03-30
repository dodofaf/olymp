exam_in = open("exam.in","r")
r = exam_in.read().split()
n = int(r[0])
a = int(r[1])
b = int(r[2])
c = int(r[3])


exam_out = open("exam.out","w")
if a == b:
	exam_out.write("%d" %(n+c))
elif a != 0:
	y = n-(c//4)
	if y<0:
		y = 0
	exam_out.write("%d" %y)
else:
	exam_out.write("%d" %n)
exam_out.write("\n")