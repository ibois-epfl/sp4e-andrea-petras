#!/bin/env python3

import os
import sys
import argparse
# import the main in the build directory
sys.path.append(os.path.join(os.path.dirname(__file__), "build"))
import main as m

# import error functions
from compute_error_simulation import readPositions, computeError

def runAndComputeError(scale : float,
                       planet_name : str,
                       input : str,
                       output_filename : str,
                       directory : str,
                       directory_ref : str,
                       nb_steps : int,
                       freq : int) -> float:
    """
        Function that runs the particle code and computes the error between the computed positions
        and the generated positions.

        Parameters
        ----------
        scale : float
            Scaling factor.
        planet_name : str
            Name of the planet.
        input : str
            Name of the input file.
        output_filename : str
            Name of the output file.
        nb_steps : int
            Number of steps.
        freq : int
            Frequency of the output.

        Returns
        -------
        float
            Error between the computed positions and the generated positions.
    """
    # generate the input file
    generateInput(scale, planet_name, input, output_filename)
    launchParticles(output_filename, nb_steps, freq)

    positions = readPositions(planet_name, directory)
    positions_ref = readPositions(planet_name, directory_ref)

    error = computeError(positions, positions_ref)

    return error

def generateInput(scale : float,
                  planet_name : str,
                  input_filename : str,
                  output_filename : str) -> None:
    """
        Function that generates an input file from a given input file but by scaling velocity of a 
        given planet.

        Parameters
        ----------
        scale : double
            Scaling factor.
        planet_name : str
            Name of the planet.
        input_filename : str
            Name of the input file.
        output_filename : str
            Name of the output file.
    """
    # open the input file
    with open(input_filename, "r") as f:
        # read the file
        lines = f.readlines()

        # get the line with the planet
        line = [line for line in lines if planet_name in line][0]

        # get the velocity of the planet
        get_velocity = lambda line: [float(x) for x in line.split()[4:7]]
        vel = get_velocity(line)

        # scale the velocity
        vel_scaled = [x*scale for x in vel]

        # replace the velocity in the line
        line = line.split()
        line[4:7] = vel_scaled
        line = " ".join([str(x) for x in line])

        # replace the line in the file
        lines = [line if planet_name in line else l for l in lines]

    # create file if it does not exist
    with open(output_filename, "w") as f:
        f.writelines(lines)

def launchParticles(input,
                    nb_steps : int,
                    freq : int) -> None:
    """
        Function that launches the particle code on an provided input file.

        Parameters
        ----------
        input : str
            Name of the input file.
        nb_steps : int
            Number of steps.
        freq : int
            Frequency of the output.
    """
    # launch the particle code from main.py
    m.main(nb_steps, freq, input, "planet", 1)


def main(scale : float,
         planet_name : str,
         input_filename : str,
         directory : str,
         directory_ref : str,
         output_filename : str) -> None:

    generateInput(scale, planet_name, input_filename, output_filename)
    launchParticles(output_filename, 365, 1)

    error = runAndComputeError(scale,
                               planet_name,
                               input_filename,
                               output_filename,
                               directory,
                               directory_ref,
                               365,
                               1)
    print("Error: {}".format(error))


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("scale", help="scaling factor", type=float)
    parser.add_argument("planet_name", help="name of the planet")
    parser.add_argument("input_filename", help="name of the input file")
    parser.add_argument("directory", help="name of the directory")
    parser.add_argument("directory_ref", help="name of the directory")
    parser.add_argument("output_filename", help="name of the output file")

    args = parser.parse_args()
    _scale = args.scale
    _planet_name = args.planet_name
    _input_filename = args.input_filename
    _directory = args.directory
    _directory_ref = args.directory_ref
    _output_filename = args.output_filename

    main(_scale,
         _planet_name,
         _input_filename,
         _directory,
         _directory_ref,
         _output_filename)

