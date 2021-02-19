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

  void set(int x) { this->value = x;    };
  int  get()      { return this->value; };
  
 private:
  int value; 
};

#endif
