import numpy as np


def minmax_scale(X: np.array):
    if np.all(X.max(axis=0) == X.min(axis=0)):
        return (X - X.min(axis=0)).astype(float)
    X_std = (X - X.min(axis=0)) / (X.max(axis=0) - X.min(axis=0))
    return X_std
