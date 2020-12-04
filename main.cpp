/*
Taylor Ropiequet
2349522
ropiequet@chapman.edu
CPSC 350-02
Assignment 5

This is my main method that implements my BST, Stack, SingleLinkedList, Student, Faculty, and Transaction classes.
*/

#include "BST.h"
#include "Student.h"
#include "Faculty.h"
#include "SingleLinkedList.h"
#include "Transaction.h"
#include "GenStack.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main(int argc, char const *argv[]) {

  BST<int, Student> *masterStudent;
  BST<int, Faculty> *masterFaculty;

  // masterStudent = new BST<int, Student>;
  // masterFaculty = new BST<int, Faculty>;

  int id;
  string name;
  string level;
  string major;
  double gpa;
  int advisor;
  string department;
  SingleLinkedList<int> *advisees = new SingleLinkedList<int>;

  bool active = true;

//need to read data from file into BSTs if the files exist
  string line;
  char c;
  int count;



  //CHECKING FOR STUDENT TABLE

//counts lines in file aka how many students
  ifstream countLines1("studentTable.txt");
  count = 0;
  while(getline(countLines1, line)){
    ++count;
  }
  countLines1.close();

  ifstream infileStudent("studentTable.txt");
  if(infileStudent){ //file exists
    masterStudent = new BST<int, Student>;
    for(int i = 0; i < count; ++i){
      string studentInfo[6];
      for (int j = 0; j < 6; ++j){ //puts student info into array to access later to create tree node
        if (j == 5){
          getline(infileStudent, line, '\n');
          studentInfo[j] = line;
        }else{
          getline(infileStudent, line, '|');
          studentInfo[j] = line;
        }
      }

      id = stoi(studentInfo[0]);
      name = studentInfo[1];
      level = studentInfo[2];
      major = studentInfo[3];
      gpa = stod(studentInfo[4]);
      advisor = stoi(studentInfo[5]);

      Student s(id, name, level, major, gpa, advisor);

      masterStudent->insertNode(s.getID(), s);
    }
  }else{ //file does not exist
    masterStudent = new BST<int, Student>;
  }


//CHECKING FOR FACULTY TABLE
  ifstream countLines2("facultyTable.txt");
  count = 0;
  while(getline(countLines2, line)){
    ++count;
  }
  countLines2.close();


  int commaCount;

  ifstream infileFaculty("facultyTable.txt");
  if(infileFaculty){ //file exists
      masterFaculty = new BST<int, Faculty>;
    for(int i = 0; i < count; ++i){
      string facultyInfo[4];
      advisees = new SingleLinkedList<int>; //fresh LL
      for (int j = 0; j < 5; ++j){ //puts faculty info into array to access later to create tree node
        if (j == 4){
          infileFaculty.get(c); // gets rid of open bracket for linked list
          getline(infileFaculty, line, ']'); // gets entire "linked list" into a string separated by commas
          commaCount = 0;
          for (int k = 0; k < line.length(); ++k){ //finds how many ids are in the list by counting the commas
            if(line.at(k) == ','){
              commaCount++;
            }
          }
          string delimiter = ",";
          string substring;
          for (int x = 0; x < commaCount + 1; ++x){
            substring = line.substr(0, line.find(delimiter));
            advisees->insertBack(stol(substring)); //inserts id into linked list
            line.erase(0, line.find(delimiter) + delimiter.length()); // erases the id we just added to linked list
          }
          //advisees->insertBack(stoi(line));

          infileFaculty.get(c); // gets rid of newline character for next loop
        }else{
          getline(infileFaculty, line, '|');
          facultyInfo[j] = line;
        }
      }
      id = stoi(facultyInfo[0]);
      name = facultyInfo[1];
      level = facultyInfo[2];
      department = facultyInfo[3];


      Faculty f(id, name, level, department, advisees);


      masterFaculty->insertNode(f.getID(), f);
    }
  }else{ //file does not exist
      masterFaculty = new BST<int, Faculty>;
  }


  GenStack<Transaction> transactions(128);
  GenStack<Student> studentStack(128);
  GenStack<Faculty> facultyStack(128);



  while (active){
    //for (int i = 0; i < 3; ++i){

    int choice;
    SingleLinkedList<Student> *students = new SingleLinkedList<Student>;
    SingleLinkedList<Faculty> *faculty = new SingleLinkedList<Faculty>;
    SingleLinkedList<int> *tempIDS = new SingleLinkedList<int>;
    Student s;
    Faculty f;
    int studentID;
    int facultyID;

    int tempID;
    int pos;



    cout << "1. Print all students and their information" << endl;
    cout << "2. Print all faculty and their information" << endl;
    cout << "3. Find and display student information given the student id" << endl;
    cout << "4. Find and display faculty information given the faculty id" << endl;
    cout << "5. Given a student’s id, print the name and info of their faculty advisor" << endl;
    cout << "6. Given a faculty id, print all the names and info of his/her advisees" << endl;
    cout << "7. Add a new student" << endl;
    cout << "8. Delete a student given the id" << endl;
    cout << "9. Add a new faculty member" << endl;
    cout << "10. Delete a faculty member given the id" << endl;
    cout << "11. Change a student’s advisor given the student id and the new faculty id" << endl;
    cout << "12. Remove an advisee from a faculty member given the ids" << endl;
    cout << "13. Rollback" << endl;
    cout << "14. Exit" << endl;
    cout << "Please enter the number of the function you would like to execute" << endl;

    cin >> choice;
    cin.ignore();

    switch (choice){

      case 1: //print all students
      {
        students = masterStudent->getValues(masterStudent->getRoot()); //linked list of students (temp)
        while (!students->isEmpty()){
          students->removeFront().printInfo();
        }
      }
        break;


      case 2: //print all faculty
      {
        faculty = masterFaculty->getValues(masterFaculty->getRoot()); //linked list of faculty (temp)
        cout << "do we get here?" << endl;
        while (!faculty->isEmpty()){
          faculty->removeFront().printInfo();
        }
      }
      break;


      case 3: //print student given id
      {
         cout << "What is the student's ID?" << endl;
         cin >> id;
         cin.ignore();
         if(masterStudent->searchNode(id)){ //student exists
           masterStudent->getValue(id).printInfo();
         }else{
           cout << "Student does not exist!" << endl;
         }
       }
       break;


      case 4: //print faculty given id
      {
        cout << "What is the faculty's ID?" << endl;
        cin >> id;
        cin.ignore();
        if(masterFaculty->searchNode(id)){ //faculty exists
          masterFaculty->getValue(id).printInfo();
        }else{
          cout << "Faculty does not exist!" << endl;
        }
      }
      break;



      case 5: //print student's advisor
      {
        cout << "What is the student's ID?" << endl;
        cin >> id;
        cin.ignore();
        if(masterStudent->searchNode(id)){ //student exists
          id = masterStudent->getValue(id).getAdvisor(); //gets students advisor's ID
          masterFaculty->getValue(id).printInfo();
        }else{
          cout << "Student does not exist!" << endl;
        }
      }
      break;




      case 6: //print faculty's advisees
      {
        cout << "What is the faculty's ID?" << endl;
        cin >> id;
        cin.ignore();
        if(masterFaculty->searchNode(id)){ //faculty exists
          f = masterFaculty->getValue(id); //faculty member
          advisees = f.getAdvisees(); //linked list of student ids
          while (!advisees->isEmpty()){
            id = advisees->removeFront(); //gets first student id from linked list
            masterStudent->getValue(id).printInfo(); //gets the student from the BST given the ID and prints info
          }
        }else{
          cout << "Faculty does not exist!" << endl;
        }
      }
        break;



      case 7: //add new student
      {
        cout << "What is the student's ID?" << endl;
        cin >> id;
        cin.ignore();
        cout << "What is the student's name?" << endl;
        getline(cin, name);
        cout << "What is the student's level?" << endl;
        getline(cin, level);
        cout << "What is the student's major?" << endl;
        getline(cin, major);
        cout << "What is the student's GPA?" << endl;
        cin >> gpa;
        cin.ignore();
        cout << "What is the ID of the student's advisor?" << endl;
        cin >> advisor;
        cin.ignore();
        while (!masterFaculty->searchNode(advisor)){ //faculty does not exist so need a different advisor id for student
          cout << "That faculty ID does not exist." << endl;
          cout << "Please enter another ID for the student's advisor" << endl;
          cin >> advisor;
          cin.ignore();
        }

        Student s(id, name, level, major, gpa, advisor);

        masterStudent->insertNode(s.getID(), s);

        f = masterFaculty->getValue(advisor); // gets students advisor
        masterFaculty->deleteNode(advisor); //deletes student advisor from tree
        advisees = f.getAdvisees(); //gets advisor linked list
        advisees->insertBack(id); // adds student id to linked list

        f.setAdvisees(advisees); //sets linked list

        masterFaculty->insertNode(f.getID(), f); //adds faculty back to bst with updated linked list of advisees

        Transaction t('d', 's');
        transactions.push(t);
        studentStack.push(s);

      }
      break;


      case 8: //delete student
      {
        while (true){
          cout << "What is the ID of the student you want to delete?" << endl;
          cin >> id;
          cin.ignore();
          if (!masterStudent->searchNode(id)){
            cout << "That student does not exist, please try again." << endl;
          }else{
            break;
          }
        }

        f = masterFaculty->getValue(masterStudent->getValue(id).getAdvisor()); //gets student's advisor
        masterFaculty->deleteNode(masterStudent->getValue(id).getAdvisor()); // deletes student advisor from tree so we can change linked list and re add
        advisees = f.getAdvisees();

        pos = advisees->find(id);
        advisees->deletePos(pos); //deletes student ID from linked List
        f.setAdvisees(advisees);

        masterFaculty->insertNode(f.getID(), f); //adds faculty back to bst with updated linked list of advisees

        s = masterStudent->getValue(id);
        masterStudent->deleteNode(id);
        Transaction t('i', 's');
        transactions.push(t);
        studentStack.push(s);
      }
      break;

      case 9: //add new faculty
      {
        cout << "What is the faculty member's ID?" << endl;
        cin >> id;
        cin.ignore();
        cout << "What is the faculty member's name?" << endl;
        getline(cin, name);
        cout << "What is the faculty member's level?" << endl;
        getline(cin, level);
        cout << "What is the faculty member's department?" << endl;
        getline(cin, department);
        // cout << "How many advisees does the faculty member have?" << endl;
        // cin >> count;
        // cin.ignore();
        //
        // tempIDS = new SingleLinkedList<int>;
        // int oldAdvisor;
        // advisees = new SingleLinkedList<int>;
        //
        // int i = 1;
        //
        // cout << "Please enter advisee " << i << " ID" << endl;
        // cin >> tempID;
        //   cin.ignore();
        //
        //
        // while (i <= count){
        //
        //   if (masterStudent->searchNode(tempID)){ // student exists so we can add
        //     tempIDS->insertBack(tempID); // adds students id to linked List
        //
        //     //need to update student info
        //     s = masterStudent->getValue(tempID); // gets student to update advisor
        //     masterStudent->deleteNode(tempID); // deletes student from tree so we can update advisor and add it back
        //     oldAdvisor = s.getAdvisor();
        //     s.setAdvisor(id); //sets new advisor
        //     masterStudent->insertNode(s.getID(), s); //adds student back to tree with updated information
        //
        //
        //     //need to remove student from old advisor LL
        //     f = masterFaculty->getValue(oldAdvisor); // gets old advisor
        //     masterFaculty->deleteNode(oldAdvisor); //deletes old advisor to update ll
        //     advisees = f.getAdvisees(); //gets old advisor LL
        //     pos = advisees->find(tempID);
        //     advisees->deletePos(pos); //deletes student ID from linked List of old advisor
        //     f.setAdvisees(advisees); // assigns the new LL to the old advisor
        //     masterFaculty->insertNode(f.getID(), f); //adds old faculty back to tree with updated info
        //
        //     ++i;
        //
        //     if (i <= count){
        //       cout << "Please enter advisee " << i << " ID" << endl;
        //       cin >> tempID;
        //       cin.ignore();
        //     }
        //
        //   }else{ //student does not exist
        //     cout << "That student does not exist, please try again" << endl;
        //     cout << "Please enter advisee " << i << " ID" << endl;
        //     cin >> tempID;
        //     cin.ignore();
        //   }
        // }
        tempIDS = new SingleLinkedList<int>;
        Faculty f(id, name, level, department, tempIDS);

        masterFaculty->insertNode(f.getID(), f);

        Transaction t('d', 'f');
        transactions.push(t);
        facultyStack.push(f);

      }
      break;


      case 10: //delete faculty
      {
        while (true){
          cout << "What is the ID of the faculty member you want to delete?" << endl;
          cin >> id;
          cin.ignore();
          if (!masterFaculty->searchNode(id)){
            cout << "That faculty member does not exist, please try again." << endl;
          }else{
            break;
          }
        }
        int newAdvisor;

        //need to get the advisees of this faculty member
        f = masterFaculty->getValue(id);
        advisees = f.getAdvisees();
        while (!advisees->isEmpty()){
          tempID = advisees->removeFront();
          s = masterStudent->getValue(tempID); //gets student
          masterStudent->deleteNode(tempID); //deletes from tree so we can update advisor
          while(true){
            cout << "Please enter the new advisor for the following student" << endl;
            cout << s.getID() << "|" << s.getName() << endl;
            cin >> newAdvisor;
            cin.ignore();

            if (!masterFaculty->searchNode(newAdvisor)){
              cout << "That faculty member does not exist, please try again." << endl;
            }else{
              break;
            }
          }
          s.setAdvisor(newAdvisor);
          masterStudent->insertNode(s.getID(), s);


          f = masterFaculty->getValue(newAdvisor);
          masterFaculty->deleteNode(newAdvisor);
          tempIDS = f.getAdvisees();
          tempIDS->insertBack(tempID);
          f.setAdvisees(tempIDS);
          masterFaculty->insertNode(f.getID(), f);
        }

        f = masterFaculty->getValue(id);
        masterFaculty->deleteNode(id);

        Transaction t('i', 'f');
        transactions.push(t);
        facultyStack.push(f);
      }

        break;


      case 11: //change student advisor given ids
      {
        while (true){
          cout << "What is the student's ID?" << endl;
          cin >> studentID;
          cin.ignore();
          if (!masterStudent->searchNode(studentID)){
            cout << "That student does not exist, please try again." << endl;
          }else{
            break;
          }
        }

        while (true){
          cout << "What is the new advisor's ID?" << endl;
          cin >> facultyID;
          cin.ignore();
          if (!masterFaculty->searchNode(facultyID)){
            cout << "That faculty member does not exist, please try again." << endl;
          }else{
            break;
          }
        }


        s = masterStudent->getValue(studentID);
        masterStudent->deleteNode(studentID);
        tempID = s.getAdvisor();

        //get student's old advisor and edit LL
        f = masterFaculty->getValue(tempID);
        masterFaculty->deleteNode(tempID);
        advisees = f.getAdvisees();
        pos = advisees->find(studentID);
        advisees->deletePos(pos);
        f.setAdvisees(advisees);
        masterFaculty->insertNode(f.getID(), f);

        //update student's new advisor LL
        f = masterFaculty->getValue(facultyID);
        masterFaculty->deleteNode(facultyID);
        advisees = f.getAdvisees();
        advisees->insertBack(studentID);
        f.setAdvisees(advisees);
        masterFaculty->insertNode(f.getID(), f);

        //update student's advisor
        s.setAdvisor(facultyID);
        masterStudent->insertNode(s.getID(), s);

      }

        break;


      case 12: //remove advisee from faculty
      {
        while (true){
          cout << "What is the faculty member's ID?" << endl;
          cin >> facultyID;
          cin.ignore();
          if (!masterFaculty->searchNode(facultyID)){
            cout << "That faculty member does not exist, please try again." << endl;
          }else{
            break;
          }
        }

        while (true){
          cout << "What is the ID of the student you want to remove?" << endl;
          cin >> studentID;
          cin.ignore();
          if (!masterStudent->searchNode(studentID)){
            cout << "That student does not exist, please try again." << endl;
          }else{
            break;
          }
        }


        //update faculty LL
        f = masterFaculty->getValue(facultyID);
        masterFaculty->deleteNode(facultyID);
        advisees = f.getAdvisees();
        pos = advisees->find(studentID);
        advisees->deletePos(pos);
        f.setAdvisees(advisees);
        masterFaculty->insertNode(f.getID(), f);

        s = masterStudent->getValue(studentID);

        while (true){
          cout << "What is the ID of the new advisor for this student: " << endl;
          cout << s.getID() << "|" << s.getName() << endl;
          cin >> facultyID;
          cin.ignore();
          if (!masterFaculty->searchNode(facultyID)){
            cout << "That faculty member does not exist, please try again." << endl;
          }else{
            break;
          }
        }


        s.setAdvisor(facultyID);

        f = masterFaculty->getValue(facultyID);
        masterFaculty->deleteNode(facultyID);
        advisees = f.getAdvisees();
        advisees->insertBack(studentID);
        f.setAdvisees(advisees);
        masterFaculty->insertNode(f.getID(), f);
      }

        break;



      case 13: //rollback
      {
        while (true){
          cout << "How many times(up to 5) would you like to rollback?" << endl;
          cin >> count;

          if (count > 5){
            cout << "Please enter a number less than 5." << endl;
          }else{
            break;
          }
        }

        Transaction t;
        char operation;
        char person;

        for (int i = 0; i < count; ++i){
          t = transactions.pop();
          operation = t.getOperation();
          if (operation == 'i'){ //we need to insert
            person = t.getPerson();
            if (person == 's'){ //student insert
              s = studentStack.pop();
              masterStudent->insertNode(s.getID(), s);
              f = masterFaculty->getValue(s.getAdvisor()); // gets students advisor
              masterFaculty->deleteNode(s.getAdvisor()); //deletes student advisor from tree
              advisees = f.getAdvisees(); //gets advisor linked list
              advisees->insertBack(s.getID()); // adds student id to linked list
              f.setAdvisees(advisees); //sets linked list
              masterFaculty->insertNode(f.getID(), f); //adds faculty back to bst with updated linked list of advisees
            }else if (person == 'f') {//faculty insert
              f = facultyStack.pop();
              masterFaculty->insertNode(f.getID(), f);
              id = f.getID();
              advisees = f.getAdvisees();
              int size = advisees->getSize(); //aka how many advisees the faculty has
              SingleLinkedList<int> *tempAdvisees = new SingleLinkedList<int>;

              for (int i = 0; i < size; ++i){
                s = masterStudent->getValue(advisees->removeFront());
                masterStudent->deleteNode(s.getID());

                tempID = s.getAdvisor();
                f = masterFaculty->getValue(tempID);
                masterFaculty->deleteNode(tempID);
                tempAdvisees = f.getAdvisees();
                pos = tempAdvisees->find(s.getID());
                advisees->deletePos(pos); //deletes student ID from linked List
                f.setAdvisees(tempAdvisees);
                masterFaculty->insertNode(f.getID(), f);

                s.setAdvisor(id);
                masterStudent->insertNode(s.getID(), s);
              }
            }
          }else if (operation == 'd'){
            person = t.getPerson();
            if (person == 's'){ //student delete
              s = studentStack.pop();
              masterStudent->deleteNode(s.getID());
              f = masterFaculty->getValue(s.getAdvisor());
              masterFaculty->deleteNode(s.getAdvisor());
              advisees = f.getAdvisees();
              pos = advisees->find(s.getID());
              advisees->deletePos(pos); //deletes student ID from linked List
              f.setAdvisees(advisees);
              masterFaculty->insertNode(f.getID(), f); //adds faculty back to bst with updated linked list of advisees
            }else if (person == 'f') {//faculty delete
              f = facultyStack.pop();
              masterFaculty->deleteNode(f.getID());
            
              id = f.getID();
              advisees = f.getAdvisees();
              int size = advisees->getSize(); //aka how many advisees the faculty has

              for (int i = 0; i < size; ++i){
                s = masterStudent->getValue(advisees->removeFront());
                masterStudent->deleteNode(s.getID());
                s.setAdvisor(0);
                masterStudent->insertNode(s.getID(), s);
            }
          }
        }
      }
    }
        break;


      case 14: //exit
      {
        active = false;

        SingleLinkedList<Student> *students = new SingleLinkedList<Student>;
        SingleLinkedList<Faculty> *faculty = new SingleLinkedList<Faculty>;
        Student s;
        Faculty f;
        ofstream outfile;
        string info;

      //write masterStudent back to studentTable
      outfile.open("studentTable.txt");
        students = masterStudent->getValues(masterStudent->getRoot()); //linked list of students (temp)
        while (!students->isEmpty()){
          s = students->removeFront();
          info = s.writeInfo();
          outfile << info << endl;
        }
        outfile.close();


        //write masterFaculty back to facultyTable

        outfile.open("facultyTable.txt");
          faculty = masterFaculty->getValues(masterFaculty->getRoot()); //linked list of students (temp)
          while (!faculty->isEmpty()){
            f = faculty->removeFront();
            info = f.writeInfo();
            outfile << info << endl;
          }
          outfile.close();
      }
        break;

     }
     cout << "--------------------------------------------------------" << endl;

   }
   return 0;
 }
