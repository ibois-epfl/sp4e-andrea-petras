# Exercice 11
///

---
## Exercice 1

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
## Exercice 4.1-4
### Configure and run
To run the testing for the temperature compute:
```bash
$ cd sp4e-andrea-petras/homework3/heat-fft-solver/starting_point
$ cmake -S . -B build -DFFTW_MODULE=ON && make -C build && './build/test_temp'
```
### Results
All tests are running but only 2 out of 3 tests are passing:
```bash
[==========] Running 3 tests from 1 test suite.
[----------] Global test environment set-up.
[----------] 3 tests from TempTest
[ RUN      ] TempTest.constant
[       OK ] TempTest.constant (2418 ms)
[ RUN      ] TempTest.sinusoidal
/home/as/sp4e-andrea-petras/homework3/heat-fft-solver/starting_point/test_temp.cc:103: Failure
The difference between T and gtT is 3.8877003419868217e-06, which exceeds 1e-10, where
T evaluates to -0.013966068039487399,
gtT evaluates to -0.013962180339145413, and
1e-10 evaluates to 1e-10.
[  FAILED  ] TempTest.sinusoidal (69 ms)
[ RUN      ] TempTest.volumetric
/home/as/sp4e-andrea-petras/homework3/heat-fft-solver/starting_point/test_temp.cc:149: Failure
The difference between T and gtT is 0.13781127137954657, which exceeds 1e-2, where
T evaluates to -0.15114460471287988,
gtT evaluates to -0.013333333333333308, and
1e-2 evaluates to 0.01.
[  FAILED  ] TempTest.volumetric (43 ms)
[----------] 3 tests from TempTest (2530 ms total)

[----------] Global test environment tear-down
[==========] 3 tests from 1 test suite ran. (2530 ms total)
[  PASSED  ] 1 test.
[  FAILED  ] 2 tests, listed below:
[  FAILED  ] TempTest.sinusoidal
[  FAILED  ] TempTest.volumetric

 2 FAILED TEST
```

---
## Exercice 4.5
To test the boundary conditions of the material particle we propose the followin:
* (a) we set a member variable and setter for the `MaterialPoint` class named `isBoundary`. A simple bool flag.
* (b) the rest it plays in the `ComputeTemperature::compute()` function where: (b.1) at the beginning we test the boundary condition of the particle and set the its flag to `true`; (b.2) at the end of the function we read the flag and set the temperature of the particle to 0 if `true`.

### Configure and run
To run the code:
```bash
'/sp4e-andrea-petras/homework3/heat-fft-solver/starting_point/build/particles' 100 20 '/home/as/sp4e-andrea-petras/homework3/heat-fft-solver/starting_point/heat_distribution.csv' material_point  3
```