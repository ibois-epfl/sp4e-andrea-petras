import numpy as np
import matplotlib.pyplot as plt
import argparse
from mpl_toolkits.mplot3d import Axes3D
from matplotlib import cm

parser = argparse.ArgumentParser()
parser.add_argument("number", help="number of particles", type=int)
parser.add_argument("filename", help="name of generated input file")

args = parser.parse_args()
N = args.number
L = 2
x = np.linspace(-L/2, L/2, N+1)[:-1]
y = x.copy()

mesh = np.meshgrid(x, y)
positions = np.zeros((N, N, 3))
positions[:, :, 0] = mesh[1]
positions[:, :, 1] = mesh[0]

temperature = np.ones((N, N))
heat_source = np.zeros_like(temperature)

heat_source[int(N/4), :] = -N
heat_source[int(3*N/4), :] = N

plt.imshow(heat_source)

X = np.linspace(-1, 1, N)
X_2d = np.einsum('i,j->ij', np.ones(N), X)

fig = plt.figure()
ax = fig.gca(projection='3d')
surf = ax.plot_surface(
    X_2d, X_2d.T, heat_source.reshape((N, N)).real, cmap=cm.coolwarm,
    antialiased=False)

plt.show()


for i in range(0, N):
    for j in range(0, N):
        if positions[i, j, 0] <= -1/2:
            temperature[i, j] = -positions[i, j, 0] - 1.
        elif positions[i, j, 0] > 1/2:
            temperature[i, j] = -positions[i, j, 0]+1.
        else:
            temperature[i, j] = positions[i, j, 0]
 

# freqs = np.fft.fftfreq(N)*2*np.pi/L*N
# freqs_2d = np.einsum('i,j->ij', np.ones(N), freqs)
# freqs = freqs_2d**2 + freqs_2d.T**2
# freqs[0, 0] = 1.
# T_hat = np.fft.fft2(heat_source)/freqs
# T_hat[0, 0] = 0.
# temperature = np.fft.ifft2(T_hat)
# temperature = temperature.real

plt.imshow(temperature)

fig = plt.figure()
ax = fig.gca(projection='3d')
surf = ax.plot_surface(
    X_2d, X_2d.T, temperature.real, cmap=cm.coolwarm,
    antialiased=False)

plt.show()


temperature = temperature.reshape((N*N, 1))
heat_source = heat_source.reshape((N*N, 1))

temperature_rate = np.zeros_like(heat_source)
positions = positions.reshape((N*N, 3))
velocity = np.zeros_like(positions)
force = velocity.copy()
mass = np.ones((N*N, 1))

print(temperature.shape)
print(heat_source.shape)
print(positions.shape)
print(velocity.shape)
print(force.shape)
print(mass.shape)


headers = ["X", "Y", "Z",
           "velX", "velY", "velZ",
           "fX", "fY", "fZ",
           "mass",
           "temperature",
           "temperature_rate",
           "heat_source"]

file_data = np.hstack((positions, velocity, force, mass,
                       temperature, temperature_rate, heat_source))
np.savetxt(args.filename, file_data, delimiter=" ",
           header='#'+" ".join(headers), comments="")

