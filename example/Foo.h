/*
 * Foo.h
 * Matt Russell
 */
#ifndef FOO_H
#define FOO_H

#include<iostream>

class Foo {
 public:
  Foo() {};
  ~Foo() {};
  
  bool operator==(const Foo& other) { 
    return this->value == other.value; 
  };

  void set(int x) { this->value = x; };
  int get()      { return this->value; };
  
 private:
  int value; 
};

#endif
