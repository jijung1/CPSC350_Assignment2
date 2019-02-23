/*
Name:                   Jin Jung
Student ID:             2329401
Email:                  jijung@chapman.edu
Course no. & Section:   CS350-02
Assignment:             2
*/

/*
  Driver file to test the functionality of DNAanalysis class.
*/

// To Do: create a GameOfLife readFile method so that all the code can get moved off main

#include "GameOfLife.h"

int main(int argc, char** argv) {
  int fileChoice  = 1;
  string filelocation = "";

  cout << "Welcome to Jon Conway's Game of life!\nPlease enter:\n (1) to start with random configuration\n (2) to specify a flatfile configuration.\n";
  cin >> fileChoice;
  if (cin.fail()) {
    cout << "Invalid input!\n";
    cin.clear();
    cin.ignore();
    exit(1);
  }
  if (fileChoice == 1) {

    //GameOfLife(); //generate new simulation

  }
  else {  //run simulation from supplied file
    cout << "Please enter file location: ";
    cin >> filelocation;
    if (cin.fail()) {
      cout << "Invalid input!\n";
      cin.clear();
      cin.ignore();
      exit(1);
    }
    if (filelocation.find(".txt") == -1)
    {
      filelocation+=".txt";
    }
    ifstream istream(filelocation);
    if(istream.is_open()) {    //check if file exists
      istream.close();
      //run behavior frame by frame, pauses, or output to file
      GameOfLife simulation1(filelocation);
      simulation1.run();
    }
    else {
      cout << "invalid input! Exiting..\n";
      exit(1);
    }
  }
  getchar();
  return 0;
}
