import pandas as pd
from sklearn.tree import DecisionTreeClassifier
import os

# File paths
TRAIN_FILE = "data/training_data.csv"
INPUT_FILE = "data/process_input.csv"
OUTPUT_FILE = "data/ai_choice.txt"

def load_training_data():
if not os.path.exists(TRAIN_FILE):
print("Training data not found.")
exit(1)

df = pd.read_csv(TRAIN_FILE)
return df

def train_model(df):
X = df[["n_process", "avg_bt", "std_bt"]]
y = df["best_algorithm"]

model = DecisionTreeClassifier()
model.fit(X, y)

return model

def load_input():
if not os.path.exists(INPUT_FILE):
print("Input file not found.")
exit(1)

df = pd.read_csv(INPUT_FILE)
return df.iloc[0] # take first row

def predict(model, input_row):
X_test = [[
input_row["n_process"],
input_row["avg_bt"],
input_row["std_bt"]
]]

prediction = model.predict(X_test)
return prediction[0]

def save_output(algo):
with open(OUTPUT_FILE, "w") as f:
f.write(algo)

def main():
df = load_training_data()
model = train_model(df)
input_row = load_input()
best_algo = predict(model, input_row)
save_output(best_algo)

print(f"Predicted Best Algorithm: {best_algo}")

if __name__ == "__main__":
main()
