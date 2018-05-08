# OBERON-Lang

An implementation of OBERON-0 in C++. Our goal here is to
better understand the work of Thomas Reps on data-flow analysis-
considering the IDE (Interprecedural Distributive Environments) class of
problems. We will also implement an interpreter for the OBERON-0 language and
several compilers for translating OBERON-0 into LLVM, JIMPLE,
and other high-level languages (like C or Java). In this way,
we hope we will also get use to the LLVM and JIMPLE intermediate
representations.

___

To compile, first create an empty folder called bin, than just command 'make'.

```bash
mkdir bin
make
```

There is a 'clean' command to compile from scratch.

```bash
make clean
```

