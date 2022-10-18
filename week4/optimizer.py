#!/usr/bin/env python3

from typing import Callable


def quadratic_function(x: float)-> float:
    """
    It returns the value of the quadratic function at x.
    By implementing the expression S(x) = (1/2)*(x^T)*A*x - (x^T)*b
    where A = [[8, 1], [1, 3]] and b = [2, 4] and A*x = b
    
        Parameters:
            x (float): The value of x in the quadratic function

        Returns:
            float: The value of the quadratic function at x
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


def optimizer(s: Callable)-> float:
    """
    It returns the optimized value of the quadratic function
    by implementing the gradient descent algorithm

        Parameters:
            s (Callable): The quadratic function

        Returns:
            float: The optimized value of the quadratic function
    """


    pass


def main()-> int:

    # quadratic_function(1)
    optimizer(quadratic_function(1))


    return 0;




if __name__ == "__main__":
    if main() != 0:
        sys.exit(1)