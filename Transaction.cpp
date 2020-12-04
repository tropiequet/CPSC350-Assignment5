/*
Taylor Ropiequet
2349522
ropiequet@chapman.edu
CPSC 350-02
Assignment 5

This is my Transaction class.
*/

#include "Transaction.h"
#include <iostream>
using namespace std;


Transaction::Transaction(){
  m_operation = '\0';
  m_person = '\0';
}

Transaction::Transaction(char operation, char person){
  m_operation = operation;
  m_person = person;
}

Transaction::~Transaction(){

}


char Transaction::getOperation(){
  return m_operation;
}

char Transaction::getPerson(){
  return m_person;
}

void Transaction::setOperation(char operation){
  m_operation = operation;
}

void Transaction::setPerson(char person){
  m_person = person;
}
