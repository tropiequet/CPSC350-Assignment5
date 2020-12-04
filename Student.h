/*
Taylor Ropiequet
2349522
ropiequet@chapman.edu
CPSC 350-02
Assignment 5

This is my Student class header file.
*/

#include <iostream>
using namespace std;

class Student{

public:
  Student();
  Student(int id, string name, string level, string major, double gpa, int advisor);
  ~Student();

  int m_id;
  string m_name;
  string m_level;
  string m_major;
  double m_gpa;
  int m_advisor;

  void setID(int id);
  void setName(string name);
  void setLevel(string level);
  void setMajor(string major);
  void setGPA(int gpa);
  void setAdvisor(int advisor);

  int getID();
  string getName();
  string getLevel();
  string getMajor();
  double getGPA();
  int getAdvisor();

  void printInfo();
  string writeInfo();
};
