/*
Taylor Ropiequet
2349522
ropiequet@chapman.edu
CPSC 350-02
Assignment 5

This is my Transaction class header file.
*/


#include <iostream>
using namespace std;

class Transaction{

public:

  Transaction();
  Transaction(char operation, char person);
  ~Transaction();

  char m_operation;
  char m_person;

  char getOperation();
  char getPerson();


  void setOperation(char operation);
  void setPerson(char person);


};
