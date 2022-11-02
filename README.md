
# sp4e-andrea-petras
Repo for sp4e course's homework for [Andrea Settimi](andrea.settimi@epfl.ch) and [Petras Vestartas](petras.vestartas@epfl.ch).

## Homework 2: *C++ classes*

The goal of the present exercise is to program a family of objects to compute series and dump them.
We are working on VSCode as IDE so the `.gitignore` is presenting some extra entries.

### Exercise 1: *Creating a Project directory*
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
### Exercise 2: *Series class*

*What is the best way/strategy to divide the work among yourselves?* In general, setting up a syntax convention might be helpful, this is why a `CONTRIBUTING.md` file has been added to the repo. Next, having a parent class the best way to split the work charge is for each one of us to take a child implementation. In the exercise 2 case, there are some reinforcements in the parent class that can guide developers such as the `virtual double compute(unsigned int N) = 0;` class member which forces the child class to implement this method.

To run the command line C++ program of exercise 2.6:
```bash
Usage: 'executable-path' <N> <series>
<N>: number of terms
<series>: arithmetic or pi
```

---
### Exercice 3: *Dumper class*

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
'<path-to-exec>' 1222 pi 1 10 0 2 ","
```
where,
```bash
Usage: executuable <N> <series> <frequency> <maxiter> <printMode> <fileformat>
<N>: number of terms
<series>: arithmetic or pi
<Frequency>: step between two outputs
<Maxiter>: capping for steps
<printMode>: 0 to print on screen, 1 to print on file
<separator>: the format output file ',' = .csv, ' ' = .txt, ', ' = .txt, '|' = .psv
```

---
### Exercice 4: *std::ostram manipulation*

> ⚠️ Note: we found out that the overloading function of the operator `<<` wasn't compiling on VScode/gcc. Hence, we had to add the keyword `friend` (exo 4.5):
> ```cpp
> inline friend std::ostream& operator<<(std::ostream& stream, DumperSeries& _this)
> {
>     _this.dump(stream);
>     return stream;
> }
> ```

---
### Exercice 5: *Series complexity*

To evaluate the global complexity of the program we define complexity first as:

**(a)** cyclomatic complexity (complexity of code branching): to do so we use the static code analysis tool [OCLint](https://oclint.org/). To use it we set the command:
```bash
cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON homework2/build/
```
Next:
```bash
$ oclint -p homework2/build/ homework2/src/*.cc homework2/src/*.hh
```
<details><summary>Here is the results print</summary>

```bash
Compiler Warnings:

/usr/lib/gcc/x86_64-linux-gnu/11/../../../../include/c++/11/bits/unique_ptr.h:85:2: delete called on 'SCPP::Series' that is abstract but has non-virtual destructor


OCLint Report

Summary: TotalFiles=11 FilesWithViolations=11 P1=0 P2=11 P3=23 

/home/as/sp4e-andrea-petras/homework2/src/compute_arithmetic.cc:6:39: short variable name [naming|P3] Length of variable name `N` is 1, which is shorter than the threshold of 3
/home/as/sp4e-andrea-petras/homework2/src/compute_pi.cc:6:31: short variable name [naming|P3] Length of variable name `N` is 1, which is shorter than the threshold of 3
/home/as/sp4e-andrea-petras/homework2/src/compute_pi.cc:8:9: short variable name [naming|P3] Length of variable name `pi` is 2, which is shorter than the threshold of 3
/home/as/sp4e-andrea-petras/homework2/src/main.cc:18:1: long line [size|P3] Line with 114 characters exceeds limit of 100
/home/as/sp4e-andrea-petras/homework2/src/main.cc:20:1: long line [size|P3] Line with 121 characters exceeds limit of 100
/home/as/sp4e-andrea-petras/homework2/src/main.cc:26:1: long line [size|P3] Line with 118 characters exceeds limit of 100
/home/as/sp4e-andrea-petras/homework2/src/main.cc:30:1: long line [size|P3] Line with 113 characters exceeds limit of 100
/home/as/sp4e-andrea-petras/homework2/src/main.cc:32:5: short variable name [naming|P3] Length of variable name `N` is 1, which is shorter than the threshold of 3
/home/as/sp4e-andrea-petras/homework2/src/main.cc:42:5: short variable name [naming|P3] Length of variable name `s` is 1, which is shorter than the threshold of 3
/home/as/sp4e-andrea-petras/homework2/src/main.cc:60:5: short variable name [naming|P3] Length of variable name `os` is 2, which is shorter than the threshold of 3
/home/as/sp4e-andrea-petras/homework2/src/main.cc:61:5: short variable name [naming|P3] Length of variable name `p` is 1, which is shorter than the threshold of 3
/home/as/sp4e-andrea-petras/homework2/src/main.cc:62:5: short variable name [naming|P3] Length of variable name `w` is 1, which is shorter than the threshold of 3
/home/as/sp4e-andrea-petras/homework2/src/main.cc:13:1: long method [size|P3] Method with 62 lines exceeds limit of 50
/home/as/sp4e-andrea-petras/homework2/src/main.cc:13:1: high ncss method [size|P2] Method of 37 non-commenting source statements exceeds limit of 30
/home/as/sp4e-andrea-petras/homework2/src/print_series.cc:10:28: short variable name [naming|P3] Length of variable name `os` is 2, which is shorter than the threshold of 3
/home/as/sp4e-andrea-petras/homework2/src/print_series.cc:10:5: avoid default arguments on virtual methods [design|P3] 
/home/as/sp4e-andrea-petras/homework2/src/write_series.cc:11:28: short variable name [naming|P3] Length of variable name `os` is 2, which is shorter than the threshold of 3
/home/as/sp4e-andrea-petras/homework2/src/compute_arithmetic.hh:6:5: destructor of virtual class [convention|P2] class ComputeArithmetic should have a virtual destructor ~ComputeArithmetic()
/home/as/sp4e-andrea-petras/homework2/src/compute_arithmetic.hh:12:24: short variable name [naming|P3] Length of variable name `N` is 1, which is shorter than the threshold of 3
/home/as/sp4e-andrea-petras/homework2/src/series.hh:7:5: base class destructor should be virtual or protected [convention|P2] ~Series() should be protected or virtual according to class ComputeArithmetic
/home/as/sp4e-andrea-petras/homework2/src/compute_pi.hh:6:5: destructor of virtual class [convention|P2] class ComputePi should have a virtual destructor ~ComputePi()
/home/as/sp4e-andrea-petras/homework2/src/compute_pi.hh:12:24: short variable name [naming|P3] Length of variable name `N` is 1, which is shorter than the threshold of 3
/home/as/sp4e-andrea-petras/homework2/src/series.hh:7:5: base class destructor should be virtual or protected [convention|P2] ~Series() should be protected or virtual according to class ComputePi
/home/as/sp4e-andrea-petras/homework2/src/dumper_series.hh:7:5: destructor of virtual class [convention|P2] class DumperSeries should have a virtual destructor ~DumperSeries()
/home/as/sp4e-andrea-petras/homework2/src/dumper_series.hh:15:27: short variable name [naming|P3] Length of variable name `os` is 2, which is shorter than the threshold of 3
/home/as/sp4e-andrea-petras/homework2/src/print_series.hh:10:5: destructor of virtual class [convention|P2] class PrintSeries should have a virtual destructor ~PrintSeries()
/home/as/sp4e-andrea-petras/homework2/src/print_series.hh:20:27: short variable name [naming|P3] Length of variable name `os` is 2, which is shorter than the threshold of 3
/home/as/sp4e-andrea-petras/homework2/src/print_series.hh:20:9: avoid default arguments on virtual methods [design|P3] 
/home/as/sp4e-andrea-petras/homework2/src/dumper_series.hh:7:5: base class destructor should be virtual or protected [convention|P2] ~DumperSeries() should be protected or virtual according to class PrintSeries
/home/as/sp4e-andrea-petras/homework2/src/series.hh:7:5: destructor of virtual class [convention|P2] class Series should have a virtual destructor ~Series()
/home/as/sp4e-andrea-petras/homework2/src/series.hh:13:32: short variable name [naming|P3] Length of variable name `N` is 1, which is shorter than the threshold of 3
/home/as/sp4e-andrea-petras/homework2/src/write_series.hh:11:5: destructor of virtual class [convention|P2] class WriteSeries should have a virtual destructor ~WriteSeries()
/home/as/sp4e-andrea-petras/homework2/src/write_series.hh:21:27: short variable name [naming|P3] Length of variable name `os` is 2, which is shorter than the threshold of 3
/home/as/sp4e-andrea-petras/homework2/src/dumper_series.hh:7:5: base class destructor should be virtual or protected [convention|P2] ~DumperSeries() should be protected or virtual according to class WriteSeries

[OCLint (https://oclint.org) v22.02]

oclint: error: violations exceed threshold
P1=0[0] P2=11[10] P3=23[20] 
```
</details>

**(b)** computational complexity (algorithmic time complexity): to our knowledge there is no such tool that can easily provide such a metric (?). The command `$ time <exec>` can give us an indication of the execution time, but this is specific to a particular machine:
```
real    0m0.001s    <--- wall colck time
user    0m0.001s    <--- the amount of CPU time spent outside the kernel (in process)
sys     0m0.000s    <--- the amount of CPU time spent inside the kernel (out process)
```