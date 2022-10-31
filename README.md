
# sp4e-andrea-petras
Repo for sp4e course's homework for [Andrea Settimi](andrea.settimi@epfl.ch) and [Petras Vestartas](petras.vestartas@epfl.ch).

## Homework 2: C++ classes

The goal of the present exercise is to program a family of objects to compute series and to dump them.
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
