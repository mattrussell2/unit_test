unit_test is a simple unit testing framework for C++ code. 

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
 * unit_tests.h
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

===============================================================================
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ compiling tests @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
===============================================================================
clang++ unit_test_driver.o 

--> tests compiled successfully

===============================================================================
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ running tests @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
===============================================================================
100%|█████████████████████████████████████████████| 3/3 [00:01<00:00,  2.08it/s]

===============================================================================
@@@@@@@@@@@@@@@@@@@@@@@@ test output for passing tests @@@@@@@@@@@@@@@@@@@@@@@@
===============================================================================

===============================================================================
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ test report @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
===============================================================================

                          name    passed?   valgrind passed?   diff passed?
passing tests
                   constructor       y              y                  
                      set_test       y              y                  
                   set_and_get       y              y                  
failing tests
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

===============================================================================
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ compiling tests @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
===============================================================================
clang++ unit_test_driver.o 

--> tests compiled successfully

===============================================================================
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ running tests @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
===============================================================================
100%|█████████████████████████████████████████████| 3/3 [00:01<00:00,  2.04it/s]

===============================================================================
@@@@@@@@@@@@@@@@@@@@@@@@ test output for passing tests @@@@@@@@@@@@@@@@@@@@@@@@
===============================================================================

===============================================================================
@@@@@@@@@@@@@@@@@@@@@@@@ test output for failing tests @@@@@@@@@@@@@@@@@@@@@@@@
===============================================================================
=== set_and_get ===
-stderr-
a.out: ./unit_tests.h:20: void set_and_get(): Assertion `f.get() == 10' failed.


===============================================================================
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ test report @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
===============================================================================

                          name    passed?   valgrind passed?   diff passed?
passing tests
                   constructor       y              y                  
                      set_test       y              y                  
failing tests
                   set_and_get       n              n                  
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

===============================================================================
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ compiling tests @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
===============================================================================
clang++ unit_test_driver.o 

--> tests compiled successfully

===============================================================================
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ running tests @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
===============================================================================
100%|█████████████████████████████████████████████| 3/3 [00:01<00:00,  2.05it/s]

===============================================================================
@@@@@@@@@@@@@@@@@@@@@@@@ test output for failing tests @@@@@@@@@@@@@@@@@@@@@@@@
===============================================================================
-valgrind stderr-
==6974== Memcheck, a memory error detector
==6974== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==6974== Using Valgrind-3.15.0 and LibVEX; rerun with -h for copyright info
==6974== Command: ./a.out constructor
==6974== 
==6974== 
==6974== HEAP SUMMARY:
==6974==     in use at exit: 400 bytes in 1 blocks
==6974==   total heap usage: 5 allocs, 4 frees, 73,320 bytes allocated
==6974== 
==6974== 400 bytes in 1 blocks are definitely lost in loss record 1 of 1
==6974==    at 0x483C583: operator new[](unsigned long) (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==6974==    by 0x401845: Foo::Foo() (in /home/mrussell/test/a.out)
==6974==    by 0x401330: constructor() (in /home/mrussell/test/a.out)
==6974==    by 0x4017AA: main (in /home/mrussell/test/a.out)
==6974== 
==6974== LEAK SUMMARY:
==6974==    definitely lost: 400 bytes in 1 blocks
==6974==    indirectly lost: 0 bytes in 0 blocks
==6974==      possibly lost: 0 bytes in 0 blocks
==6974==    still reachable: 0 bytes in 0 blocks
==6974==         suppressed: 0 bytes in 0 blocks
==6974== 
==6974== For lists of detected and suppressed errors, rerun with: -s
==6974== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)

-valgrind stderr-
==6978== Memcheck, a memory error detector
==6978== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==6978== Using Valgrind-3.15.0 and LibVEX; rerun with -h for copyright info
==6978== Command: ./a.out set_test
==6978== 
==6978== 
==6978== HEAP SUMMARY:
==6978==     in use at exit: 400 bytes in 1 blocks
==6978==   total heap usage: 5 allocs, 4 frees, 73,320 bytes allocated
==6978== 
==6978== 400 bytes in 1 blocks are definitely lost in loss record 1 of 1
==6978==    at 0x483C583: operator new[](unsigned long) (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==6978==    by 0x401845: Foo::Foo() (in /home/mrussell/test/a.out)
==6978==    by 0x401357: set_test() (in /home/mrussell/test/a.out)
==6978==    by 0x4017AA: main (in /home/mrussell/test/a.out)
==6978== 
==6978== LEAK SUMMARY:
==6978==    definitely lost: 400 bytes in 1 blocks
==6978==    indirectly lost: 0 bytes in 0 blocks
==6978==      possibly lost: 0 bytes in 0 blocks
==6978==    still reachable: 0 bytes in 0 blocks
==6978==         suppressed: 0 bytes in 0 blocks
==6978== 
==6978== For lists of detected and suppressed errors, rerun with: -s
==6978== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)

-valgrind stderr-
==6991== Memcheck, a memory error detector
==6991== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==6991== Using Valgrind-3.15.0 and LibVEX; rerun with -h for copyright info
==6991== Command: ./a.out set_and_get
==6991== 
==6991== 
==6991== HEAP SUMMARY:
==6991==     in use at exit: 400 bytes in 1 blocks
==6991==   total heap usage: 5 allocs, 4 frees, 73,320 bytes allocated
==6991== 
==6991== 400 bytes in 1 blocks are definitely lost in loss record 1 of 1
==6991==    at 0x483C583: operator new[](unsigned long) (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==6991==    by 0x401845: Foo::Foo() (in /home/mrussell/test/a.out)
==6991==    by 0x4013B7: set_and_get() (in /home/mrussell/test/a.out)
==6991==    by 0x4017AA: main (in /home/mrussell/test/a.out)
==6991== 
==6991== LEAK SUMMARY:
==6991==    definitely lost: 400 bytes in 1 blocks
==6991==    indirectly lost: 0 bytes in 0 blocks
==6991==      possibly lost: 0 bytes in 0 blocks
==6991==    still reachable: 0 bytes in 0 blocks
==6991==         suppressed: 0 bytes in 0 blocks
==6991== 
==6991== For lists of detected and suppressed errors, rerun with: -s
==6991== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)


===============================================================================
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ test report @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
===============================================================================

                          name    passed?   valgrind passed?   diff passed?
passing tests
failing tests
                   constructor       y              n                  
                      set_test       y              n                  
                   set_and_get       y              n                  
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
  Foo()  {};
  ~Foo() {};
  
  void set(int x) { 
     std::cout << "entered set" << std::endl; 
     this->value = 50; 
     std::cout << "the value of x is: " << x << std::endl;
     std::cout << "the value of my value is: " << this->value << std::endl;
  };
  
  int get() { 
      return this->value;
  };
  
 private:
  int value; 
};
```
stdout and stderr are captured during runtime and will be printed to the terminal if not empty.
```
matt:example$ unit_test

===============================================================================
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ compiling tests @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
===============================================================================
clang++ unit_test_driver.o 

--> tests compiled successfully

===============================================================================
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ running tests @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
===============================================================================
100%|█████████████████████████████████████████████| 3/3 [00:01<00:00,  2.01it/s]

===============================================================================
@@@@@@@@@@@@@@@@@@@@@@@@ test output for passing tests @@@@@@@@@@@@@@@@@@@@@@@@
===============================================================================
=== set_test ===
-stdout-
entered set
the value of x is: 10
the value of my value is: 50


===============================================================================
@@@@@@@@@@@@@@@@@@@@@@@@ test output for failing tests @@@@@@@@@@@@@@@@@@@@@@@@
===============================================================================
=== set_and_get ===
-stdout-
entered set
the value of x is: 10
the value of my value is: 50

-stderr-
a.out: ./unit_tests.h:20: void set_and_get(): Assertion `f.get() == 10' failed.


===============================================================================
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ test report @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
===============================================================================

                          name    passed?   valgrind passed?   diff passed?
passing tests
                   constructor       y              y                  
                      set_test       y              y                  
failing tests
                   set_and_get       n              n                  
```

What happens if our code crashes? Let's manually raise a segfault in get()
```cpp
/*
 * Foo.h
 * A simple class.
 */

#include <iostream>
#include <csignal>

class Foo {
 public:
  Foo()  {};
  ~Foo() {};
  
  void set(int x) {  
     this->value = x; 
  };
  
  int get() {
     std::raise(SIGSEGV); 
     return this->value;
  };
  
 private:
  int value; 
};
```
Fortunately, unit_test runs each test individually, so one segfault will not crash 
all tests.
```
matt:example$ unit_test

===============================================================================
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ compiling tests @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
===============================================================================
clang++ unit_test_driver.o 

--> tests compiled successfully

===============================================================================
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ running tests @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
===============================================================================
100%|█████████████████████████████████████████████| 3/3 [00:01<00:00,  2.04it/s]

===============================================================================
@@@@@@@@@@@@@@@@@@@@@@@@ test output for passing tests @@@@@@@@@@@@@@@@@@@@@@@@
===============================================================================

===============================================================================
@@@@@@@@@@@@@@@@@@@@@@@@ test output for failing tests @@@@@@@@@@@@@@@@@@@@@@@@
===============================================================================

===============================================================================
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ test report @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
===============================================================================

                          name    passed?   valgrind passed?   diff passed?
passing tests
                   constructor       y              y                  
                      set_test       y              y                  
failing tests
                   set_and_get       n              n                  
```

## prerequisites 

unit_test requires 
  * Python >= 3.7
  * Valgrind 
  * A C++ compiler with a C++ standard >= C++11

## installation

    git clone https://www.github.com/mattrussell2/unit_test
    cd unit_test
    chmod a+x unit_test

Copy the unit_test file to any location on your $PATH.

Assuming you're an administrator, and running Linux/Unix, for example: 
    
    sudo cp unit_test /usr/local/bin/
    
If not, you can always create an alias for unit_test in .bashrc or .profile

    alias unit_test="/path/to/unit/test/executable/unit_test"
    
If following this step, don't forget to run 

    source ~/.bashrc 

To see the demo in action:  

    cd examples
    unit_test
    
If the command fails, ensure that unit_test is in a folder on your $PATH, and 
that the file it executable by you. 

## usage requirements
In order to use unit_test, a few requirements must be met. Namely, there must be certain 
testing files in your working directory, each containing test functions. Further, there must
be a Makefile which follows a few simple rules. Details follow below. 

### test file
unit_test requires a testing file named `unit_tests.h` in your working directory

### test functions
Each test in a test file must be a function which has  
  1) a void return type  
  2) no input arguments

Each test must have a unique name. 

### Makefile
unit_test requires a Makefile with a target named 'unit_test', which must require a file
`unit_test_driver.o`, and which will build an executable 'a.out'. 

For example, the Makefile rule to test the Foo class with unit_test could be:  
```
unit_test: unit_test_driver.o Foo_tests.cpp Foo.h  
    clang++ unit_test_driver.o  Foo_tests.cpp
```
Note that `unit_test` builds `unit_test_driver.o` for you! This file has `int main()`
inside of it - so do **not** add a `main` function!

## testing notes
A test is considered successful upon successful completion of the test function. 

It is suggested that you use assert() in your tests, however this is not required. 

Upon successful completion of a test, it will immediately be rerun with valgrind.

Any test that fails will fail valgrind by default. 

Run **unit_test -h** to see options. 

## unit_test implementation details 

unit_test works by leveraging an originally incomplete driver, the text of
which is inside unit_test.

Specifically, unit_test extracts all test functions from all test files, and, 
for each test function:
  
  1. Adds a forward declaration for each function to the driver file text. 
  2. Inserts a string in the driver file text of the following format:
          
            { "test_function_name": test_function_name },\n
            
Each pair is inserted in the driver file text as part of the initialization of a 
std::map<std::string, FnPtr>> object, where "FnPtr" is a typdef of a 
pointer to a void function that takes no arguments.

The driver file, `unit_test_driver.o`, is then saved in the current working directory.

The files are compiled in accordance with the Makefile, and a.out is run 
one time for each test via the Python subprocess module. 

Specifically, for each test, the name of the test function name is provided 
to a.out as a string; the string is used as the key to extract the function
pointer associated with the test from the map. The test is then run. 
