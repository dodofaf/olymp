lawn_in = open("lawn.in","r")
inp = lawn_in.readline().split()
#inp = input().split()
n = int(inp[0])
k = int(inp[1])
cnt = n//k
if cnt<2 and k<n:
	cnt+=1
if n%k>0:
	cnt += 1
lawn_out = open("lawn.out","w")
lawn_out.write("%d" %cnt)
print(cnt)