/*
Name:                   Jin Jung
Student ID:             2329401
Email:                  jijung@chapman.edu
Course no. & Section:   CS350-02
Assignment:             2
*/

//there will also be two child classes GameOfLife_Mirror and GameOfLife_Torus
/*
  Class invariant:
*/

#ifndef GAMEOFLIFE_H
#define GAMEOFLIFE_H

#include <iostream>
#include <fstream>
#include <cstdlib> //for rand()
//#include <cmath>
//#include <ctime>
#include <unistd.h>
//#include <string>

using namespace std;

const unsigned int DELAY = 2000000;

class GameOfLife {
public:
  GameOfLife(string filelocation);  //read file from constructor.
  //GameOfLife(); //generate new simulation prompt user for desired world specs

  void run(); //3 options: output to file, frame by frame, pause between frames output generation number each frame

  void printCurrentGen();
  //double popCell() //(RAND_MAX - rand()) / static_cast<double>(RAND_MAX) <= userSuppliedDecVal
  void checkNeighbors(); //iterative through every cell
  bool simulationOver(); //compare two generations and if all cells are same, return true. Also check if empty, then return true
  void setCell(int row, int column, int neighbors); //determines modifiedGen based on neighbors of each cell
  ~GameOfLife(); //need to deallocate dynamically allocated memory.



private:
  //int gameMode; classic doughnut mirror only if inheritance not implemented
//  char** modifiedCondition; //analyze currentGen, and modify accordingly.
  int row;
  int column;
  char** currentGen; //start with currentGen, read its info and use that to populate each cell in modified Gen.
  char** tempGen; //we need to compare modifiedGen with tempGen to see if world has stabilized
  char** modifiedGen;
  int runOption; //frame, pause, or output to file
};



#endif /*GAMEOFLIFE_H*/
