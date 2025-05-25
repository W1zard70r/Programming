n, k = map(int, input().split())
L = []
C = []
max_wall_len = 0
for _ in range(n):
	l, c = map(int, input().split())
	L.append(l)
	C.append(c)
	if c == 1:
		max_wall_len += l
wall_fill = [[0] + [-1] * max_wall_len for _ in range(k + 1)]
for i in range(n):
	c, l = C[i], L[i]
	for j in range(max_wall_len - l, -1, -1):
		if wall_fill[c][j] != -1 and wall_fill[c][j + l] == -1:
			wall_fill[c][j + l] = i + 1

for i in range(1, max_wall_len):
	flag = True
	for c in range(1, k + 1):
		if wall_fill[c][i] == -1:
			flag = False
			break
	if flag:
		print("YES")
		ans = []
		for c in range(1, k + 1):
			start = i
			while start != 0:
				ans.append(wall_fill[c][start])
				start -= L[wall_fill[c][start] - 1]
		print(*ans)
		break
else:
	print("NO")