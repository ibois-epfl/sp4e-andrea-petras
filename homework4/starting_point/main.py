#!/bin/env python3

import sys
import argparse
from pypart import MaterialPointsFactory, ParticlesFactoryInterface
from pypart import PingPongBallsFactory, PlanetsFactory
from pypart import CsvWriter
from pypart import ComputeTemperature
from pypart import ComputeGravity
from pypart import ComputeVerletIntegration


def main(nsteps, freq, filename, particle_type, timestep):

    # print(pypart.__file__)

    if particle_type == "planet":
        PlanetsFactory.getInstance()
    elif particle_type == "ping_pong":
        PingPongBallsFactory.getInstance()
    elif particle_type == "material_point":
        MaterialPointsFactory.getInstance()
    else:
        print("Unknown particle type: ", particle_type)
        sys.exit(-1)

    factory = ParticlesFactoryInterface.getInstance()

    def createComputes(self, timestep):

        if particle_type == "planet":

            try:
                compute_grav = ComputeGravity()
                compute_verlet = ComputeVerletIntegration(timestep)

                G = 6.67384e-11  # m^3 * kg^-1 * s^-2
                UA = 149597870.700  # km
                earth_mass = 5.97219e24  # kg
                G /= (UA * 1e3)**3  # UA^3 * kg^-1 * s^-2
                G *= earth_mass    # UA^3 * earth_mass^-1 * s^-2
                G *= (60*60*24)**2  # UA^3 * earth_mass^-1 * day^-2

                compute_grav.setG(G)
                compute_verlet.addInteraction(compute_grav)
                self.system_evolution.addCompute(compute_verlet)

            except Exception as e:
                help(compute_grav)
                raise e

        elif particle_type == 'material_point':

            try:
                compute_temp = ComputeTemperature()
                compute_temp.conductivity = 1
                compute_temp.L = 2
                compute_temp.capacity = 1
                compute_temp.density = 1
                compute_temp.deltat = 1
                self.system_evolution.addCompute(compute_temp)
            except Exception as e:
                help(compute_temp)
                raise e

    evol = factory.createSimulation(filename, timestep, createComputes)

    dumper = CsvWriter("out.csv")
    dumper.write(evol.getSystem())

    evol.setNSteps(nsteps)
    evol.setDumpFreq(freq)
    evol.evolve()


if __name__ == "__main__":

    parser = argparse.ArgumentParser(description='Particles code')
    parser.add_argument('nsteps', type=int,
                        help='specify the number of steps to perform')
    parser.add_argument('freq', type=int,
                        help='specify the frequency for dumps')
    parser.add_argument('filename', type=str,
                        help='start/input filename')
    parser.add_argument('particle_type', type=str,
                        help='particle type')
    parser.add_argument('timestep', type=float,
                        help='timestep')

    args = parser.parse_args()
    nsteps = args.nsteps
    freq = args.freq
    filename = args.filename
    particle_type = args.particle_type
    timestep = args.timestep

    main(nsteps, freq, filename, particle_type, timestep)
