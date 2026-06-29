<h1>ft_linear_regression</h1>

<h3>ft_linear_regression is one of the project of 42-network here the <a href='https://cdn.intra.42.fr/pdf/pdf/102546/en.subject.pdf'>Subject</a></h3>

<h3>The aim of this project is to introduce you to the basic concept behind machine learning.
For this project, you will have to create a program that predicts the price of a car by
using a linear function train with a gradient descent algorithm.</h3>

---

<h1>Project Overview</h1>

<h2>Data</h2>

### Sample from `data.csv`

| km     | price |
|--------|-------|
| 240000 | 3650  |
| 139800 | 3800  |
| 150500 | 4400  |
| 185530 | 4450  |
| 176000 | 5250  |
| 114800 | 5350  |
| 166800 | 5800  |
| 89000  | 5990  |
| 144500 | 5999  |
| 84000  | 6200  |

#### The column `km` represents the kilometers driven by the car.  
#### The column `price` is the selling price of the car.

#### The goal is to create a linear regression model that takes `km` as input and predicts the `price` for a new example. 

<h2>Code Steps</h2>

- ### Data Preprocessing

  - #### load data from csv file
    ```python
    import pandas as pd

    file_name = "data.csv"
    data_csv = pd.read_csv(file_name)
    ```
  - #### Split the data into input X and output or target Y
    ```python
    import numpy as np

     X = np.array(data_csv["km"]).reshape(-1,1)
     Y = np.array(data_csv["price"]).reshape(-1,1)
    ```
  - #### Split the input X and the target Y to training and validation sets
    ```python
    from sklearn.model_selection import train_test_split


    # Train Val Split
    X_train, X_val, Y_train, Y_val = train_test_split(X,Y, test_size=0.2, random_state=88)

    ```
    - <h5>using 80% of data for training and keep 20% for testing</h5>
    - <h5>We fix the `random_state` to 88 to ensure reproducibility. It controls how the data is shuffled before splitting.</h5>


  - #### Scaling data by using MinMaxScaler method that transform data to a range between 0 and 1
    ```python
    from sklearn.preprocessing import MinMaxScaler
    
    # Scaling
    scaler_X = MinMaxScaler().fit(X_train)
    X_train = scaler_X.transform(X_train)
    X_val = scaler_X.transform(X_val)
    ```
    this step help learning rate to control the jumps of gradient descent also avoid large numbers

---

- ### Trianing with <a href=''>Gradient Descent</a> algorithm</h4>
  - #### Create Gadient Descent Model
    - ##### to discover theore behind gradient descent check this [Document](../README.md)
    - #### create a class GradientDescent and init its varibels 
      ```python
      class GradientDescent(BaseEstimator, RegressorMixin):
        def __init__(self, fit_intercept=False, lr=0.1, pr=1e-9, max_itr=10000, W1=None):
          self.fit_intercept = fit_intercept # add column of ones to input X or not
          self.lr = lr # learning rate
          self.pr = pr # presission
          self.max_itr = max_itr # max iterations
          self.W1 = W1 # weights
      ```
      ##### weights in this case is a matrix of n row and two column m and c in real word we have many features so we have `m1, m2, m3, ...` not just `m, c`
    - #### create a cost function (also known as error  or loss function) defined by `error = 1/2n Σ((m*x+c)-y_r)^2` To implement this in Python, we use the numpy library, which provides efficient matrix operations.
      ```python
      def cost_f(self, X, Y, W):
          # X input
          # Y output/target
          # W weights
          exampels = X.shape[0] # number of exampels
          pred = np.dot(X, W) # predicted target
          error = pred - Y
          cost = error.T.dot(error) / 2 * exampels
          return cost[0][0]

      ```
    - #### create derivative of cost function `d(error)/dm = 1/n Σ((m*x+c)-y_r)*x`
      ```python
      def f_derive(self, X, Y, W):
        n = X.shape[0] # number of exampels
        pred = np.dot(X, W) # predicted target
        error = pred - Y
        gr = X.T @ error / n # final derivative
        return gr
      ```
    - #### Start training iterations until the derivative of cost function equal or close to zero or reach the max_itr
      ```python
      def fit(self, X, Y):
        if self.fit_intercept: 
          # add columnof ones to the left side of matrix X
            X = np.hstack([np.ones((X.shape[0],1)),X])
        if self.W1 is None:
            self.W1 = np.random.rand(X.shape[1],1)
        cur_p = self.W1
        last_p = cur_p + 100

        iter = 0
        while norm(cur_p - last_p) > self.pr and iter < self.max_itr:
            last_p = cur_p.copy()
            gr = self.f_derive(X, Y, cur_p)
            cur_p -= gr * self.lr
            iter += 1
        self.__wights = cur_p.copy()
        return cur_p
      ```
      ##### in each itr copy the current weights `cur_p` in `last_p`, then update it and check if the difference between `last_p` and `cur_p` is still great than presission and `itr < max_itr`, if this condition no mush valid stop and return the learning weights `cur_p`

      ##### Why do we need to add a column of ones to the input X?
      ##### In the linear equation y = m * x + c, we can rewrite this as y = m * x + 1 * c to treat both m and c as weights.
      ##### To express this using matrix multiplication, we represent the weights as a vector W = [c, m], and the input as X = [1, x].

      ##### So the equation becomes:
        ```r
        y = W · X^T = [c, m] · [1, x]^T
        ```
      ##### To make this multiplication valid for all data points, we add a column of ones to the input matrix X. This allows us to include the intercept c (also called bias) as part of the weights vector, simplifying implementation.
      
    - #### add predict function
      ```python
      def predict(self, X):
        if self.__wights is None:
            raise ValueError("Model has not been fitted yet!")
        if self.fit_intercept:
            X = np.hstack([np.ones((X.shape[0],1)),X])
        return np.dot(X,self.__wights)
      ```
    - #### add a function to calculate the performence/score
      ```python
      def score(self, X, Y):
        # R^2 score
        
        y_pr = self.predict(X)
        u = np.sum((Y - y_pr) ** 2)
        v = np.sum((Y - np.mean(Y)) ** 2)
        return 1 - u / v
      ```
---
- ### Visualizing to see if our model undestand the data or not</h4>

  - #### use matplotlib.pyplot library to show the actual points and our model prediction</h5>


---
- ### Save the wights and Scaler in a file.pkl to predict the price of a car for a new given mileage</h4>

