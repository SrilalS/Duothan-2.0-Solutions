def grid(m,n,mem = {}):
    if (m,n) in mem:
        return mem[(m,n)]
    if(m==0 or n ==0):
        return 0;
    if (m==1 or n==1):
        return 1;
    k = grid(m-1,n,mem)+grid(m,n-1,mem)
    mem[(m,n)] = k
    return k;

m,n = map(int,input().split())
print(grid(m,n))