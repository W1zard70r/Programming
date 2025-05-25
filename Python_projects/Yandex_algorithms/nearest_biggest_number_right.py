import math


class SegmentTree:
	def __init__(self, n):
		a = [[int(x), i] for i,x in enumerate(input().split(), 1)]
		j = 1
		while j < n:
			j *= 2
		a += [[-math.inf, -1] for _ in range(n, j)]
		self.n = j
		self.Tree = [[0, -1] for _ in range(self.n - 1)] + a
		for i in range(self.n - 2, -1, -1):
			if self.Tree[2 * i + 1][0] > self.Tree[2 * i + 2][0]:
				self.Tree[i][0] = self.Tree[2 * i + 1][0]
				self.Tree[i][1] = self.Tree[2 * i + 1][1]
			elif self.Tree[2 * i + 1][0] < self.Tree[2 * i + 2][0]:
				self.Tree[i][0] = self.Tree[2 * i + 2][0]
				self.Tree[i][1] = self.Tree[2 * i + 2][1]
			else:
				self.Tree[i][0] = self.Tree[2 * i + 2][0]
				self.Tree[i][1] = self.Tree[2 * i + 2][1]
		# self.promises = [[-1, -1] for _ in range((2 * n - 1))]
			
	def update(self, change_index, left, right, value, i):
		if change_index < left or change_index > right:
			return self.Tree[i]
		elif change_index == left == right:
			self.Tree[i][0] = value
			return self.Tree[i]
		mid = (left + right) // 2
		if change_index <= mid:
			left_res = self.update(change_index, left, mid, value, 2 * i + 1)
			right_res = self.Tree[2 * i + 2]
			if left_res[0] > right_res[0] or (left_res[0] == right_res[0] and left_res[1] < right_res[1]): self.Tree[i] = left_res
			else: self.Tree[i] = right_res
		else:
			right_res = self.update(change_index, mid + 1, right, value, 2 * i + 2)
			left_res = self.Tree[2 * i + 1]
			if left_res[0] > right_res[0] or (left_res[0] == right_res[0] and left_res[1] < right_res[1]): self.Tree[i] = left_res
			else: self.Tree[i] = right_res
		return self.Tree[i]
		
	def Search(self, ind, x, left, right, i):
		if right < ind:
			return ("NF", -1)
		elif ind <= left:
			if self.Tree[i][0] < x:
				return ("NF", -1)
			elif left == right:
				if self.Tree[i][0] >= x:
					return ("F", right)
				else:
					return ("NF", -1)
		left_child_res = self.Search(ind, x, left, (right + left) // 2, 2 * i + 1)
		if left_child_res[0] == "F":
			return left_child_res
		right_child_res = self.Search(ind, x, (left + right) // 2 + 1, right, 2 * i + 2)
		return right_child_res
n, m = map(int, input().split())
STree = SegmentTree(n)
# print(STree.Tree)
for _ in range(m):
	request, ind, x = map(int, input().split())
	if request == 1:
		res = STree.Search(ind - 1, x, 0, STree.n - 1, 0)
		if res[0] == "F":
			print(res[1] + 1)
		else:
			print(-1)
	else:
		STree.update(ind - 1, 0, STree.n -1, x, 0)
		# print(STree.Tree)