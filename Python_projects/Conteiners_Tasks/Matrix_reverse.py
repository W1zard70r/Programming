def rotate(matrix: list[list[int]]) -> list[list[int]]:
    starts = [[0, j] for j in range(1, len(matrix))] + [[j, len(matrix) - 1] for j in range(1, len(matrix) - 1)]
    for i, j in starts:
        while (j > i):
            matrix[i][j], matrix[j][i] = matrix[j][i], matrix[i][j]
            j -= 1
            i += 1 

    for i in range(len(matrix)):
        matrix[i] = matrix[i][::-1]

    return matrix


matrix1 = [
[1, 2, 3],
[4, 5, 6],
[7, 8, 9]
]
matrix2 = [
[ 1,  2,  3,  4],
[ 5,  6,  7,  8],
[ 9, 10, 11, 12],
[13, 14, 15, 16]
]

print(*rotate(matrix2), sep = "\n")