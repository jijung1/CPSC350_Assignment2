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
  this->modifiedGen = new char* [this -> row]; //this will become currentGen if simulationOver() == false

  for (int i = 0; i < this->row; ++i) {   //dynamically allocate memory for 2-d array
    currentGen[i] = new char[this->column];
    modifiedGen[i] = new char[this->column];
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

GameOfLife::GameOfLife() {
  //ask for grid size, dimensions, and decimal number
  cout << "Please enter the number of rows: ";
  cin >> this->row;
  cout << "\nPlease enter the number of columns: ";
  cin >> this->column;

  //run behavior frame by frame, pauses, or output to file
}

bool GameOfLife::simulationOver() {
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
  for (int i = 0; i < this->row; ++i) {
    for (int j = 0; j < this->column; ++j) {
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
        //cout << "modifiedGen [" << i << "][" << j << "]: " << modifiedGen[i][j] << endl;
      }
      if (i == 0 && j == this->column-1) {  //top right corner
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
          //cout << "modifiedGen [" << i << "][" << j << "]: " << modifiedGen[i][j] << endl;
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
        //cout << "modifiedGen [" << i << "][" << j << "]: " << modifiedGen[i][j] << endl;
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
        //cout << "modifiedGen [" << i << "][" << j << "]: " << modifiedGen[i][j] << endl;
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
        //cout << "modifiedGen [" << i << "][" << j << "]: " << modifiedGen[i][j] << endl;
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
        //cout << "modifiedGen [" << i << "][" << j << "]: " << modifiedGen[i][j] << endl;
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
        //cout << "modifiedGen [" << i << "][" << j << "]: " << modifiedGen[i][j] << endl;
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
        //cout << "modifiedGen [" << i << "][" << j << "]: " << modifiedGen[i][j] << endl;
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
        //cout << "modifiedGen [" << i << "][" << j << "]: " << modifiedGen[i][j] << endl;
      }
    }
  }
}

void GameOfLife::printCurrentGen() {
  for (int j = 0; j < this->row; ++j) {
    for (int k = 0; k < this->column; ++k) {
    cout << this->currentGen[j][k];
    }
    cout << endl;
  }
}


void GameOfLife::run() {    //where the magic happens. hardest part... that's what she said. -michael scott
  int count = 0;
  cout << string(45, '\n'); //makes for a less stuttery display than system("clear");
  cout << "Generation: " << count++ << endl;
  this->printCurrentGen();
  this->checkNeighbors(); //generate modified generation
  switch (runOption) {
    case 1:   //short pauses between generations.
      while(!simulationOver()) {
        unsigned int microseconds = DELAY;
        usleep(microseconds);
        for (int i = 0; i < this->row; ++i) {
          for (int j = 0; j < this->column; ++j) {
            currentGen[i][j] = modifiedGen[i][j];
          }
        }
        cout << string(45, '\n');
        cout << "Generation: " << count++ << endl;
        this->printCurrentGen();
        this->checkNeighbors();
      }
      break;
    case 2:   //press enter for next frame
      while(!simulationOver()) {
        while(cin.get()!='\n') {}
        for (int i = 0; i < this->row; ++i) {
          for (int j = 0; j < this->column; ++j) {
            currentGen[i][j] = modifiedGen[i][j];
          }
        }
        // cout << string(45, '\n');
        system("clear");
        cout << "Generation: " << count++ << endl;
        this->printCurrentGen();
        this->checkNeighbors();
      }

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
    delete[] modifiedGen[i];
  }
  delete[] currentGen;
  delete[] modifiedGen;
}
