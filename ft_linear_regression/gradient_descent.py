import numpy as np
from numpy.linalg import norm


class GradientDescent():
    __wights = np.array([[0,0],[0,0]])
    
    def __init__(self, fit_intercept=False, lr=0.1, pr=1e-9, max_itr=10000, W1=None):
        self.fit_intercept = fit_intercept
        self.lr = lr
        self.pr = pr
        self.max_itr = max_itr
        self.W1 = W1
    
    def predict(self, X):
        if self.__wights is None:
            raise ValueError("Model has not been fitted yet!")
        if self.fit_intercept:
            X = np.hstack([np.ones((X.shape[0],1)),X])
        return np.dot(X,self.__wights)
    
    def cost_f(self, X, Y, W):
        # X input
        # Y output/target
        # W weights
        # X.shape[0] number of exampels
        exampels = X.shape[0]
        pred = np.dot(X, W)
        error = pred - Y
        cost = error.T.dot(error) / 2 * exampels
        return cost[0][0]

    def f_derive(self, X, Y, W):
        n = X.shape[0]
        pred = np.dot(X, W)
        error = pred - Y
        gr = X.T @ error / n # X.T.dot(error) / exampels
        return gr


    def fit(self, X, Y):
        if self.fit_intercept:
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
    
    def score(self, X, Y):
        # R^2 score
        
        y_pr = self.predict(X)
        u = np.sum((Y - y_pr) ** 2)
        v = np.sum((Y - np.mean(Y)) ** 2)
        return 1 - u / v

