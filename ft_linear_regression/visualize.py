import matplotlib.pyplot as plt


def visualize(X, Y, Y_pr, color='red', label='line'):
    plt.figure(figsize=(10,6))
    plt.plot(X,Y_pr, label=label,color=color)
    plt.scatter(X,Y)
    plt.title('MSE')
    plt.xlabel("mileage")
    plt.ylabel("price")
    plt.legend()
    plt.show()
