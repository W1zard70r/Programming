import math


class SegmentTree:
	def __init__(self):
		n = int(input())
		a = [[int(x), 1] for x in input().split()]
		j = 1
		while j < n:
			j *= 2
		a += [[-math.inf, 1] for _ in range((j - n))]
		self.n = j
		self.Tree = [[0, 0] for _ in range(self.n - 1)] + a
		for i in range(self.n - 2, -1, -1):
			if self.Tree[2 * i + 1][0] > self.Tree[2 * i + 2][0]:
				self.Tree[i][0] = self.Tree[2 * i + 1][0]
				self.Tree[i][1] = self.Tree[2 * i + 1][1]
			elif self.Tree[2 * i + 1][0] < self.Tree[2 * i + 2][0]:
				self.Tree[i][0] = self.Tree[2 * i + 2][0]
				self.Tree[i][1] = self.Tree[2 * i + 2][1]
			else:
				self.Tree[i][0] = self.Tree[2 * i + 2][0]
				self.Tree[i][1] = self.Tree[2 * i + 2][1] + self.Tree[2 * i + 1][1]
	def Search(self, target_left, target_right, left, right, i):
		# print(f'{i=} {left=} {right=}')
		if target_left <= left and right <= target_right:
			return tuple(self.Tree[i])
		elif target_left <= left <= target_right and right > target_right or target_left > left and target_left <= right <= target_right or left <= target_left and target_right <= right:
			left_child_res = self.Search(target_left, target_right, left, (right + left) // 2, 2 * i + 1)
			right_child_res = self.Search(target_left, target_right, (left + right) // 2 + 1, right, 2 * i + 2)
			if left_child_res[0] > right_child_res[0]:
				return left_child_res
			elif left_child_res[0] < right_child_res[0]:
				return right_child_res
			else:
				return (right_child_res[0], left_child_res[1] + right_child_res[1])
		else:
			return (-math.inf, 0)

STree = SegmentTree()
# print(STree.Tree)
k = int(input())
for _ in range(k):
	target_left, target_right = map(int, input().split())
	res = STree.Search(target_left - 1, target_right - 1, 0, STree.n - 1, 0)
	print(*res)