#!/bin/env python3

import os
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


def main() -> None:
    positions = readPositions()


if __name__ == "__main__":
    main()