#!/usr/bin/env python3

import argparse
from typing import Callable

import numpy as np

from optimizer import optimizator
from optimizer import quadratic_function
from GMRES import custom_GMRES


def main(_o_type: str,
            _A: np.ndarray,
            _b: np.ndarray,
            _x: float,
            _tol: float,
            _max_iter: int,
            _plot: bool)-> int:

    # set the current quadratic function
    func_cmd = lambda x: quadratic_function(x, A=_A, b=_b)
    
    if _o_type == 'BFGS':
        optimizator(opt_type="BFGS",
                    x0=_x,
                    A=_A,
                    b=_b,
                    func=func_cmd,
                    isPlotted=_plot)
    elif _o_type == 'LGMRES':
        optimizator(opt_type="LGMRES",
                    x0=_x,
                    A=_A,
                    b=_b,
                    func=func_cmd,
                    isPlotted=_plot)
    elif _o_type == 'GMRES':
        custom_GMRES(A=_A,
                    b=_b,
                    x0=_x,
                    tol=_tol,
                    max_iter=_max_iter,
                    isPlotted=_plot)
    return 0


if __name__ == "__main__":
    parser = argparse.ArgumentParser()

    # add parser for what type of optimization to run
    parser.add_argument("--opt_type",
                        type=str,
                        choices=["BFGS", "LGMRES", "GMRES"],
                        default="BFGS")
    
    parser.add_argument('-nrows',
                        action='store',
                        type=int,
                        default=2,
                        help="Number of rows for the matrix")
    parser.add_argument("-A", "--matrix",
                        type=int,
                        action="store",
                        nargs="+",
                        default= "8 1 1 3",
                        help="The matrix A")
    parser.add_argument("-b", "--vector",
                        type=int,
                        action="store",
                        nargs="+",
                        default= "2 4",
                        help="The vector b")

    parser.add_argument('-x', '--initial_guess',
                        type=float,
                        nargs='+',
                        default=10.,
                        help='the initial guess')
    
    parser.add_argument('-t', '--tolerance',
                        type=float,
                        default=1e-6,
                        help='the tolerance')
    parser.add_argument('-m', '--max_iter',
                        type=int,
                        default=100,
                        help='the maximum number of iterations')
    
    parser.add_argument('-p', '--plot',
                        type=bool,
                        default=True,
                        help='whether to plot the result or not')
   
    args = parser.parse_args()

    o_type = args.opt_type

    global xk_list
    xk_list = []

    global A, b
    A = np.array(args.matrix).reshape((args.nrows, len(args.matrix)//args.nrows))
    b = np.array(args.matrix)
    x = float(args.initial_guess)

    tol = args.tolerance
    max_iter = args.max_iter
    plot = args.plot

    if main(_o_type=o_type, _A=A, _b=b, _x=x, _tol=tol, _max_iter=max_iter, _plot=plot) != 0:
        sys.exit(1)