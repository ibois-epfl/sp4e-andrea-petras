#!/bin/env python3

import os
import numpy as np


def readPosistions(planet_name : str = "mercury",
                   directory : str = "trajectory") -> np.ndarray:
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
            Numpy array with the trajectory of the planet. The numpy to be returned should be a m 
            x n matrix with m = 365 and n = 3, the columns being the three components of the planet
            position.
    """
    
    # read the trajectory of the planet "mercury" in the files of trajectory directory
    # and return a numpy array with the trajectory of the planet
    
    



def main() -> None:
    """Main function."""





if __name__ == "__main__":
    main()