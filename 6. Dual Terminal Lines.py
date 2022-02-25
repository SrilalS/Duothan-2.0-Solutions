acount = int(input())
a = input()
achars = set(a)
bcount = int(input())
b = input()
bchars = set(b)
common = achars.intersection(bchars)
total = 0
for i in common:
    total += min(a.count(i),b.count(i))
print(total)