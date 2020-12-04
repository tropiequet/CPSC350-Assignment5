/*
Taylor Ropiequet
2349522
ropiequet@chapman.edu
CPSC 350-02
Assignment 4

This is my SingleLinkedList template class.
*/

#include <iostream>
#include "ListNode.h"
#ifndef SINGLELINKEDLIST_H
#define SINGLELINKEDLIST_H
using namespace std;

template<class T>

class SingleLinkedList{
private:
  ListNode<T> *front;
  ListNode<T> *back;
  unsigned int size;

public:
  SingleLinkedList();
  ~SingleLinkedList();
  void insertFront(T d);
  void insertBack(T d);
   T removeFront();
  // T removeBack();
  int find(T value);
  T deletePos(int pos);

  void printList();
  bool isEmpty();
  unsigned int getSize();
};


template<class T>
SingleLinkedList<T>::SingleLinkedList(){
  front = NULL;
  back = NULL;
  size = 0;
}

template<class T>
SingleLinkedList<T>::~SingleLinkedList(){
  //
}


template<class T>
void SingleLinkedList<T>::insertFront(T d){
  ListNode<T> *node = new ListNode<T>(d);
  if (size == 0){
    //empty List
    back = node;
  }
  node->next = front;
  front = node;
  ++size;
}


template<class T>
void SingleLinkedList<T>::insertBack(T d){
  ListNode<T> *node = new ListNode<T>(d);
  node->next = NULL;
  if (size == 0){ //same as size == 0
    front = node;
    back = node;
  }else{
    back->next = node;
    back = node;
  }
  ++size;
}


template<class T>
T SingleLinkedList<T>::removeFront(){
  ListNode<T> *node = front;
  T temp;
  if (size == 0){
    //list is empty
    return T();
  }else if (front->next == NULL){
    //only 1 element in list
    front = NULL;
    temp = node->data;
    --size;
    return temp;
  }else{
    //more than 1 element in list
    front = front->next;
    node->next = NULL;
    temp = node->data;
    --size;

    return temp;
  }
}
//
// template<class T>
// T SingleLinkedList<T>::removeBack(){
//   ListNode<T> *node = back;
//   if (front == NULL){
//     //list is empty
//     return T();
//   }



template<class T>
void SingleLinkedList<T>::printList(){
  if (!isEmpty()){
    ListNode<T> *curr = front;
    cout << "[";
    while (curr != NULL){
      cout<<curr->data;
      if (curr->next != NULL){
        cout << ", ";
      }
      curr = curr->next;
    }
    cout << "]";
  }
}


template<class T>
int SingleLinkedList<T>::find(T value){
  int pos = -1;
  ListNode<T> *curr = front;
  while (curr != NULL){
    ++pos;
    if (curr->data == value){
      break;
    }
    curr = curr->next;
  }
  if (curr == NULL){
    pos = -1;
  }
  return pos;
}


template<class T>
T SingleLinkedList<T>::deletePos(int pos){
  int p = 0;
  ListNode<T> *curr = front;
  ListNode<T> *prev = front;

  if (pos == 0){
    front = front->next;
    curr->next = NULL;
  }else{
    while (p != pos){
      prev = curr;
      curr = curr->next;
      p++;
    }
    prev->next = curr->next;
    curr->next = NULL;
  }
  T temp = curr->data;
  size--;

  delete curr;

  return temp;
}

template<class T>
bool SingleLinkedList<T>::isEmpty(){
  return(size == 0);
}

template<class T>
unsigned int SingleLinkedList<T>::getSize(){
  return(size);
}

#endif
