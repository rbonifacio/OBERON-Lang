# OBERON-Lang

An implementation of OBERON-0 in C++. Our goal here is to
better understand the work of Thomas Reps on data-flow analysis-
considering the IDE (Interprecedural Distributive Environments) class of
problems. We will also implement an interpreter for the OBERON-0 language and
several compilers for translating OBERON-0 into LLVM, JIMPLE,
and other high-level languages (like C or Java). In this way,
we hope we will also get use to the LLVM and JIMPLE intermediate
representations.

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

