/*
 * ArrayList.h
 * Matt Russell
 * COMP15 lab 0
 * 1/6/2021
 *
 * This is an (class declaration for an ArrayList for lab0.
 *
 * TODO: complete the file!
 */
#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include<iostream>
#include<string>

class ArrayList{
 public:
  ArrayList();
  ~ArrayList();
  
  void insert(int x); 
  void remove(int x);
  bool find(int x); 

  int numitems(); 
  
 private:

  int num_items;
  //TODO: add other private member variables
};

#endif
