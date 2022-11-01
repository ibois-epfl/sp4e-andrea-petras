
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
cd homework2
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
'./bin/Homework2'
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

---
### Exercice 3: Dumper class

> ⚠️ Note: when we try to implement the DumperSeries like proposed by the `sujet.pdf`:
> ```cpp
> class DumperSeries
> {
> public:
>     virtual void dump() = 0;
> 
> protected:
>     Series & series;
> }
> ```
> We recived this error and the child constructor instantiation fail:
> ```
> class 'DumperSeries' does not declare any constructor to initialize its non-modifiable members
> ```
> Thus, there are two option to solve the problem (stackoverflow [here](https://stackoverflow.com/questions/15451840/why-cant-we-initialize-class-members-at-their-declaration)): (a) we implement a constructor with Series as field in DumperSeries class, (b) we implement a default constructor without fields but we make the DumperSeries's Series member static. We decided to go for the solution (a) as it seems to be the most sound like so:
> ```cpp
> class DumperSeries
>   {
>   public:
>       DumperSeries(Series& series)
>           : p_Series(series)
>       {};
>       ~DumperSeries() = default;>
> 
>       virtual void dump() = 0;>
> 
>   protected:
>       Series& p_Series;
>   };
> ```

To run the command line program:
```bash
'<path-to-exec>' 1222 pi 1 10 0
```
where,
```bash
<N>: number of terms
<series>: arithmetic or pi
<Frequency>: step between two outputs
<Maxiter>: capping for steps
<printMode>: 0 to print on screen, 1 to print on file
```