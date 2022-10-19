#!/usr/bin/env python3

import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

from optimizer import quadratic_function
from optimizer import optimizator


def plot_3d()-> None:
    """
    Plot the quadratic function with the minimum found by the optimizer GMRES and its iterations.

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

    # print all the points in xk_list
    for i in range(len(xk_list)):
        ax.scatter(xk_list[i][0], xk_list[i][1], 2*quadratic_function(xk_list[i]), color='red')

    # draw the lines between the points
    for i in range(len(xk_list)-1):
        ax.plot([xk_list[i][0], xk_list[i+1][0]], [xk_list[i][1], xk_list[i+1][1]], [2*quadratic_function(xk_list[i][0]), 2*quadratic_function(xk_list[i+1][0])], color='green')

    # show the plot
    plt.show()


# implement a generalized minimal residual method with einsum, independent of the matrix size and record each iteration
def GMRES(A: np.ndarray, b: np.ndarray, x0: np.ndarray, tol: float, max_iter: int)-> np.ndarray:
    """
    generalized minimal residual method with einsum, independent of the matrix size and record each iteration

        :param A: np.ndarray The matrix A
        :param b: np.ndarray The vector b
        :param x0: np.ndarray The initial guess
        :param tol: float The tolerance
        :param max_iter: int The maximum number of iterations

        :return: np.ndarray The solution of the linear system
    """
    # append the initial guess
    xk_list.append(x0)

    # initialize the variables
    xk = x0
    vk = b - np.einsum('ij,j->i', A, xk)
    rk = b - np.einsum('ij,j->i', A, xk)
    # rk_list = [rk]
    # xk_list = [xk]
    # vk_list = [vk]
    res_list = [np.linalg.norm(rk)]
    i = 0

    while i < max_iter and res_list[i] > tol:
        # compute the residual
        res = np.linalg.norm(rk)

        # append the residual to the list
        res_list.append(res)

        # compute the new vector vk
        vk = b - np.einsum('ij,j->i', A, xk)

        # append the new vector vk to the list
        vk_list.append(vk)

        # compute the new vector xk
        xk = xk + np.einsum('ij,j->i', np.linalg.inv(A), vk)

        # append the new vector xk to the list
        xk_list.append(xk)

        # compute the new vector rk
        rk = b - np.einsum('ij,j->i', A, xk)

        # append the new vector rk to the list
        rk_list.append(rk)

        # increment the counter
        i += 1

    # return the solution
    print("The solution is: ", xk)
    return xk


def main()-> int:

    global res_list, rk_list, xk_list, vk_list

    res_list = []
    rk_list = []
    xk_list = []
    vk_list = []

    # define the matrix A
    A = np.array([[8, 1], [1, 3]])

    # define the vector b
    b = np.array([2, 4])

    # define the initial guess
    x0 = np.array([10, 10])

    # define the tolerance
    tol = 1e-6

    # define the maximum number of iterations
    max_iter = 100

    # call the GMRES function
    GMRES(A, b, x0, tol, max_iter)
    plot_3d()


    return 0


if __name__ == "__main__":
    if main() != 0:
        sys.exit(1)