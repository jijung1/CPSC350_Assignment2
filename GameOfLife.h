/*
Name:                   Jin Jung
Student ID:             2329401
Email:                  jijung@chapman.edu
Course no. & Section:   CS350-02
Assignment:             2
*/

/*
  Class invariant: Every instance of this class will have int row, int column, char*** stabilityCheck, char** currentGen, char** modifiedGen, int runOption, int mode, and string outFileName.
*/

#ifndef GAMEOFLIFE_H
#define GAMEOFLIFE_H

#include <iostream>
#include <fstream>
#include <cstdlib> //for rand()
#include <unistd.h> //for usleep() pause function
using namespace std;

const unsigned int DELAY = 120000;  //specify delay for pauses between program.
const int GENERATION_TO_TERMINATE_PROGRAM = 1000; //default termination point
const int NUMBER_OF_OSCILLATIONS_BEFORE_TERMINATION = 5; //number of allowed repetitions of oscillating pattern

class GameOfLife {
public:
  GameOfLife(string filelocation, int mode);  //read file from constructor.
  GameOfLife(int mode); //generate new simulation prompt user for desired world specs
  void run(); //3 options: output to file, frame by frame, pause between frames output generation number each frame
  string printCurrentGen(); //returns currentGen
  void setOutFileName();
  void allocateMemory(int row, int column);
  void readInput();
  void displayOption();
  void checkNeighbors(); //iterate through every cell
  void checkNeighborsMirror();// mirror mode cell iteration
  void checkNeighborsDoughnut();
  bool simulationOver(); //compare two generations and if all cells are same, return true. Also check if empty, then return true
  void setCell(int row, int column, int neighbors); //determines modifiedGen based on neighbors of each cell
  ~GameOfLife(); //need to deallocate dynamically allocated memory.
protected:
  int row;
  int column;
  char*** stabilityCheck; //3-d array used to store multiple generations to compare oscillation cases
  char** currentGen; //start with currentGen, read its info and use that to populate each cell in modified Gen.
  char** modifiedGen;
  int runOption; // 1= frame-by-frame, 2 = pause until enter, 3 = output to file
  int mode; //1 = classic, 2 = mirror, 3 = doughnut
  string outFileName;
};

#endif /*GAMEOFLIFE_H*/
