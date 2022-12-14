#!/bin/env python3

import os
import sys
import argparse
import numpy as np


def readPositions(planet_name : str = "mercury",
                   directory : str = "trajectories") -> np.ndarray:
    """
        Function that reads the trajectory of a given planet and make a numpy array out of it.
    
        Parameters
        ----------
        planet_name : str
            Name of the planet.
        directory : str
            Directory where the file is located.
        
        Returns
        -------
        np.ndarray
            Numpy array with the trajectory of the planet. The numpy to be returned is a m 
            x n matrix with m = 365 and n = 3, the columns being the three components of the planet
            position.
    """
    
    # get all the files in the directory
    files = os.listdir(directory)

    # instatiate the numpy array
    positions_np = np.zeros((365, 3))
    np_count = 0

    for file in files:
        # open the file string stream
        with open(os.path.join(directory, file), "r") as f:
            # read the file and retain only the lines with the planet name
            line = [line for line in f.readlines() if planet_name in line]

            # get the position of the planet
            get_position = lambda line: np.array([float(x) for x in line.split()[1:4]])
            pos_np = np.array(get_position(line[0]))

            # append the position to the numpy array
            positions_np[np_count] = pos_np
            np_count += 1

    return positions_np

def computeError(positions : np.ndarray,
                 postiions_ref : np.ndarray) -> float:
    """
        Function that computes the error between the computed positions and the reference positions.

        Parameters
        ----------
        positions : np.ndarray
            Numpy array with the computed positions.
        postiions_ref : np.ndarray
            Numpy array with the reference positions.
        
        Returns
        -------
        float
            The error between the computed positions and the reference positions.
    """
    # compute the error
    error = 0
    for i in range(365):
        for j in range(3):
            error += (positions[i][j] - postiions_ref[i][j])**2
    error = np.sqrt(error)

    return error


def main(planet_name : str,
         directory : str,
         directory_ref : str) -> None:
    positions = readPositions(planet_name, directory)
    positions_ref = readPositions(planet_name, directory_ref)
    error = computeError(positions, positions_ref)
    print(f"The error between the computed positions and the reference positions is {error}.")


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='Compute error simulation')
    parser.add_argument('planet_name', type=str, default="mercury",
                        help='specify the planet name')
    parser.add_argument('directory', type=str, default="trajectories",
                        help='specify the directory where the file is located')
    parser.add_argument('directory_ref', type=str, default="build/dumps",
                        help='specify the directory where the reference file is located')
    
    args = parser.parse_args()
    _planet_name = args.planet_name
    _directory = args.directory
    _directory_ref = args.directory_ref

    if not os.path.exists(_directory):
        raise ValueError(f"The directory {_directory} does not exist.")
    if not os.path.exists(_directory_ref):
        print("Run first the main.py file to generate the directory build/dumps.")
        raise ValueError(f"The directory {_directory_ref} does not exist.")

    main(planet_name=_planet_name,
         directory=_directory,
         directory_ref=_directory_ref)