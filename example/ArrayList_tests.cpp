/*
 * ArraryList_tests.cpp
 * Matt Russell
 * 1/6/2021
 * This file demonstrates test style for the unit_test unit testing framework.
 *
 * Rules for unit tests:
 *     All test file names must end with the string "_tests.cpp"
 *     All test functions must take no arguments
 *     All test functions must return void
 *
 * Background info for tests:
 *     If a test finishes execution, it is considered successful.
 *     Use assert(boolean_expression) to test for known conditions.
 *     If the expression evaluates to false, then the assertion fails.
 *     Tests will also fail on segfaults, etc.
 *  
 * Other notes:
 *     Be sure to #include any .h files as necessary
 *     You may have multiple testing files, but all tests must have unique names
 *     Valgrind will be run automatically on all tests
 * 
 * Workflow encouragements:
 *     You are encouraged to write MANY, MANY tests!!!
 *     Furthermore, you are encouraged to write and run tests as you work.
 *     So, the workflow should be something along the lines of: 
 *            1) Write a function (or part of a function)
 *            2) Write at least 1 test for the code you just wrote
 *            3) Run the tests, and fix all errors (including memory issues)
 *            4) Repeat!
 *    *** It is wise to debug BEFORE moving on to writing the next function. ***
 *
 * NB: The ArrayList code has bugs, so the tests will fail first on purpose!
 * Be sure to ask questions on piazza, or come to office hours!
*/

#include <cassert>
#include "ArrayList.h"

/*
 * constructor test 0 
 * Make sure no fatal errors/memory leaks in the default constructor
 */
void constructor_0() {
  ArrayList list = ArrayList();
}

/*
 * constructor test 1 
 * Make sure no items exist in the list upon construction
 * Note: given the provided code, this test should fail. 
 */
void constructor_1() {
  ArrayList list = ArrayList();
  assert(list.numitems() == 0);
}

/*
 * destructor test 
 * Destructor called implicitly
 * Make sure no fatal errors/memory leaks in the destructor
 */
void destructor() {
  ArrayList list = ArrayList();  
}


