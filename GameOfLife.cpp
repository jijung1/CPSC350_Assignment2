/*
Name:                   Jin Jung
Student ID:             2329401
Email:                  jijung@chapman.edu
Course no. & Section:   CS350-02
Assignment:             2
*/

/*
  Implementation file for GameOfLife class.
*/
#include "GameOfLife.h"

GameOfLife::GameOfLife(string filelocation, int mode) {   //constructor for initializing with user supplied flatfile
  string row = "";
  string column = "";
  ifstream istream(filelocation); //declare initialize and open stream
  getline(istream, row);  //first line of flat file should represent int row
  getline(istream, column); //second line of flat file should represent int column
  this->mode = mode;
  this->row = stoi(row);
  this->column = stoi(column);
  cout << "row: " << this->row << "\ncolumn: "<< this->column<< endl;
  this->allocateMemory(this->row,this->column);
  for (int j = 0; j < this->column; ++j) {  //initialize all cells with input file data
    string temp = "";
    getline(istream, temp);
    for (int k = 0; k < temp.length(); ++k) {
      this->currentGen[j][k] = temp[k];
    cout << this->currentGen[j][k];
    }
    cout << endl;
  }
  istream.close();
  this -> displayOption();
  if (runOption == 3) {
    this -> setOutFileName();
  }
}
GameOfLife::GameOfLife(int mode) {
  //ask for grid size, dimensions, and decimal number
  this->mode = mode;
  double density = 0.0f;
  this->readInput();
  cin >> density;
  if (cin.fail() || density <=0 || density > 1) { //check for valid input
    cout << "Invalid input!\n";
    cin.clear();
    cin.ignore();
    exit(1);
  }
  this->allocateMemory(this->row, this->column);
  double a = 0.0f;
  for (int i = 0; i < this->row; ++i) {
    for (int j = 0; j < this->column; ++j) {
      a = (RAND_MAX - rand()) / static_cast<double>(RAND_MAX);
      if (a <= density) {
        this->currentGen[i][j] = 'X';
      }
      else {
        this->currentGen[i][j] = '-';
      }
      cout << this->currentGen[i][j];
    }
    cout << endl;
  }
  this -> displayOption();
  if (runOption == 3) {
    this -> setOutFileName();
  }
}
void GameOfLife::allocateMemory(int row, int column) {
  this -> stabilityCheck = new char**[7]; //dynamically allocate memory for 3-d array with 7 cells to check for oscillation cases of that are 2 and 6 generations apart
  for (int m = 0; m < 7; ++m) {
    this->stabilityCheck[m] = new char*[this->row];
    for (int n = 0; n < this->row; ++n) {
      this->stabilityCheck[m][n] = new char[this->column];
    }
  }
  this->currentGen = new char*[this->row];  //dynamically allocate memory for 2-d arrays
  this->modifiedGen = new char* [this -> row]; //free to modify this generation while comparing currentGen
  for (int i = 0; i < this->row; ++i) {
    currentGen[i] = new char[this->column];
    modifiedGen[i] = new char[this->column];
  }
}
void GameOfLife::readInput() {
  cout << "Please enter the number of rows (preferably an integer value >0 and <45), columns (preferably an integer value >0 and <150), and initial density(a decimal value >0 and <=1) separated by spaces: ";
  cin >> this->row;
  if (cin.fail() || this->row <=0) {
    cout << "Invalid input!\n";
    cin.clear();
    cin.ignore();
    exit(1);
  }
  cin >> this->column;
  if (cin.fail() || this->column <= 0) {
    cout << "Invalid input!\n";
    cin.clear();
    cin.ignore();
    exit(1);
  }
}
void GameOfLife::displayOption() {
  cout << "Please choose display option:\n(1) brief-pause between generations\n(2) press \"enter\" key to display next generation\n(3) output to text file\n";
  cin >> this->runOption; //only accept 1,2,3
  if(cin.fail() || (runOption != 1 && runOption != 2 && runOption != 3)) {
    cout << "Invalid input!\n";
    cin.clear();
    cin.ignore();
    exit(1);
  }
}
void GameOfLife::setOutFileName() {
  cout << "Enter output file name: \n";
  cin >> this->outFileName;
  if (cin.fail()) {
    cout << "Invalid input!\n";
    cin.clear();
    cin.ignore();
    exit(1);
  }
}
bool GameOfLife::simulationOver() { //checks if currentGen has no live cells or is the same as previous generation
  bool unchanged = true;
  bool empty = true;
  for (int i = 0; i < this->row; ++i) {
    for (int j = 0; j < this->column; ++j) {
      if (currentGen[i][j] != modifiedGen[i][j]) {
        unchanged = false;
      }
      if (currentGen[i][j] != '-') {
        empty = false;
      }
    }
  }
  return (unchanged || empty);
}
void GameOfLife::setCell(int row, int column, int neighbors) {  //behavior as defined by the specifications of the assignment
  if (neighbors < 2 || neighbors > 3) {
    modifiedGen[row][column] = '-';
  }
  else if (neighbors == 2) {
    modifiedGen[row][column] = currentGen[row][column];
  }
  else if (neighbors == 3) {
    modifiedGen[row][column] = 'X';
  }
}

void GameOfLife::checkNeighbors() { //check neighbors for classic mode
  int neighbors = 0;
  for (int i = 0; i < this->row; ++i) {
    for (int j = 0; j < this -> column; ++j) { //iterate through entire grid of currentGen
      neighbors = 0;
      for (int m = i-1; m <= i+1; ++m) {  //checking the neighboring cells
        for (int n = j-1; n <= j+1; ++n) {
          if (m == -1 || m == this->row || n == -1 || n == this->column) {} //out of bounds
          else if (m==i && n ==j){} //ignore cell under scrutiny
          else {
            if (currentGen[m][n] == 'X') {
              neighbors++;
            }
          }
        }
      }
      this->setCell(i,j,neighbors);
    }
  }
}

void GameOfLife::checkNeighborsMirror() {     //checks neighbors for mirror mode
  int neighbors = 0;
  for (int i = 0; i < this -> row; ++i) {
    for (int j = 0; j < this -> column; ++j) {
      neighbors = 0;
      for (int m = i-1; m <= i+1; ++m) {
        for (int n = j-1; n <= j+1; ++n) {
          if(m == i && n == j) {} //ignore cell under scrutiny
          else if (currentGen[((m==-1||m==this->row) ? (abs(m)-1) : m)][((n==-1||n==this->column) ? (abs(n)-1) : n)] == 'X') {  //credit to Matt Raymond for point out that abs() can be used to minimize mirror mode logic
            neighbors++;
          }
        }
      }
      this->setCell(i,j,neighbors);
    }
  }
}
void GameOfLife::checkNeighborsDoughnut() { //checks neighbors for doughnut mode
  int neighbors = 0;
  for (int i = 0; i < this->row; ++i) {
    for (int j = 0; j < this->column; ++j) {
      neighbors = 0;
      for (int m = i-1; m <= i+1; ++m) {
        for (int n = j-1; n <= j+1; ++n) {
          if (m == i && n == j) {}
          else if (currentGen[(m + this->row)%this->row][(n + this->column)%this->column] == 'X') { //since doughnut mode wraps around, behavior can be generalized for every cell in currentGen
            neighbors++;
          }
        }
      }
      this->setCell(i, j, neighbors);
      }
    }
  }
string GameOfLife::printCurrentGen() {  //returns currentGen as a string
  string temp = "";
  for (int j = 0; j < this->row; ++j) {
    for (int k = 0; k < this->column; ++k) {
    temp += this->currentGen[j][k];
    }
    temp+= "\n";
  }
  return temp;
}
void GameOfLife::run() {  //put everything here together to run the game of life simulation
  int count = 0;  //keep track of generations
  bool endSim = false; //check to see if simulation should end
  ofstream ostream; //declare and ofstream object;
  int stable = 0; //keep track of stability condition
  int stablerepeat = 0; //keep a counter for repeated oscillation
  if (runOption == 3) {
    ostream.open((this->outFileName),std::fstream::app);
    ostream << "Generation: " << count++ << endl;
    ostream << this->printCurrentGen();
    ostream << "\n--------------------------------------------------------------------------------\n--------------------------------------------------------------------------------\n";
  }
  else {
    cout << string(75, '\n'); //append new lines to console output to clear screen between generations
    cout << "Generation: " << count++ << endl;
    cout << this->printCurrentGen();
  }
  if (mode == 1) {    //required to intialize modifiedGen;
    this->checkNeighbors();
  }
  else if (mode == 2) {
    this->checkNeighborsMirror();  //required to intialize modifiedGen;
  }
  else if (mode == 3) {
    this->checkNeighborsDoughnut();  //required to intialize modifiedGen;
  }
  switch (runOption) {
    case 1:   //short pauses between generations.
      while(!endSim) {
        unsigned int microseconds = DELAY;
        usleep(microseconds);
        for (int i = 0; i < this->row; ++i) {
          for (int j = 0; j < this->column; ++j) {
            currentGen[i][j] = modifiedGen[i][j]; //update currentGen to next generation
          }
        }
        cout << string(75, '\n'); //append new lines to console output to clear screen between generations
        cout << "Generation: " << count++ << endl;
        cout << this->printCurrentGen();
        if (mode == 1) {
          this->checkNeighbors();
        }
        else if (mode == 2) {
          this->checkNeighborsMirror();
        }
        else if (mode == 3) {
          this->checkNeighborsDoughnut();
        }
        if (count >= GENERATION_TO_TERMINATE_PROGRAM) { //termination condition
          endSim = true;
          break;
        }

        for (int i = 0; i < this->row; ++i) {
          for (int j = 0; j < this->column; ++j) {
            stabilityCheck[stable][i][j] = currentGen[i][j];
          }
        }
        stable++;
        stable = stable % 7;

        if (count > 7) {
          bool boole = false;
          bool boole2 = false;
          for (int m = 0; m < this->row; ++m) {
            for (int n = 0; n < this->column; ++n) {
              if (stabilityCheck[stable][m][n] != stabilityCheck[(stable+2)%7][m][n]) { //check for oscillation of every other generation
                boole = true;
              }
              if (stabilityCheck[stable][m][n] != stabilityCheck[(stable+6)%7][m][n]) { //check for oscillation of every 6 generations
                boole2 = true;
              }
            }
          }
          if (!(boole && boole2)) {
            stablerepeat++;
          }
          if (stablerepeat > NUMBER_OF_OSCILLATIONS_BEFORE_TERMINATION)  //output up to a specified number of repeating oscillations before ending program
          {
            endSim = true;  //termination condition
          }
        }

        if (!endSim) {
          endSim = this->simulationOver();
        }
      }
      break;
    case 2:   //press enter for next frame
      while(!endSim) {
        while(cin.get()!='\n') {} //wait for user to press enter
        for (int i = 0; i < this->row; ++i) {
          for (int j = 0; j < this->column; ++j) {
            currentGen[i][j] = modifiedGen[i][j]; //update currentGen
          }
        }
        cout << string(75, '\n'); //append new lines to console output to clear screen between generations
        cout << "Generation: " << count++ << endl;
        cout << this->printCurrentGen();
        if (mode == 1) {
          this->checkNeighbors();
        }
        else if (mode == 2) {
          this->checkNeighborsMirror();
        }
        else if (mode == 3) {
          this->checkNeighborsDoughnut();
        }
        if (count >= GENERATION_TO_TERMINATE_PROGRAM) {
          endSim = true;  //termination condition
          break;
        }

        for (int i = 0; i < this->row; ++i) {
          for (int j = 0; j < this->column; ++j) {
            stabilityCheck[stable][i][j] = currentGen[i][j];
          }
        }
        stable++;
        stable = stable % 7;

        if (count > 7) {
          bool boole = false;
          bool boole2 = false;
          for (int m = 0; m < this->row; ++m) {
            for (int n = 0; n < this->column; ++n) {
              if (stabilityCheck[stable][m][n] != stabilityCheck[(stable+2)%7][m][n]) { //check for oscillation of every other generation
                boole = true;
              }
              if (stabilityCheck[stable][m][n] != stabilityCheck[(stable+6)%7][m][n]) { //check for oscillation of every 6 generations
                boole2 = true;
              }
            }
          }
          if (!(boole && boole2)) {
            stablerepeat++;
          }
          if (stablerepeat > NUMBER_OF_OSCILLATIONS_BEFORE_TERMINATION)  ///output up to a specified number of repeating oscillations before ending program
          {
            endSim = true;
          }
        }

        if(!endSim) {
          endSim = this->simulationOver();
        }
      }
      break;
    case 3:   //output to external file
      endSim = false;
      while (!endSim) {
        for (int i = 0; i < this->row; ++i) {
          for (int j = 0; j < this->column; ++j) {
            currentGen[i][j] = modifiedGen[i][j];
          }
        }
        ostream << "Generation: " << count++ << endl;
        ostream << this -> printCurrentGen();
        ostream << "\n--------------------------------------------------------------------------------\n--------------------------------------------------------------------------------\n";

        if (mode == 1) {
          this->checkNeighbors();
        }
        else if (mode == 2) {
          this->checkNeighborsMirror();
        }
        else if (mode == 3) {
          this->checkNeighborsDoughnut();
        }
        if (count >= GENERATION_TO_TERMINATE_PROGRAM) { //termination condition
          endSim = true;
          break;
        }
        for (int i = 0; i < this->row; ++i) {
          for (int j = 0; j < this->column; ++j) {
            stabilityCheck[stable][i][j] = currentGen[i][j];
          }
        }
        stable++;
        stable = stable % 7;

        if (count > 7) {
          bool boole = false;
          bool boole2 = false;
          for (int m = 0; m < this->row; ++m) {
            for (int n = 0; n < this->column; ++n) {
              if (stabilityCheck[stable][m][n] != stabilityCheck[(stable+2)%7][m][n]) { //check for oscillation of every other generation
                boole = true;
              }
              if (stabilityCheck[stable][m][n] != stabilityCheck[(stable+6)%7][m][n]) { //check for oscillation of every 6 generations
                boole2 = true;
              }
            }
          }
          if (!(boole && boole2)) {
            stablerepeat++;
          }
          if (stablerepeat > NUMBER_OF_OSCILLATIONS_BEFORE_TERMINATION)  //output up to a specified number of repeating oscillations before ending program
          {
            endSim = true;
          }
        }
        if (!endSim) {
          endSim = this->simulationOver();
        }
      }
      break;
    default:
      cout << "invalid option!\n";
      exit(1);
    }
    cout << "Simulation has ended.\n";
    ostream << "Simulation has ended.\n";
    ostream.close();
    cout << "Press enter to exit the program: ";
    while(cin.get()!='\n') {} //wait for user to press enter
}
GameOfLife::~GameOfLife() { //deconstructor for deallocation of memory
  for (int i = 0; i < 7; ++i) {
    for (int j = 0; j < this->row; ++j) {
      delete[] this->stabilityCheck[i][j];
    }
    delete[] this->stabilityCheck[i];
  }
  for(int k = 0; k < this->row; ++k) {
    delete[] this->currentGen[k];
    delete[] this->modifiedGen[k];

  }
  delete[] this->stabilityCheck;
  delete[] this->currentGen;
  delete[] this->modifiedGen;
}
