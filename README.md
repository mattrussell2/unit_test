
# unit_test - a frictionless C++ unit testing framework.
By Matt Russell

Let's assume we want to test the following class Foo. 

```cpp
class Foo {
 public:
  Foo() {};
  ~Foo() {};

  void set(int x) { this->value = x; };
  int  get()      { return this->value; };
  
 private:
  int value; 
};
```

Here are unit tests for the class. 

```cpp
#include <cassert>
#include "Foo.h"

void constructor() {
  Foo f; 
}

void set_get() {
  Foo f; 
  f.set(10); 
  assert(f.get() == 10); 
}   
```

And the output of running unit_test

```
matt:example$ unit_test


<span style="color:blue">setting up tests</span>
-----------------------------------
<span style="color:green">tests were set up successfully</span>


<span style="color:blue">compiling tests</span>
-----------------------------------
<span style="color:green">compilation passed</span>


<span style="color:blue">constructor/span>
-----------------------------------
<span style="color:green">test passed</span>
<span style="color:green">valgrind passed</span>


<span style="color:blue">set get</span>
-----------------------------------
<span style="color:green">test passed</span>
<span style="color:green">valgrind passed</span>


<span style="color:blue">results</span>
-----------------------------------
2 / 2 tests passed
2 / 2 valgrind tests passed

```

## prerequisites 

unit_test requires Python >= 3.7, clang++, and valgrind

## installation

    git clone https://www.github.com/mattrussell2/unit_test
    cd unit_test
    chmod a+x unit_test

Copy the unit_test file to any location on your $PATH.

Assuming you're an administrator, and running Linux/Unix, for example: 
    
    sudo cp unit_test /usr/local/bin/
    
If not, you can always create an alias for unit_test in .bashrc or .profile

    alias /home/username/unit_test unit_test

## usage

To see the system in action:  

    cd examples
    unit_test
    
If the command fails, ensure that unit_test is in a folder on your $PATH, and 
that it is user-executable. 

Note that the examples contain bugs on purpose, so not all tests will pass!

## implementation details 

There are a two key phases of this script: 

1) initilize unit_test_driver.cpp
2) compile, run, and run valgrind on all tests cases

### initialization

This program works by leveraging an originally incomplete driver, the text of
which is inside unit_test.

Then, it parses all files in the student's working directory of the form XX_tests.cpp.

Specifically, for each testing file, the script discovers all of the test functions. 
Test functions are functions which have both
  1) a void return type
  2) no input arguments

For each test function, the script:
  1) Adds a forward declaration to the driver file text. 
  2) Inserts a string in the driver file text of the following format:
          
            { "test_function_name": test_function_name },\n

    This pair is inserted in the initialization of a std::map<std::string, FnPtr>> object,
    where "FnPtr" is a typdef of a void function that takes no arguments.

The driver file, unit_test_driver.cpp, is then saved in the current working directory.

### compilation and running

    After compilation, Python makes subprocess calls to the compiled binary, passing 
    in a testname as an argument.

    Valgrind is run automatically on all tests, and pass/fail results are displayed. 

    Passes / failures are kept track of; all results are printed to the terminal. 
