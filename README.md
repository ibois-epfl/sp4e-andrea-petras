# Exercice 11
///

---
## Exercice 1

<!-- ### In MaterialPoint class:
Particle is the parent of this class. This class add extra properties and related getters.
<p align="center"> <img src="./homework3/heat-fft-solver/starting_point/img/Screenshot from 2022-12-08 15-53-31.png" height="300"> </p>

### Matrix class:
This is a only header class regrouping all utility structs and methods for matrix calculations. Given that this structs implement all templates, particles can also be stored inside.

### MaterialPointsFactory:
The MaterialPointsFactory is in charge of creating  -->

`MaterialPoint` is a child of the `Particle` with two extra properties and getters. The `MaterialPointFactory` inherits from the interface `ParticleFactoryInterface`. It is implemented as a singleton pattern so that by calling the `ParticlesFactoryInterface::getInstance().creatParticle()` we can create particles when we parse file. `MaterialPointFactory` has another important function for the particles which is `CreateSimulat`ion(..) it creates the `SystemEvolution` that contains `System` which this last one contains all the particle objects.

`FFT` uses the matrices structs contained in `matrix.hh` for calculations.


---
## Exercice 2
### Configure and run
To configure and build the code:
```bash
$ cd sp4e-andrea-petras/homework3/heat-fft-solver/starting_point
$ mkdir build
$ cmake -S . -B build -DFFTW_MODULE=ON && make -C build
```
To run the code:
```bash
'/sp4e-andrea-petras/homework3/heat-fft-solver/starting_point/build/test_fft'
```

The result of `ldd <your-executable>`:
```bash

```
### Results
for `ldd` (printing shared libraries dependencies):
```bash
(base) as@as-Legion-7-16ACHg6:~/sp4e-andrea-petras/homework3/heat-fft-solver/starting_point$ ldd '/home/as/sp4e-andrea-petras/homework3/heat-fft-solver/starting_point/build/test_fft'
        linux-vdso.so.1 (0x00007ffdcb78e000)
        libstdc++.so.6 => /lib/x86_64-linux-gnu/libstdc++.so.6 (0x00007f7992db3000)
        libm.so.6 => /lib/x86_64-linux-gnu/libm.so.6 (0x00007f7992ccc000)
        libgcc_s.so.1 => /lib/x86_64-linux-gnu/libgcc_s.so.1 (0x00007f7992cac000)
        libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007f7992a84000)
        /lib64/ld-linux-x86-64.so.2 (0x00007f7993114000)
```

The test is running without problems but we cannot see the shared library in the output of `ldd`. *We cannot figure out why*.

---
## Exercice 3