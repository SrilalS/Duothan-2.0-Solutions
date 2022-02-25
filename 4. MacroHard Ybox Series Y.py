n,m = map(int,input().split())
lst = list(map(int,input().split()))
lst.sort()
seg = [lst[i:i + m] for i in range(0, len(lst), m)]
if len(seg[-1]) <m:
    seg[-2].extend(seg[-1])
    seg.pop()
s = 0
for i in range(1,len(seg)+1):
    s += sum(seg[i-1])*i
print(s%1000000007)