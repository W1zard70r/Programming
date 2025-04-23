import numpy as np

x =np.array([
    [1,1,9,6,3],
    [1,3,1,9,6],
    [1,6,3,1,9],
    [1,9,6,3,1],
    [1,1,0,1,0]
    ]
)
y = np.array([2,1,3,-1,1])
w = np.linalg.inv(x.T @ x + np.eye(5,5)) @ x.T @ y
print(np.round(w, 2))