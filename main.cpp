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

// TO DO: move all preprocessor directives to .h file
// To Do: create a GameOfLife readFile method so that all the code can get moved off main

#include "GameOfLife.h"

int main(int argc, char** argv) {
  int fileChoice  = 1;
  string filelocation = "";
  string row = "";
  string column = "";
  int rowint = 0;
  int columnint = 0;


  cout << "Welcome to Jon Conway's Game of life!\nPlease enter:\n (1) to start with random configuration\n (2) to specify a flatfile configuration.\n";
  cin >> fileChoice;
  if (cin.fail()) {
    cout << "Invalid input!\n";
    cin.clear();
    cin.ignore();
    exit(1);
  }
  if (fileChoice == 1) {
    //start random simulation
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
      getline(istream, row);
      getline(istream, column);
      rowint = stoi(row);
      columnint = stoi(column);
      cout << "row: " << rowint << "\ncolumn: "<< columnint<< endl;
      char** initialCondition = new char*[rowint];

      for (int i = 0; i < rowint; ++i) {
        initialCondition[i] = new char[columnint];
      }
      for (int j = 0; j < rowint; ++j) {
        string temp = "";
        getline(istream, temp);
        for (int k = 0; k < temp.length(); ++k) {
          initialCondition[j][k] = temp[k];
        cout << initialCondition[j][k];
        }
        cout << endl;
      }
      //call a constructor GameOfLife(initialCondition);
      for(int i = 0; i < rowint; ++i) {
        delete[] initialCondition[i];
      }
      delete[] initialCondition;
      istream.close();
    }
    else {
      cout << "invalid input! Exiting..\n";
      exit(1);
    }
  }

  getchar();
  return 0;
}
