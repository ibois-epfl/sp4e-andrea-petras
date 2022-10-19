#!/usr/bin/env python3

from typing import Callable

import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D


def quadratic_function(x: float,
                        A: np.ndarray = np.array([[8, 1], [1, 3]]),
                        b: np.ndarray = np.array([2, 4]))-> float:
    """
    It returns the value of the quadratic function at x.
    By implementing the expression S(x) = (1/2)*(x^T)*A*x - (x^T)*b
    where A = [[8, 1], [1, 3]] and b = [2, 4] and A*x = b

        :param x: float The value of x in the quadratic function
        :param A: np.ndarray The matrix A
        :param b: np.ndarray The vector b

        :return: float The value of the quadratic function at x
    """
    # A*x
    A_x = [A[0][0] * x + A[0][1] * x, A[1][0] * x + A[1][1] * x]
    
    # (1/2)*(x^T)*A*x
    term1 = (1/2) * (x * A[0][0] * x + x * A[0][1] * x + x * A[1][0] * x + x * A[1][1] * x)
    
    # -(x^T)*b
    term2 = -(x * b[0] + x * b[1])

    # final expression for the quadratic function
    S = term1 + term2

    # return the value of the quadratic function at x
    return S

def plot_3d(iters: list, func: Callable = quadratic_function)-> None:
    """
    Plot the quadratic function with the minimum found by the optimizer BFGS and its iterations.

        :param iters: list The list of the iterations
        :param func: Callable functor of the quadratic function

        :return: None
    """
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

    # print all the points and lines for iterations
    # check for the shape of the list
    if isinstance(iters[0], float) or isinstance(iters[0], int):
        for i in range(len(iters)):
            ax.scatter(iters[i], iters[i], 2*quadratic_function(iters[i]), color='red')
        for i in range(len(iters)-1):
            ax.plot([iters[i], iters[i+1]], [iters[i], iters[i+1]], [2*quadratic_function(iters[i]), 2*quadratic_function(iters[i+1])], color='green')
    else:
        for i in range(len(iters)):
            ax.scatter(iters[i][0], iters[i][1], 2*quadratic_function(iters[i]), color='red')
        for i in range(len(iters)-1):
            ax.plot([iters[i][0], iters[i+1][0]], [iters[i][1], iters[i+1][1]], [2*quadratic_function(iters[i][0]), 2*quadratic_function(iters[i+1][0])], color='green')
    # show the plot
    plt.show()

def callback_storer(xk: np.ndarray)-> None:
    """
    Store the value of xk in the list xk_list
    
        :param xk: float The value of xk
    
        :return: None
    """
    xk_list.append(xk)

def optimizator(opt_type: str,
                x0:float = 10,
                A: np.ndarray = np.array([[8, 1], [1, 3]]),
                b: np.ndarray = np.array([2, 4]),
                func: Callable = quadratic_function,
                isPlotted: bool = True)-> float:
    """
    Find the minimum of the quadratic function.

        :param opt_type: str The type of the optimizer to use. It can be "BFGS" or "LGMRES"
        :param x0: float The initial guess
        :param func: Callable functor of the quadratic function
        :param A: np.ndarray The matrix A
        :param b: np.ndarray The vector b
        :param isPlotted: bool True if the the optimization process is plotted

        :return: float The minimum of the quadratic function
    """
    # # clear out the storer for iterations
    global xk_list
    xk_list = []
    xk_list.clear()

    if opt_type == "BFGS":
        from scipy.optimize import minimize

        # add the first guess
        xk_list.append(x0)

        # run minimizer BFGS
        res = minimize(func,
                        x0, 
                        method= 'BFGS', 
                        callback=callback_storer,
                        options={'disp': False})

    elif opt_type == "LGMRES":
        from scipy.sparse.linalg import lgmres
        from scipy.sparse import csc_matrix

        # parse matrix A for scipy
        A_csc = csc_matrix(A)

        # format initial guess
        x0 = np.array([x0, x0], dtype=float)
        xk_list.append(x0)

        # run the optimization
        res, info = lgmres(A_csc, b, x0, callback=callback_storer)

        # check for successful convergence
        if info > 0:
            raise Exception("The algorithm did not converge.")

    # plot it
    if isPlotted:
        plot_3d(iters=xk_list)

    else:
        raise ValueError("Invalid opt_type")

def main()-> int:

    # define the matrix A
    A_custom = np.array([[8, 3], [1, 3]])

    # define the vector b
    b_custom = np.array([2, 4])

    # define the initial guess
    x0t = 10.

    # define a custom functor
    functest = lambda x: quadratic_function(x, A=A_custom, b=b_custom)
    print(functest(1))

    # run the scipy optimizer
    optimizator(func=functest, A=A_custom, b=b_custom, opt_type="BFGS")

    optimizator(func=functest, A=A_custom, b=b_custom, opt_type="LGMRES")

    return 0;


if __name__ == "__main__":
    if main() != 0:
        sys.exit(1)