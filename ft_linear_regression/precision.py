from sklearn.preprocessing import MinMaxScaler
from sklearn.model_selection import train_test_split
import pandas as pd
import numpy as np
import pickle
import sys


def load_model():
    try:
        with open("model.pkl", "rb") as model_file:
            data = pickle.load(model_file)
            model = data["model"]
            scaler_X = data["scaler_X"]
            return model, scaler_X
    except:
        print("Cannot load model statistics!")
        sys.exit(1)


def load_data():
    data_file = "data.csv"
    try:
        data_csv = pd.read_csv(data_file)
        X = np.array(data_csv["km"]).reshape(-1,1)
        Y = np.array(data_csv["price"]).reshape(-1,1)
        return X, Y
    except:
        print(f"Cannot read from file: {data_file}")
        sys.exit(1)


if __name__ == "__main__":
    # Load data set
    X, Y = load_data()

    # Split data to test and train sets
    X_train, X_test, Y_train, Y_test = train_test_split(X,Y, test_size=0.2, random_state=88)

    # Load model and scaler
    model, scaler_X = load_model()

    # Scale test set
    X_test = scaler_X.transform(X_test)

    # Test Performence
    Y_pr = model.predict(X_test)
    precision = model.score(X_test, Y_test)
    print(f"----------Precision------------")
    print(f"\tprecision: {precision:.2f}%")