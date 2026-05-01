import pandas as pd
from sklearn.tree import DecisionTreeClassifier
import os

TRAIN_FILE = "data/training_data.csv"
INPUT_FILE = "data/process_input.csv"
OUTPUT_FILE = "data/ai_choice.txt"

def load_training_data():
    if not os.path.exists(TRAIN_FILE):
        print("Training data not found.")
        exit(1)

    return pd.read_csv(TRAIN_FILE)

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
    return df.iloc[0]

def predict(model, input_row):
    X_test = pd.DataFrame([{
    "n_process": input_row["n_process"],
    "avg_bt": input_row["avg_bt"],
    "std_bt": input_row["std_bt"]
}])

    prediction = model.predict(X_test)[0]

    probs = model.predict_proba(X_test)[0]
    confidence = max(probs)

    return prediction, confidence

def save_output(algo, confidence):
    with open(OUTPUT_FILE, "w") as f:
        f.write(f"{algo} {confidence:.2f}")

def main():
    df = load_training_data()
    model = train_model(df)
    input_row = load_input()

    prediction, confidence = predict(model, input_row)

    save_output(prediction, confidence)

    print(f"Prediction: {prediction}")
    print(f"Confidence: {confidence:.2f}")
    print(f"Predicted Best Algorithm: {prediction}")

if __name__ == "__main__":
    main()