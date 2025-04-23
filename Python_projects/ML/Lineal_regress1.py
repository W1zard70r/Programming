import numpy as np

x =np.array([
    [2,0,2,2],
    [5,3,3,5],
    [0,3,1,2],
    [2,8,7,6],
    [7,1,3,2]
    ]
)
w = np.array([1, 1, -1, 1])
y = np.array([1,2,3,5,8])
w0 = -1

y_pred = w0 + x @ w
diff = y_pred - y
print(np.sum(diff**2))