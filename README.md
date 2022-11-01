
# sp4e-andrea-petras
Repo for sp4e course's homework for [Andrea Settimi](andrea.settimi@epfl.ch) and [Petras Vestartas](petras.vestartas@epfl.ch).

## Homework 2: C++ classes

The goal of the present exercise is to program a family of objects to compute series and dump them.
We are working on VSCode as IDE so the `.gitignore` is presenting some extra entries.

### Exercise 1: Creating a Project directory
Here's the structure of the C++ project first committed:
```bash
├── CMakeLists.txt
├── homework2
│   ├── build  <------------ not included
│   │   ├── bin
│   │   │   └── Homework2
│   │   ├── ...
│   └── src
│       ├── CMakeLists.txt
│       └── main.cc
└── README.md
```
To config the project from the repository root:
```bash
mkdir build
cd build
cmake -S ../.. -B .
```

To build the project:
```bash
make
```

To run the executable:
```bash
'./homework2/build/bin/Homework2'
```
---
### Exercise 2: Series class

*What is the best way/strategy to divide the work among yourselves?* In general, setting up a syntax convention might be helpful, this is why a `CONTRIBUTING.md` file has been added to the repo. Next, having a parent class the best way to split the work charge is for each one of us to take a child implementation. In the exercise 2 case, there are some reinforcements in the parent class that can guide developers such as the `virtual double compute(unsigned int N) = 0;` class member which forces the child class to implement this method.

To run the command line C++ program of exercise 2.6:
```bash
Usage: 'executable-path' <N> <series>
<N>: number of terms
<series>: arithmetic or pi
```