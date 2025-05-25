import math


class SegmentTree:
    def __init__(self):
        n = int(input())
        a = [[int(x), 1] for x in input().split()]
        j = 1
        while j < n:
            j *= 2
        a += [[math.inf, 1] for _ in range(n, j)]
        self.n = j
        self.Tree = [[0, -1] for _ in range(self.n - 1)] + a
        for i in range(self.n - 2, -1, -1):
            if self.Tree[2 * i + 1][0] < self.Tree[2 * i + 2][0]:
                self.Tree[i][0] = self.Tree[2 * i + 1][0]
                self.Tree[i][1] = self.Tree[2 * i + 1][1]
            elif self.Tree[2 * i + 1][0] > self.Tree[2 * i + 2][0]:
                self.Tree[i][0] = self.Tree[2 * i + 2][0]
                self.Tree[i][1] = self.Tree[2 * i + 2][1]
            else:
                self.Tree[i][0] = self.Tree[2 * i + 2][0]
                self.Tree[i][1] = self.Tree[2 * i + 2][1] + \
                    self.Tree[2 * i + 1][1]
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
            if left_res[0] < right_res[0]:
                self.Tree[i] = left_res.copy()
            elif left_res[0] == right_res[0]:
                self.Tree[i][0] = left_res[0]
                self.Tree[i][1] = left_res[1] + right_res[1]
            else:
                self.Tree[i] = right_res.copy()
        else:
            right_res = self.update(
                change_index, mid + 1, right, value, 2 * i + 2)
            left_res = self.Tree[2 * i + 1]
            if left_res[0] < right_res[0]:
                self.Tree[i] = left_res.copy()
            elif left_res[0] == right_res[0]:
                self.Tree[i][0] = left_res[0]
                self.Tree[i][1] = left_res[1] + right_res[1]
            else:
                self.Tree[i] = right_res.copy()
        return self.Tree[i]

    def Knull(self, left, right, target_left, target_right, nulls_left, i):
        mid = (left + right) // 2
        if target_left <= left and right <= target_right:
            if self.Tree[i][0] == 0:
                if self.Tree[i][1] >= nulls_left:
                    if right == left and nulls_left == 1:
                        return ("F", right)
                    left_result = self.Knull(
                        left, mid, target_left, target_right, nulls_left, 2 * i + 1)
                    if left_result[0] == "F":
                        return left_result
                    nulls_left -= left_result[1]
                    right_result = self.Knull(
                        mid + 1, right, target_left, target_right, nulls_left, 2 * i + 2)
                    return right_result
                return ("NF", self.Tree[i][1])
            return ("NF", 0)
        elif right < target_left or target_right < left:
            return ("NF", 0)
        left_result = self.Knull(
            left, mid, target_left, target_right, nulls_left, 2 * i + 1)
        if left_result[0] == "F":
            return left_result
        nulls_left -= left_result[1]
        right_result = self.Knull(
            mid + 1, right, target_left, target_right, nulls_left, 2 * i + 2)
        if right_result[0] == "F":
            return right_result
        return ("NF", left_result[1] + right_result[1])


STree = SegmentTree()
# print(STree.Tree)
k = int(input())
for _ in range(k):
    request, *a = input().split()
    a = list(map(int, a))
    if request == 's':
        target_left = a[0]
        target_right = a[1]
        k = a[2]
        res = STree.Knull(0, STree.n - 1, target_left -
                          1, target_right - 1, k, 0)
        if res[0] == "F":
            print(res[1] + 1)
        else:
            print(-1)
    else:
        change_index = a[0]
        value = a[1]
        STree.update(change_index - 1, 0, STree.n - 1, value, 0)
        # print(STree.Tree)
