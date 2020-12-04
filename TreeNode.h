/*
Taylor Ropiequet
2349522
ropiequet@chapman.edu
CPSC 350-02
Assignment 4

This is my TreeNode template class.
*/

#include <iostream>

using namespace std;

template <class Key, class Value>

class TreeNode{

public:
  TreeNode();
  //TreeNode(Key k); //key and value are the same, key = value and value = key
  TreeNode(Key k, Value v);
  ~TreeNode();

  Key key;
  Value value;
  TreeNode<Key, Value> *left;
  TreeNode<Key, Value> *right;


};

template <class Key, class Value>
TreeNode<Key, Value>::TreeNode(){
  left = NULL;
  right = NULL;
}

// template <class Value>
// TreeNode<Value>::TreeNode(T k){
//   left = NULL;
//   right = NULL;
//   key = k;
// }

template <class Key, class Value>
TreeNode<Key, Value>::TreeNode(Key k, Value v){
  left = NULL;
  right = NULL;
  key = k;
  value = v;
}



template <class Key, class Value>
TreeNode<Key, Value>::~TreeNode(){
  delete left;
  delete right;
}
