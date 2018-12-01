from __future__ import print_function

training_data = [
    ['Green', 458835, 'Lamborghini'],
    ['Yellow', 458835, 'Lamborghini'],
    ['Red', 382210, 'Jet'],
    ['Red', 382210, 'Jet'],
    ['Yellow', 458835, 'Toyota'],
]

# column labels-> print the tree.
header = ["color", "price", "label"]

#send (training_data,0)
#find the unique values for a column in a dataset
def unique_vals(rows, col):
    return set([row[col] for row in rows])

#send (training_data)
#the number of each type of example in a dataset
def class_counts(rows):
    counts = {}  # a dictionary of label -> count.
    for row in rows:
        # in our dataset format, the label is always the last column
        label = row[-1]
        if label not in counts:
            counts[label] = 0
        counts[label] += 1
    return counts

def is_numeric(value):
    return isinstance(value, int) or isinstance(value, float)

#used to partition a dataset  
#This class just records a 'column number' (e.g., 0 for Color) and a
#'column value' (e.g., label). The 'match' method is used to compare
class Question:
    def __init__(self, column, value):
        self.column = column
        self.value = value

    def match(self, example):
        val = example[self.column]
        if is_numeric(val):
            return val >= self.value
        else:
            return val == self.value

    def __repr__(self):
        condition = "=="
        if is_numeric(self.value):
            condition = ">="
        return "Is %s %s %s?" % (
            header[self.column], condition, str(self.value))

#Partitions a dataset
#For each row in the dataset, check if it matches the question. If
#so, add it to 'true rows', otherwise, add it to 'false rows'
def partition(rows, question):
    true_rows, false_rows = [], []
    for row in rows:
        if question.match(row):
            true_rows.append(row)
        else:
            false_rows.append(row)
    return true_rows, false_rows

#Calculate -> uncertainy of our training data
def gini(rows):
    counts = class_counts(rows)
    impurity = 1
    for lbl in counts:
        prob_of_lbl = counts[lbl] / float(len(rows))
        impurity -= prob_of_lbl**2
    return impurity

#information gain
def info_gain(left, right, current_uncertainty):
    p = float(len(left)) / (len(left) + len(right))
    return current_uncertainty - p * gini(left) - (1 - p) * gini(right)

#Find the best question to ask by iterating over every feature / value
#and calculating the information gain.	
def find_best_split(rows):
    best_gain = 0  # keep track of the best information gain
    best_question = None  # keep train of the feature / value that produced it
    current_uncertainty = gini(rows)
    n_features = len(rows[0]) - 1  # number of columns

    for col in range(n_features):
        values = set([row[col] for row in rows])  # unique values in the column
        for val in values: 
            question = Question(col, val)
            true_rows, false_rows = partition(rows, question)
            if len(true_rows) == 0 or len(false_rows) == 0:
                continue
            gain = info_gain(true_rows, false_rows, current_uncertainty)
            if gain >= best_gain:
                best_gain, best_question = gain, question

    return best_gain, best_question

#A Leaf node classifies data.	
class Leaf:
    def __init__(self, rows):
        self.predictions = class_counts(rows)

#This holds a reference to the question, and to the two child nodes		
class Decision_Node:
    def __init__(self,
                 question,
                 true_branch,
                 false_branch):
        self.question = question
        self.true_branch = true_branch
        self.false_branch = false_branch
	
def build_tree(rows):
    gain, question = find_best_split(rows)
    if gain == 0:
        return Leaf(rows)
    true_rows, false_rows = partition(rows, question)
    true_branch = build_tree(true_rows)
    false_branch = build_tree(false_rows)
    return Decision_Node(question, true_branch, false_branch)

	
def print_tree(node, spacing=""):
    # Base case: we've reached a leaf
    if isinstance(node, Leaf):
        print (spacing + "Predict", node.predictions)
        return
		
    print (spacing + str(node.question))

    print (spacing + '--> True:')
    print_tree(node.true_branch, spacing + "  ")

    print (spacing + '--> False:')
    print_tree(node.false_branch, spacing + "  ")

my_tree = build_tree(training_data)
print_tree(my_tree)

def classify(row, node):
    # Base case: we've reached a leaf
    if isinstance(node, Leaf):
        return node.predictions

    # Compare the feature / value stored in the node,
    if node.question.match(row):
        return classify(row, node.true_branch)
    else:
        return classify(row, node.false_branch)
		
def print_leaf(counts):
    total = sum(counts.values()) * 1.0
    probs = {}
    for lbl in counts.keys():
        probs[lbl] = str(int(counts[lbl] / total * 100)) + "%"
    return probs
	
# Evaluate
testing_data = [
    ['Green', 458835, 'Lamborghini'],
    ['Yellow', 458835, 'Lamborghini'],
    ['Red', 382210, 'Jet'],
    ['Red', 382210, 'Jet'],
    ['Yellow', 458835, 'Toyota'],
]
for row in testing_data:
    print ("Actual: %s. Predicted: %s" %
           (row[-1], print_leaf(classify(row, my_tree))))