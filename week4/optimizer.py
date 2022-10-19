#!/usr/bin/env python3

from typing import Callable

import numpy as np


def plot_3d_quadratic_function()-> None:
    """
    Plot the quadratic function with the minimum found by the optimizer and its iterations.

        :return: None
    """
    import matplotlib.pyplot as plt
    from mpl_toolkits.mplot3d import Axes3D

    # create the grid
    X = np.arange(-10, 10, 0.25)
    Y = np.arange(-10, 10, 0.25)
    X, Y = np.meshgrid(X, Y)
    Z = quadratic_function(X) + quadratic_function(Y)

    # create the figure as transparent and in axonometric view
    fig = plt.figure(figsize=(5, 5), dpi=100, facecolor='w', edgecolor='k')

    # add a transparent add_subplot
    ax = fig.add_subplot(111, projection='3d')
    ax.plot_surface(X, Y, Z, color="blue", edgecolor='none', alpha=.4)
    ax.view_init(30, -45)
    ax.set_xlabel('x')
    ax.set_ylabel('y')
    ax.set_zlabel('z')

    # print all the points in xk_list
    for i in range(len(xk_list)):
        ax.scatter(xk_list[i], xk_list[i], 2*quadratic_function(xk_list[i]), color='red')

    # add lines between the points
    for i in range(len(xk_list)-1):
        ax.plot([xk_list[i], xk_list[i+1]], [xk_list[i], xk_list[i+1]], [2*quadratic_function(xk_list[i]), 2*quadratic_function(xk_list[i+1])], color='green')

    # show the plot
    plt.show()

def quadratic_function(x: float)-> float:
    """
    It returns the value of the quadratic function at x.
    By implementing the expression S(x) = (1/2)*(x^T)*A*x - (x^T)*b
    where A = [[8, 1], [1, 3]] and b = [2, 4] and A*x = b

        :param x: float The value of x in the quadratic function

        :return: float The value of the quadratic function at x
    """
    A = [[8, 1], [1, 3]]
    b = [2, 4]
    
    # A*x
    A_x = [A[0][0] * x + A[0][1] * x, A[1][0] * x + A[1][1] * x]
    
    # (1/2)*(x^T)*A*x
    term1 = (1/2) * (x * A[0][0] * x + x * A[0][1] * x + x * A[1][0] * x + x * A[1][1] * x)
    
    # -(x^T)*b
    term2 = -(x * b[0] + x * b[1])

    # final expression for the quadratic function
    S = term1 + term2

    return S

def callback_storer(xk: float)-> None:
    """
    Store the value of xk in the list xk_list
    
        :param xk: float The value of xk
    
        :return: None
        """
    xk_list.append(xk)

def optimizer_bfgs(s: Callable, isPlotted: bool)-> float:
    """
    Find the minimum of the quadratic function using the scipy.optimize.minimize function

        :param s: Callable functor of the  quadratic function
        :param isPlotted: bool True if the the optimization process is plotted

        :return: float The minimum of the quadratic function
    """"
    from scipy.optimize import minimize
    from scipy.sparse.linalg import lgmres

    # first guess
    x0 = 10

    # clear out the storer for iterations
    xk_list.clear()

    # run otpimization
    res = minimize(s, 
                   x0, 
                   method= 'BFGS', 
                   callback=callback_storer,
                   options={'disp': False})

    # plot the gradient descent
    print(f"Stored iterations mid-results: {len(xk_list)}")
    print(f"Stored iterations: {xk_list}")

    # print results
    print(f"first {xk_list[0]}, second {res.fun}")
    print(f"test opti {quadratic_function(xk_list[0])}")

    # plot the solution
    plot_3d_quadratic_function()

def main()-> int:

    global xk_list
    xk_list = []

    # exercice 1.a
    optimizer_bfgs(quadratic_function, True)

    return 0;


if __name__ == "__main__":
    if main() != 0:
        sys.exit(1)