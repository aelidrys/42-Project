import numpy as np
import pickle
import sys


if __name__ == "__main__":
    # Load model and scaler
    try:
        with open("model.pkl", "rb") as model_file:
            data = pickle.load(model_file)
            model = data["model"]
            scaler_X = data["scaler_X"]
    except:
        print("Cannot load model statistics!")
        sys.exit(1)


    # Scale the input mileage
    try:
        mileage = input("enter the mileage: ")
        mlg_Features = np.array([int(mileage)]).reshape(-1,1)
        mlg_Features = scaler_X.transform(mlg_Features)
    except:
        print(f"Invalid input: {mileage}")
        sys.exit(1)

    # Predict the Price
    price = model.predict(mlg_Features)[0][0]
    print("price = ", f"{price:.5f}")

