# Load libraries
import pandas as pd
from sklearn.tree import DecisionTreeClassifier # Import Decision Tree Classifier
from sklearn.model_selection import train_test_split # Import train_test_split function
from sklearn import metrics #Import scikit-learn metrics module for accuracy calculation
from sklearn import tree
import matplotlib.pyplot as plt

col_names = ['buying', 'maint', 'doors', 'persons', 'lug_boot', 'safety', 'outcome']
# load dataset
pima = pd.read_csv("car_data.csv", header=None, names=col_names)


#split dataset in features and target variable
feature_cols = ['buying', 'maint', 'doors', 'persons', 'lug_boot', 'safety']
X = pima[feature_cols] # Features
y = pima['outcome']# Target variable

# Split dataset into training set and test set
X_train, X_test, y_train, y_test = train_test_split(X, y, train_size=0.8, test_size=0.2, random_state=1) # 70% training and 30% test

# Create Decision Tree classifer object
clf = DecisionTreeClassifier(criterion="entropy", max_depth=6)

# Train Decision Tree Classifer
clf = clf.fit(X_train,y_train)

#Predict the response for test dataset
y_pred = clf.predict(X_test)


# Model Accuracy, how often is the classifier correct?
print("Accuracy:",metrics.accuracy_score(y_test, y_pred) * 100.0)
fig = plt.figure(figsize=(30,18))
tree.plot_tree(clf)
fig.savefig("decistion_tree.png")




