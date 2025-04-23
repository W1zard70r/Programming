def longest_ideal_route(sequence):
    max_length = 0
    n = len(sequence)
    
    for i in range(n):
        l, r = i, i
        while l >= 0 and r < n and sequence[l] == sequence[r]:
            if (r - l + 1) > max_length:
                max_length = r - l + 1
            l -= 1
            r += 1
        
        l, r = i, i + 1
        while l >= 0 and r < n and sequence[l] == sequence[r]:
            if (r - l + 1) > max_length:
                max_length = r - l + 1
            l -= 1
            r += 1
    
    return max_length

n = int(input())
s = list(map(int, input().split()))
max_len = longest_ideal_route(s)
print(max_len if max_len > 1 else 0)