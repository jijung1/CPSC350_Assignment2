/*
Name:                   Jin Jung
Student ID:             2329401
Email:                  jijung@chapman.edu
Course no. & Section:   CS350-02
Assignment:             2
*/

/*
  Class invariant:
*/

#include "GameOfLife.h"

GameOfLife::GameOfLife(string filelocation) {
  string row = "";
  string column = "";

  ifstream istream(filelocation);

  getline(istream, row);
  getline(istream, column);
  this->row = stoi(row);
  this->column = stoi(column);
  cout << "row: " << this->row << "\ncolumn: "<< this->column<< endl;
  this->currentGen = new char*[this->row];
  this->tempGen = new char* [this->row];
  this->modifiedGen = new char* [this -> row]; //this will become currentGen if simulationOver() == false

  for (int i = 0; i < this->row; ++i) {   //dynamically allocate memory for 2-d array
    currentGen[i] = new char[this->column];
  }
  for (int j = 0; j < this->row; ++j) {
    string temp = "";
    getline(istream, temp);
    for (int k = 0; k < temp.length(); ++k) {   //initialize all cells with input file values
      currentGen[j][k] = temp[k];
    cout << currentGen[j][k];
    }
    cout << endl;
  }
  istream.close();

  cout << "Please choose display option:\n(1) brief-pause between generations\n(2) press \"enter\" key to display next generation\n(3) output to text file\n";
  cin >> this->runOption; //only accept 1,2,3
}
bool GameOfLife::simulationOver() {
  bool unchanged = true;
  bool empty = true;
  for (int i = 0; i < this->row-1; ++i) {
    for (int j = 0; j < this-> column-1; ++j) {
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
/*
GameOfLife::GameOfLife() {  //no file constructor

}
*/
void GameOfLife::setCell(int row, int column, int neighbors) {
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

void GameOfLife::checkNeighbors() {  //modifiedGen is determined here.
  int neighbors = 0;
  for (int i = 0; i < this->row-1; ++i) {
    for (int j = 0; j < this->column-1; ++j) {
      neighbors = 0;
      if (i == 0 && j == 0) { //top left corner
        if(currentGen[i][j+1] == 'X') {
          neighbors++;
        }
        if (currentGen[i+1][j] == 'X') {
          neighbors++;
        }
        if (currentGen[i+1][j+1] == 'X') {
          neighbors++;
        }
        this->setCell(i, j, neighbors);
        cout << "modifiedGen [" << i << "][" << j << "]: " << modifiedGen[i][j] << endl;
      }
      if (i == 0 && j == this->column-1) {  //top right corner
          if (currentGen[i][j-1] == 'X') {
            neighbors++;
          }
          if (currentGen[i+1][j-1] == 'X') {
            neighbors++;
          }
          if (currentGen[i-1][j] == 'X') {
            neighbors++;
          }
          this->setCell(i, j, neighbors);
          cout << "modifiedGen [" << i << "][" << j << "]: " << modifiedGen[i][j] << endl;
      }
      if (i == this->row-1 && j == 0) { //bottom left corner
        if (currentGen[i-1][j] == 'X') {
          neighbors++;
        }
        if (currentGen[i-1][j+1] == 'X') {
          neighbors++;
        }
        if (currentGen[i][j+1] == 'X') {
          neighbors++;
        }
        this->setCell(i, j, neighbors);
        cout << "modifiedGen [" << i << "][" << j << "]: " << modifiedGen[i][j] << endl;
      }
      if (i == this->row-1 && j == this->column-1) {  //bottom right corner
        if (currentGen[i-1][j-1] == 'X') {
          neighbors++;
        }
        if (currentGen[i-1][j] == 'X') {
          neighbors++;
        }
        if (currentGen[i][j-1] == 'X') {
          neighbors++;
        }
        this->setCell(i, j, neighbors);
        cout << "modifiedGen [" << i << "][" << j << "]: " << modifiedGen[i][j] << endl;
      }
      if (i == 0 && j != 0 && j != this->column-1) { //top edge
        if (currentGen[i][j-1] == 'X') {
          neighbors++;
        }
        if (currentGen[i+1][j-1] == 'X') {
          neighbors++;
        }
        if (currentGen[i+1][j] == 'X') {
          neighbors++;
        }
        if (currentGen[i+1][j+1] == 'X') {
          neighbors++;
        }
        if (currentGen[i][j+1] == 'X') {
          neighbors++;
        }
        this->setCell(i, j, neighbors);
        cout << "modifiedGen [" << i << "][" << j << "]: " << modifiedGen[i][j] << endl;
      }
      if (i == this->row-1 && j != 0 && j != this->column-1) { //bottom edge
        if (currentGen[i][j-1] == 'X') {
          neighbors++;
        }
        if (currentGen[i-1][j-1] == 'X') {
          neighbors++;
        }
        if (currentGen[i-1][j] == 'X') {
          neighbors++;
        }
        if (currentGen[i-1][j+1] == 'X') {
          neighbors++;
        }
        if (currentGen[i][j+1] == 'X') {
          neighbors++;
        }
        this->setCell(i, j, neighbors);
        cout << "modifiedGen [" << i << "][" << j << "]: " << modifiedGen[i][j] << endl;
      }
      if (i != 0 && i != this->row-1 && j == 0) { //left edge
        if (currentGen[i-1][j] == 'X') {
          neighbors++;
        }
        if (currentGen[i-1][j+1] == 'X') {
          neighbors++;
        }
        if (currentGen[i][j+1] == 'X') {
          neighbors++;
        }
        if (currentGen[i+1][j+1] == 'X') {
          neighbors++;
        }
        if (currentGen[i+1][j] == 'X') {
          neighbors++;
        }
        this->setCell(i, j, neighbors);
        cout << "modifiedGen [" << i << "][" << j << "]: " << modifiedGen[i][j] << endl;
      }
      if (i != 0 && i != this->row-1 && j == this->column-1) { //right edge
        if (currentGen[i-1][j] == 'X') {
          neighbors++;
        }
        if (currentGen[i-1][j-1] == 'X') {
          neighbors++;
        }
        if (currentGen[i][j-1] == 'X') {
          neighbors++;
        }
        if (currentGen[i+1][j-1] == 'X') {
          neighbors++;
        }
        if (currentGen[i+1][j] == 'X') {
          neighbors++;
        }
        this->setCell(i, j, neighbors);
        cout << "modifiedGen [" << i << "][" << j << "]: " << modifiedGen[i][j] << endl;
      }
      if (i != 0 && i != this->row-1 && j != 0 && j != this->column-1) { //middle
        for (int m = j-1; m <= j+1; ++m) {
          if (currentGen[i+1][m] == 'X') {
            neighbors++;
          }
          if (currentGen[i-1][m] == 'X') {
            neighbors++;
          }
        }
        if (currentGen[i][j-1] == 'X') {
          neighbors++;
        }
        if (currentGen[i][j+1] == 'X') {
          neighbors++;
        }
        this->setCell(i, j, neighbors);
        cout << "modifiedGen [" << i << "][" << j << "]: " << modifiedGen[i][j] << endl;
      }
    }
  }
}

void GameOfLife::printCurrentGen() {
  for (int j = 0; j < this->row-1; ++j) {
    string temp = "";
    for (int k = 0; k < this->column-1; ++k) {
    cout << currentGen[j][k];
    }
    cout << endl;
  }
}


void GameOfLife::run() {

// checkNeighbors(); //sets modifiedGen

  int count = 0;
  switch (runOption) {
    case 1:   //short pauses between generations.
      while(!simulationOver()) {
        cout << "Generation: " << count++ << endl;
        //void printCurrentGen();
        unsigned int microseconds = DELAY;
        usleep(microseconds);
      }
      break;
    case 2:
      //code for enter to move on to checkNeighbors
      break;
    case 3:
      //code to output to text file
      break;
    default:
      cout << "invalid option!\n";
      exit(1);
  }
  cout << "Simulation has ended.\n";
}
GameOfLife::~GameOfLife() {
  for(int i = 0; i < this->row; ++i) {
    delete[] currentGen[i];
  }
  delete[] currentGen;
}
