import pandas as pd
import numpy as np
from sklearn.metrics import accuracy_score
from sklearn.model_selection import train_test_split
from sklearn.neighbors import KNeighborsClassifier


dataset = pd.read_csv('penguins.csv')
dataset = dataset.dropna() 

labels = dataset['species']
features = dataset[['bill_length_mm', 'bill_depth_mm']] 

train_features, test_features, train_labels, test_labels = train_test_split(
    features, labels, test_size=0.2, random_state=123
)

all_accuracy = []

for k in range(1, 11):  
    for weight in ["uniform", "distance"]: 
        knn = KNeighborsClassifier(n_neighbors=k, weights=weight)
        knn.fit(train_features, train_labels)

        pred_labels = knn.predict(test_features)

        model_accuracy = accuracy_score(test_labels, pred_labels)

        all_accuracy.append(model_accuracy)

print('Best accuracy: {:.6f}'.format(max(all_accuracy)))  
print('Worst accuracy: {:.6f}'.format(min(all_accuracy)))  
