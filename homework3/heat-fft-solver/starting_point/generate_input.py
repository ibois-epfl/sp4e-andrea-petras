import numpy as np

import argparse

parser = argparse.ArgumentParser()
parser.add_argument("number", help="number of particles", type=int)
parser.add_argument("filename", help="name of generated input file")

args = parser.parse_args()

positions = np.random.random((args.number, 3))
velocity = np.zeros((args.number, 3))
force = velocity.copy()
masses = 1e9*(np.random.random((args.number, 1)) + 1)

file_data = np.hstack((positions, velocity, force, masses))
np.savetxt(args.filename, file_data, delimiter=" ")
