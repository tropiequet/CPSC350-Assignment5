/*
Taylor Ropiequet
2349522
ropiequet@chapman.edu
CPSC 350-02
Assignment 5

This is my ListNode template class.
*/

#include <iostream>
#ifndef LISTNODE_H
#define LISTNODE_H
using namespace std;

template<class T>

class ListNode{
public:
  ListNode();
  ListNode(T d);
  ~ListNode();

  T data;
  ListNode<T> *next;

};


template<class T>
ListNode<T>::ListNode(){
data = NULL;
next = NULL;
}

template<class T>
ListNode<T>::ListNode(T d){
  data = d;
  next = NULL;
}

template<class T>
ListNode<T>::~ListNode(){
  delete next;
}

#endif
