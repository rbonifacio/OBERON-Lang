# OBERON-Lang

An implementation of OBERON-0 in C++. Our goal here is to
better understand the work of Thomas Reps on data-flow analysis-
considering the IDE (Interprecedural Distributive Environments) class of
problems. We will also implement an interpreter for the OBERON-0 language and
several compilers for translating OBERON-0 into LLVM, JIMPLE,
and other high-level languages (like C or Java). In this way,
we hope we will also get use to the LLVM and JIMPLE intermediate
representations.

### Reading list

During the development of OBERON-0, we discussed several references on the field, including 

   * Niklaus Wirth. Compiler Construction 2000. Addison-Wesley (1996).

   * Steven Arzt. Static Data Flow Analysis for Android Applications, PhD thesis, Technische Universität 
     Darmstadt, 2016. 

   * Thomas Reps, Susan Horwitz, and Mooly Sagiv. 1995. Precise interprocedural dataflow 
     analysis via graph reachability. In Proceedings of the 22nd ACM SIGPLAN-SIGACT symposium 
     on Principles of programming languages (POPL '95). ACM, New York, NY, USA, 49-61. 
     DOI=http://dx.doi.org/10.1145/199448.199462

   * Eric Bodden. 2012. Inter-procedural data-flow analysis with IFDS/IDE and Soot. In Proceedings 
     of the ACM SIGPLAN International Workshop on State of the Art in Java Program analysis (SOAP '12). 
     ACM, New York, NY, USA, 3-8. DOI=http://dx.doi.org/10.1145/2259051.2259052

   * George Balatsouras, Kostas Ferles, George Kastrinis, and Yannis Smaragdakis. 2017. A Datalog 
     model of must-alias analysis. In Proceedings of the 6th ACM SIGPLAN International Workshop on State 
     Of the Art in Program Analysis (SOAP 2017). ACM, New York, NY, USA, 7-12. DOI: https://doi.org/10.1145/3088515.3088517


### Building and Testing

Currently, our implementation only depends on google C++ test framework. Please, 
install it and define an environemnt variable (GTEST_DIR) pointing to the dir 
that includes the library *libgtest.a*. For instance, for some OSX distributions, 
it is located at /usr/local/lib. 

To compile, first create an empty folder called bin, then just run the command 'make'.

```bash
mkdir bin
make
```

There is a 'clean' command to compile from scratch.

```bash
make clean 
```

To run the test cases, you must build the test driver. 

````bash
make tester
```` 

An then run it. 

````bash
./bin/tester
````

