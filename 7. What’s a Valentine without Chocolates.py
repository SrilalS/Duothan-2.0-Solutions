import sys
 
def maxSumSubseq(A, i, n, prev=-sys.maxsize):
    if i == n:
        return 0
 
    excl = maxSumSubseq(A, i + 1, n, prev)
 
    incl = 0
 
    if prev + 1 != i:
        incl = maxSumSubseq(A, i + 1, n, i) + A[i]
 
    return max(incl, excl)
 
 
if __name__ == '__main__':
 
    A = list (map (int, input().strip().split()))
    print(maxSumSubseq(A, 0, len(A)))