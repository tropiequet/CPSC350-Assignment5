/*
Taylor Ropiequet
2349522
ropiequet@chapman.edu
CPSC 350-02
Assignment 5

This is my Faculty class.
*/

#include "Faculty.h"
#include <iostream>
using namespace std;


Faculty::Faculty(){
   m_id = -1;
   m_name = "";
   m_level = "";
   m_department = "";
   m_advisees = new SingleLinkedList<int>;
}

Faculty::Faculty(int id, string name, string level, string department, SingleLinkedList<int> *advisees){
  m_id = id;
  m_name = name;
  m_level = level;
  m_department = department;
  m_advisees = advisees;
}

Faculty::~Faculty(){

}


void Faculty::setID(int id){
  m_id = id;
}


void Faculty::setName(string name){
  m_name = name;
}


void Faculty::setLevel(string level){
  m_level = level;
}


void Faculty::setDepartment(string department){
  m_department = department;
}


void Faculty::setAdvisees(SingleLinkedList<int>* advisees){
  m_advisees = advisees;
}


int Faculty::getID(){
  return m_id;
}


string Faculty::getName(){
  return m_name;
}


string Faculty::getLevel(){
  return m_level;
}


string Faculty::getDepartment(){
  return m_department;
}


SingleLinkedList<int>* Faculty::getAdvisees(){
  return m_advisees;
}

void Faculty::printInfo(){
  cout << m_id << "|" << m_name << "|" << m_level << "|" << m_department << "|";
  if (!m_advisees->isEmpty()){
    m_advisees->printList();
    cout << endl;
  }else{
    cout << "No advisees" << endl;
  }
}

string Faculty::writeInfo(){
  string advisees = "[";
  SingleLinkedList<int> *temp = m_advisees;
  while (!temp->isEmpty()){
    advisees += to_string(temp->removeFront());
    if (!temp->isEmpty()){
      advisees += ",";
    }
  }
  advisees += "]";
  return (to_string(m_id) + "|" + m_name + "|" + m_level + "|" + m_department + "|" + advisees);
}
