/*
Taylor Ropiequet
2349522
ropiequet@chapman.edu
CPSC 350-02
Assignment 5

This is my Student class.
*/

#include "Student.h"
#include <iostream>

using namespace std;


Student::Student(){
   m_id = -1;
   m_name = "";
   m_level = "";
   m_major = "";
   m_gpa = -1;
   m_advisor = -1;
}

Student::Student(int id, string name, string level, string major, double gpa, int advisor){
  m_id = id;
  m_name = name;
  m_level = level;
  m_major = major;
  m_gpa = gpa;
  m_advisor = advisor;
}

Student::~Student(){

}


void Student::setID(int id){
  m_id = id;
}


void Student::setName(string name){
  m_name = name;
}


void Student::setLevel(string level){
  m_level = level;
}


void Student::setMajor(string major){
  m_major = major;
}


void Student::setGPA(int gpa){
  m_gpa = gpa;
}


void Student::setAdvisor(int advisor){
  m_advisor = advisor;
}


int Student::getID(){
  return m_id;
}


string Student::getName(){
  return m_name;
}


string Student::getLevel(){
  return m_level;
}


string Student::getMajor(){
  return m_major;
}


double Student::getGPA(){
  return m_gpa;
}


int Student::getAdvisor(){
  return m_advisor;
}

void Student::printInfo(){
  cout << m_id << "|" << m_name << "|" << m_level << "|" << m_major << "|" << m_gpa << "|";
  if (m_advisor == 0){
    cout << "No advisor" << endl;
  }else{
    cout << m_advisor << endl;
  }
}

string Student::writeInfo(){
  string advisor;
  if (m_advisor == 0){
    advisor = "No advisor";
  }else{
    advisor = to_string(m_advisor);
  }
  return (to_string(m_id) + "|" + m_name + "|" + m_level + "|" + m_major + "|" + to_string(m_gpa) + "|" + advisor);
}
