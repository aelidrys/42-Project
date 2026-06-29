import pandas as pd
import numpy as np
import pickle
from visualize import *
from gradient_descent import GradientDescent
from sklearn.preprocessing import MinMaxScaler
from sklearn.model_selection import train_test_split
import argparse
import sys


MODEL_FILE = "model.pkl"

def save_nodel():
    try:
        with open(MODEL_FILE, "wb") as model_file:
            pickle.dump({"model": model, "scaler_X": scaler_X}, model_file)

        print(f"Model saved to {MODEL_FILE}")
    except:
        print(f"Cannot save model to file: {MODEL_FILE}")
        sys.exit(1)


def load_data():
    try:
        data_file = "data.csv"
        data_csv = pd.read_csv(data_file)
        X = np.array(data_csv["km"]).reshape(-1,1)
        Y = np.array(data_csv["price"]).reshape(-1,1)
        return X, Y
    except:
        print(f"Cannot read from file: {data_file}")
        sys.exit(1)


if __name__ == "__main__":
    arg_parse = argparse.ArgumentParser(description="simple argparser")
    arg_parse.add_argument('--visualize', type=bool, default=False,
                        help=' add --visualize True to show the graph')

    args = arg_parse.parse_args()
    _visualize = args.visualize

    # Load dataset
    X, Y = load_data()

    # Train Val Split
    X_train, X_val, Y_train, Y_val = train_test_split(X,Y, test_size=0.2, random_state=88)

    # Scaling
    scaler_X = MinMaxScaler().fit(X_train)
    X_train = scaler_X.transform(X_train)
    X_val = scaler_X.transform(X_val)


    # Trianing with Gradient Descent
    model = GradientDescent(fit_intercept=True,lr=1, max_itr=10000)
    wights = model.fit(X_train, Y_train)

    # Save model and scaler
    save_nodel()

    # Visualize
    if _visualize:
        X_scl = scaler_X.transform(X)
        Y_pr = model.predict(X_scl)
        visualize(X,Y,Y_pr)





