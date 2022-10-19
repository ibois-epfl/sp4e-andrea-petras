#!/usr/bin/env python3

import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

from optimizer import quadratic_function
from optimizer import plot_3d_LGMRES
from optimizer import optimizator


# implement a generalized minimal residual method with einsum, independent of the matrix size and record each iteration
def GMRES(A: np.ndarray, b: np.ndarray, x0: np.ndarray, tol: float, max_iter: int, isPlotted: bool = True)-> np.ndarray:
    """
    generalized minimal residual method with einsum, independent of the matrix size and record each iteration

        :param A: np.ndarray The matrix A
        :param b: np.ndarray The vector b
        :param x0: np.ndarray The initial guess
        :param tol: float The tolerance
        :param max_iter: int The maximum number of iterations

        :return: np.ndarray The solution of the linear system
    """
    # clear out the global variables
    xk_list.clear()

    # append the initial guess
    xk_list.append(x0)

    # initialize the variables
    xk = x0
    vk = b - np.einsum('ij,j->i', A, xk)
    rk = b - np.einsum('ij,j->i', A, xk)
    res_list = [np.linalg.norm(rk)]
    i = 0

    while i < max_iter and res_list[i] > tol:
        # compute the residual
        res = np.linalg.norm(rk)

        # append the residual to the list
        res_list.append(res)

        # compute the new vector vk
        vk = b - np.einsum('ij,j->i', A, xk)

        # compute the new vector xk
        xk = xk + np.einsum('ij,j->i', np.linalg.inv(A), vk)

        # append the new vector xk to the list
        xk_list.append(xk)

        # compute the new vector rk
        rk = b - np.einsum('ij,j->i', A, xk)

        # increment the counter
        i += 1
    
    # plot it
    if isPlotted:
        plot_3d_LGMRES(xk_list)

    # return the solution
    return xk


def main()-> int:

    global xk_list

    xk_list = []

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

    return 0


if __name__ == "__main__":
    if main() != 0:
        sys.exit(1)