t = eval(input())
for _ in range(t):
    word = list(input().strip())
    start = -1
    for i in range(0, len(word) - 1):
        if word[i] < word[i + 1]:
            start = i

    if start == -1:
        print("no answer")
        continue

    end = -1
    for j in range(start + 1, len(word)):
        if word[start] < word[j]:
            end = j

    word[start], word[end] = word[end], word[start]
    a = word[start + 1:]
    a.sort()

    for j in range(start + 1, len(word)):
        word[j] = a[j - start - 1]

    print("".join(word))
