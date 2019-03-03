/*
Name:                   Jin Jung
Student ID:             2329401
Email:                  jijung@chapman.edu
Course no. & Section:   CS350-02
Assignment:             2
*/

/*
  Driver file to test the functionality of GameOfLife program.
*/

#include "GameOfLife.h"

int main(int argc, char** argv) {
  int fileChoice  = 0;
  int mode = 0;
  string filelocation = "";

  cout << "Welcome to John Conway's Game of life!\nPlease enter:\n (1) to start with random configuration\n (2) to specify a flatfile configuration.\n";
  cin >> fileChoice;
  if (cin.fail()) {
    cout << "Invalid input!\n";
    cin.clear();
    cin.ignore();
    exit(1);
  }
  cout << "Select a boundary mode:\n(1) classic\n(2) mirror\n(3) doughnut\n";
  cin >> mode;
  if (cin.fail() || (mode != 1 && mode != 2 && mode != 3 )) {
    cout << "Invalid input!\n";
    cin.clear();
    cin.ignore();
    exit(1);
  }
  if (fileChoice == 1) {  //new simulation

    GameOfLife simulation1(mode); //generate new simulation
    simulation1.run();
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
    if (filelocation.find(".txt") == -1)  //append extension if required
    {
      filelocation+=".txt";
    }
    ifstream istream(filelocation);
    if(istream.is_open()) {    //check that file exists
      istream.close();
      //run behavior frame by frame, pauses, or output to file
      GameOfLife simulation1(filelocation, mode);
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
