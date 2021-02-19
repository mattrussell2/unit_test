Let's assume we want to test the following class Foo. 

```cpp
/*
 * Foo.h
 * A simple class.
 */
class Foo {
 public:
  Foo() {};
  ~Foo() {};
  
  void set(int x) { this->value = x;    };
  int  get()      { return this->value; };
  
 private:
  int value; 
};
```

Here is the unit testing file for Foo 

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

void set_get() {
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


set get
-----------------------------------
test passed
valgrind passed


results
-----------------------------------
3 / 3 tests passed
3 / 3 valgrind tests passed
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
functions as each being its own main. To be clear, when using unit_test, you do **NOT** need to run 'make', 
create main.cpp, or create a main(). 

## testing notes
A test is considered upon successful execution of the test function. 

It is suggested that you use assert in your tests, however this is not required. 

Each test will be run with valgrind immediately after the test is run. 

Any test that fails will fail valgrind by default. 

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
