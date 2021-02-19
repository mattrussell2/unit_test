/*
 * Foo_tests.cpp
 * Matt Russell
 * This file demonstrates test style for the unit_test framework.
 *   
 * Notes:
 *     All tests must return void, and take no arguments
 *     Multiple XX_tests.cpp files are allowed
 *     All tests must have unique names
 */

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


