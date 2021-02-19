
# unit_test - a frictionless C++ unit testing framework.
By Matt Russell

Let's assume we want to test a simple ArrayList class. 

```cpp
/*
 * ArrayList.h
 */

class ArrayList(){
  public:
    ArrayList();
    ~ArrayList();

    void getSize(); 
    void pushBack(int);
    void popBack(int);
    
    ...
    
};

```

unit tests for the class. 

```cpp
/*
 * ArrayList_tests.cpp
 */
 
#include <iostream>
#include "ArrayList.h"

void first_size_test(){
    ArrayList list; 
    assert(list.size() == 0);
    list.push_back(1); 
    assert(list.size() == 1); 
    list.push_back(2);
    assert(list.size() == 2); 
}

void scnd_size_test(){
    ArrayList list; 
    for (int i = 0; i < 100; i++)
    { 
        assert(list.size() == i); 
        list.pushBack(i); 
    }
}   

void third_size_test(){
    ArrayList list; 
    for (int i = 0; i < 100; i++)
    { 
        assert(list.size() == i); 
        list.popBack(i); 
    }
    
    for (int i = 100; i > 0; i--){
        assert(list.size() == i); 
        list.popBack(i);
    }
}   

```

unit_test output




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
