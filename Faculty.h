/*
Taylor Ropiequet
2349522
ropiequet@chapman.edu
CPSC 350-02
Assignment 5

This is my Faculty class header file.
*/

#include <iostream>
#include "SingleLinkedList.h"
using namespace std;

class Faculty{

public:
  Faculty();
  Faculty(int id, string name, string level, string department, SingleLinkedList<int> *advisees);
  ~Faculty();

  int m_id;
  string m_name;
  string m_level;
  string m_department;
  SingleLinkedList<int> *m_advisees;

  void setID(int id);
  void setName(string name);
  void setLevel(string level);
  void setDepartment(string department);
  void setAdvisees(SingleLinkedList<int> *advisees);

  int getID();
  string getName();
  string getLevel();
  string getDepartment();
  SingleLinkedList<int>* getAdvisees();


  void printInfo();
  string writeInfo();
};
