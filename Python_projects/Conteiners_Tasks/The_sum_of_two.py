def two_sum(a: list[int], target: int):
    b = a.copy()
    b.sort()
    i = 0
    j = len(b) - 1
    nowsum = b[i] + b[j]
    while (i < j):
        if nowsum < target:
            i += 1
            nowsum = b[i] + b[j]
        elif nowsum > target:
            j -= 1
            nowsum = b[i] + b[j]
        else:
            return tuple(sorted([a.index(b[i]), len(a) - 1 - a[::-1].index(b[j])]))
    else:
        if a[i] + a[j] == target and i !=j:
            return tuple(sorted([a.index(b[i]), len(a) - 1 - a[::-1].index(b[j])]))
        else:
            raise ValueError
print(two_sum([1,1,2],2))