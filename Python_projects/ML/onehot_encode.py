import numpy as np


def onehot_encoding(x: np.array):
    n = np.size(x)
    x_uniq = np.sort(np.unique(x))
    m = np.size(x_uniq)
    new_array = np.zeros((n, m), int)
    for i in range(n):
        new_array[i, np.where(x_uniq == x[i])[0][0]] = 1

    return new_array

print(onehot_encoding(np.array([3,2,1,3,2,3])))