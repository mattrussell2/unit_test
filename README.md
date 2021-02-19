Unit test is a simple and elegant framework in which you can write and run tests for C++ code. 

Let's assume we want to test the following class Foo. 

```cpp
/*
 * Foo.h
 * A simple class.
 */
class Foo {
 public:
  Foo()  {};
  ~Foo() {};
  
  void set(int x) { this->value = x;    };
  int  get()      { return this->value; };
  
 private:
  int value; 
};
```

With unit_test, here's an example unit testing file for Foo. 

```cpp
/*
 * Foo_tests.cpp
 * unit tests for the Foo class.
 */
#include <cassert>
#include "Foo.h"

void constructor() {
  Foo f; 
}

void set_test() {
  Foo f; 
  f.set(10); 
}

void set_and_get() {
  Foo f; 
  f.set(10); 
  assert(f.get() == 10); 
}
```
And the output of unit_test:

```
matt:example$ unit_test


setting up tests
-----------------------------------
tests were set up successfully


compiling tests
-----------------------------------
compilation passed


constructor
-----------------------------------
test passed
valgrind passed


set test
-----------------------------------
test passed
valgrind passed


set and get
-----------------------------------
test passed
valgrind passed


results
-----------------------------------
3 / 3 tests passed
3 / 3 valgrind tests passed
```

Now, let's introduce a bug into our Foo class
```cpp
/*
 * Foo.h
 * A simple class.
 */
class Foo {
 public:
  Foo()  {};
  ~Foo() {};
  
  void set(int x) { this->value = 50;   }; //should be x, not 50!
  int  get()      { return this->value; };
  
 private:
  int value; 
};
```
The output of unit_test reads:

```
matt:example$ unit_test


setting up tests
-----------------------------------
tests were set up successfully


compiling tests
-----------------------------------
compilation passed


constructor
-----------------------------------
test passed
valgrind passed


set test
-----------------------------------
test passed
valgrind passed


set and get
-----------------------------------
test failed
valgrind failed by default
stderr
------
a.out: Foo_tests.cpp:27: void set_and_get(): Assertion `f.get() == 10' failed.



results
-----------------------------------
2 / 3 tests passed
2 / 3 valgrind tests passed
```

Let's go ahead and introduce a memory leak in the constructor!

```cpp
/*
 * Foo.h
 * A simple class.
 */
class Foo {
 public:
  Foo()  { int *x = new int[100]; };
  ~Foo() {};
  
  void set(int x) { this->value = x;    };
  int  get()      { return this->value; };
  
 private:
  int value; 
};
```
Fortunately, unit_test doesn't let us get away with this madness!
```
matt:example$ unit_test

setting up tests
-----------------------------------
tests were set up successfully


compiling tests
-----------------------------------
compilation passed


constructor
-----------------------------------
test passed
valgrind failed
==6477== Memcheck, a memory error detector
==6477== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==6477== Using Valgrind-3.15.0 and LibVEX; rerun with -h for copyright info
==6477== Command: ./a.out constructor
==6477== 
==6477== 
==6477== HEAP SUMMARY:
==6477==     in use at exit: 400 bytes in 1 blocks
==6477==   total heap usage: 5 allocs, 4 frees, 73,320 bytes allocated
==6477== 
==6477== 400 bytes in 1 blocks are definitely lost in loss record 1 of 1
==6477==    at 0x483C583: operator new[](unsigned long) (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==6477==    by 0x4039E5: Foo::Foo() (in /home/matt/unit_test/example/a.out)
==6477==    by 0x4038B0: constructor() (in /home/matt/unit_test/example/a.out)
==6477==    by 0x401506: main (in /home/matt/unit_test/example/a.out)
==6477== 
==6477== LEAK SUMMARY:
==6477==    definitely lost: 400 bytes in 1 blocks
==6477==    indirectly lost: 0 bytes in 0 blocks
==6477==      possibly lost: 0 bytes in 0 blocks
==6477==    still reachable: 0 bytes in 0 blocks
==6477==         suppressed: 0 bytes in 0 blocks
==6477== 
==6477== For lists of detected and suppressed errors, rerun with: -s
==6477== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)



set test
-----------------------------------
test passed
valgrind failed
==6479== Memcheck, a memory error detector
==6479== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==6479== Using Valgrind-3.15.0 and LibVEX; rerun with -h for copyright info
==6479== Command: ./a.out set_test
==6479== 
==6479== 
==6479== HEAP SUMMARY:
==6479==     in use at exit: 400 bytes in 1 blocks
==6479==   total heap usage: 5 allocs, 4 frees, 73,320 bytes allocated
==6479== 
==6479== 400 bytes in 1 blocks are definitely lost in loss record 1 of 1
==6479==    at 0x483C583: operator new[](unsigned long) (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==6479==    by 0x4039E5: Foo::Foo() (in /home/matt/unit_test/example/a.out)
==6479==    by 0x4038D7: set_test() (in /home/matt/unit_test/example/a.out)
==6479==    by 0x401506: main (in /home/matt/unit_test/example/a.out)
==6479== 
==6479== LEAK SUMMARY:
==6479==    definitely lost: 400 bytes in 1 blocks
==6479==    indirectly lost: 0 bytes in 0 blocks
==6479==      possibly lost: 0 bytes in 0 blocks
==6479==    still reachable: 0 bytes in 0 blocks
==6479==         suppressed: 0 bytes in 0 blocks
==6479== 
==6479== For lists of detected and suppressed errors, rerun with: -s
==6479== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)



set and get
-----------------------------------
test failed
valgrind failed by default
stderr
------
a.out: Foo_tests.cpp:27: void set_and_get(): Assertion `f.get() == 10' failed.



results
-----------------------------------
2 / 3 tests passed
0 / 3 valgrind tests passed


matt:example$ 
```

Let's fix the memory leak, and use print statements to help catch our other bug.
```cpp
/*
 * Foo.h
 * A simple class.
 */

#include<iostream>

class Foo {
 public:
  Foo()  { std::cerr << "inside the constructor" << std::endl; };
  ~Foo() {};
  
  void set(int x) { 
     std::cerr << "entered set" << std::endl; 
     this->value = 50; 
     std::cout << "the value of x is: " << x << std::endl;
     std::cout << "the value of my value is: " << this->value << std::endl;
  };
  int  get()      { return this->value; };
  
 private:
  int value; 
};
```
cout and cerr are captured during runtime and will be printed to the terminal if not empty.
```
matt:example$ unit_test


setting up tests
-----------------------------------
tests were set up successfully


compiling tests
-----------------------------------
compilation passed


constructor
-----------------------------------
test passed
valgrind passed


set test
-----------------------------------
test passed
stdout
------
entered set
the value of x is 10
the value of my value is: 50

valgrind passed


set and get
-----------------------------------
test failed
valgrind failed by default
stdout
------
entered set
the value of x is 10
the value of my value is: 50

stderr
------
a.out: Foo_tests.cpp:27: void set_and_get(): Assertion `f.get() == 10' failed.



results
-----------------------------------
2 / 3 tests passed
2 / 3 valgrind tests passed


matt:example$ 
```

## prerequisites 

unit_test requires Python >= 3.7 and valgrind

## installation

    git clone https://www.github.com/mattrussell2/unit_test
    cd unit_test
    chmod a+x unit_test

Copy the unit_test file to any location on your $PATH.

Assuming you're an administrator, and running Linux/Unix, for example: 
    
    sudo cp unit_test /usr/local/bin/
    
If not, you can always create an alias for unit_test in .bashrc or .profile

    alias unit_test="/home/$USER/unit_test"

To see this demo in action:  

    cd examples
    unit_test
    
If the command fails, ensure that unit_test is in a folder on your $PATH, and 
that the file it executable by you. 

## usage requirements
In order to use unit_test, a few requirements must be met. Namely, there must be certain 
testing files in your working directory, each containing test functions. Further, there must
be a Makefile which follows a few simple rules. Details follow below. 

### test file
unit_test requires one or more testing files of the form XX_tests.cpp

### test functions
Each test must be a function which has  
  1) a void return type  
  2) no input arguments

Each test, even accross multiple testing files, must have a unique name. 

### Makefile
unit_test requires a Makefile with a target named 'unit_test', which must require a file
main.cpp, and which will build an executable 'a.out'. 

For example, the Makefile rule to test the Foo class with unit_test could be:  

    unit_test: main.cpp Foo_tests.cpp Foo.h  
        clang++ main.cpp Foo_tests.cpp

**NOTE** 
The file main.cpp is created for you by unit_test - this file has the testing 
program's main(), so there is no need for you to write a main(). Instead, think of your test
functions as each being its own main. For details on this see below. To be clear, when 
using unit_test, you do **NOT** need to run 'make', create main.cpp, or create a main(). 

## testing notes
A test is considered successful upon successful completion of the test function. 

It is suggested that you use assert() in your tests, however this is not required. 

Upon successful completion of a test, it will immediately be rerun with valgrind.

Any test that fails will fail valgrind by default. 

Valgrind is run with --leak-check=full and --show-leak-kinds=all by default. 

Run **unit_test -v** to run valgrind in verbose mode. 

After each test, the output of stdout and stderr are printed to the terminal if not empty. 

## unit_test implementation details 

unit_test works by leveraging an originally incomplete driver, the text of
which is inside unit_test.

Specifically, unit_test extracts all test functions from all test files, and, 
for each test function:
  1) Adds a forward declaration of the function to the driver file text. 
  2) Inserts a string in the driver file text of the following format:
          
            { "test_function_name": test_function_name },\n
            
Each pair is inserted in the driver file text as part of the initialization of a std::map<std::string, FnPtr>> object, where "FnPtr" is a typdef of a 
pointer to a void function that takes no arguments.

The driver file, main.cpp, is then saved in the current working directory.

Then the files are compiled in accordance with the Makefile, and a.out is run 
one time for each test via the Python subprocess module. 

Specifically, for each test, the name of the test function name is provided to a.out as a string; the string is used as the key to extract the function pointer associated with the test. The test is then run. 
