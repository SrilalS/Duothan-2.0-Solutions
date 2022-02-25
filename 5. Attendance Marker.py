n = int(input())
l = set(list(map(int,input().split())))
number = set(range(1,n+1))
print(*number-l,sep=" ")