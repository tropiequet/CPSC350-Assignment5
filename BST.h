/*
Taylor Ropiequet
2349522
ropiequet@chapman.edu
CPSC 350-02
Assignment 5

This is my Binary Search Tree template class.
*/


#include <iostream>
#include "TreeNode.h"
#include "SingleLinkedList.h"


template <class Key, class Value>

class BST{

public:
  BST();
  ~BST();

  //void insertNode(Key key);
  void insertNode(Key k, Value v);
  bool searchNode(Key k);
  bool deleteNode(Key k);

  bool isEmpty();
  Value getMax();
  Value getMin();
  void recPrint(TreeNode<Key,Value> *node);
  void printTree();

  SingleLinkedList<Value>* getValues(TreeNode<Key,Value> *d);
  TreeNode<Key,Value>* getRoot();
  Value getValue(Key k);


  TreeNode<Key,Value>* getSuccessor(TreeNode<Key,Value> *d); //return the successor of the node to be deleted, d
  SingleLinkedList<Value> *values = new SingleLinkedList<Value>;



private:

  TreeNode<Key,Value> *root;

};

template <class Key, class Value>
BST<Key,Value>::BST(){
  root = NULL;
}

template <class Key, class Value>
BST<Key,Value>::~BST(){
  //iterate and delete, this is 0(n)
}

template <class Key, class Value>
bool BST<Key,Value>::isEmpty(){
  return(root == NULL);
}



//prints from specific node
template <class Key, class Value>
void BST<Key,Value>::recPrint(TreeNode<Key,Value> *node){
  //inorder traversal
  if (node != NULL){
    recPrint(node->left);
    cout << node->key << endl;
    recPrint(node->right);
  }
}

//prints entire tree
template <class Key, class Value>
void BST<Key,Value>::printTree(){
  recPrint(root);
}


template <class Key, class Value>
Value BST<Key,Value>::getMax(){
  //looking for rightmost TreeNode<Key,Value>
  if (isEmpty()){
    return Value();
  }

  TreeNode<Key,Value> *current = root;

  while (current->right != NULL){
    current = current->right;
  }
  return current->value;
}


template <class Key, class Value>
Value BST<Key,Value>::getMin(){
  //looking for leftmost TreeNode<Key,Value>
  if (isEmpty()){
    return Value();
  }

  TreeNode<Key,Value> *current = root;

  while (current->left != NULL){
    current = current->left;
  }
  return current->value;
}


// template <class Key, class Value>
// void BST<Key,Value>::insertNode(T key){
//   TreeNode<Key,Value> *node = new TreeNode<Key,Value>(key);
//
//   if(isEmpty()){
//     //empty tree
//     root = node;
//   }else{
//     //not empty
//     TreeNode<Key,Value> *current = root;
//     TreeNode<Key,Value> *parent = NULL;
//     while (true){
//       parent = current;
//
//       if (key < current->key){
//         //go left
//         current = current->left;
//         if (current == NULL){
//           //found insertion point
//           parent->left = node;
//           break;
//         }
//       }else{
//         //go right
//         current = current->right;
//         if (current == NULL){
//           //found insertion point
//           parent->right = node;
//           break;
//         }
//       }
//     }
//   }
// }


template <class Key, class Value>
void BST<Key,Value>::insertNode(Key k , Value v){
  TreeNode<Key, Value> *node = new TreeNode<Key, Value>(k, v);


  if(isEmpty()){
    //empty tree
    root = node;
  }else{
    //not empty
    TreeNode<Key, Value> *current = root;
    TreeNode<Key, Value> *parent = NULL;
    while (true){
      parent = current;

      if (k < current->key){
        //go left
        current = current->left;
        if (current == NULL){
          //found insertion point
          parent->left = node;
          break;
        }
      }else{
        //go right
        current = current->right;
        if (current == NULL){
          //found insertion point
          parent->right = node;
          break;
        }
      }
    }
  }
}




template <class Key, class Value>
bool BST<Key,Value>::searchNode(Key k){

  if(isEmpty()){
    return false;
  }else{
    //not empty, lets look for the value
    TreeNode<Key,Value> *current = root;

    while (current->key != k){
      if (k < current->key){
        current = current->left;
      }else{
        current = current->right;
      }
      if (current == NULL){
        //we did not find it
        return false;
      }
    }
    return true;
  }
}


template <class Key, class Value>
bool BST<Key,Value>::deleteNode(Key k){
  if (isEmpty()){
    return false;
  }
  TreeNode<Key,Value> *parent = NULL;
  TreeNode<Key,Value> *current = root;
  bool isLeftNode = true;

  while (current->key != k){
    parent = current;


    if (k < current->key){
      //go leftmost
      isLeftNode = true;
      current = current->left;
    }else{
      isLeftNode = false;
      current = current->right;
    }

    if (current == NULL){
      //value deleteNode
      return false;
    }
  }
  //if we make it here, we found it


  //case: node to be deleted has no children
  if (current->left == NULL && current->right == NULL){
    if (current == root){ //root
      root = NULL;
    }else if(isLeftNode){ //left
      parent->left = NULL;
    }else{ //right
      parent->right = NULL;
    }
  //case: node to be deleted has left child only
  }else if (current->right == NULL){
    //node has left child, no right child
    if (current == root){ //root
      root = current->left;
    }else if (isLeftNode){ //left
      parent->left = current->left;
    }else{ //right
      parent->right = current->left;
    }
  //case: node to be deleted has right child only
  }else if (current->left == NULL){
    if (current == root){ //root
      root = current->right;
    }else if (isLeftNode){ //left
      parent->left = current->right;
    }else{ //right
      parent->right = current->right;
    }
  //case: node to be deleted has 2 children - we need to find the successor in this case
  }else{
    TreeNode<Key,Value> *successor = getSuccessor(current); //current is the node to be deleted

    if (current == root){ //root
      root = successor;
    }else if (isLeftNode){ //left
      parent->left = successor;
    }else{ //right
      parent->right = successor;
    }
    successor->left = current->left;
  }
  return true;
}



template <class Key, class Value>
TreeNode<Key,Value>* BST<Key,Value>::getSuccessor(TreeNode<Key,Value> *d){ //d is the node to be deleted
  TreeNode<Key,Value> *sp = d;
  TreeNode<Key,Value> *successor = d;
  TreeNode<Key,Value> *current = d->right;

  while (current != NULL){
    sp = successor;
    successor = current;
    current = current->left;
  }

  if (successor != d->right){
    //descendant of the right child
    sp->left = successor->right;
    successor->right = d->right;
  }

  return successor;
}
template <class Key, class Value>
SingleLinkedList<Value>* BST<Key,Value>::getValues(TreeNode<Key,Value> *node){
  //inorder traversal
  if (node != NULL){
    getValues(node->left);
    values->insertBack(node->value);
    getValues(node->right);
  }
  return values;
}

template <class Key, class Value>
TreeNode<Key,Value>* BST<Key,Value>::getRoot(){
  return root;
}


template <class Key, class Value>
Value BST<Key,Value>::getValue(Key k){

TreeNode<Key,Value> *current = root; //start at g

while (current->key != k){
  if (k < current->key){
    current = current->left;
  }else{
    current = current->right;
  }
}

return current->value;
}
