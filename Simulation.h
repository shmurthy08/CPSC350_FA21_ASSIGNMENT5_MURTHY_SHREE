/*
 * Shree Murthy
 * 2374658
 * shmurthy@chapman.edu
 * CPSC 350-03
 * Assignment 5 
 **/

#ifndef SIMULATION_H
#define SIMULATION_H

#include <iostream>
#include <exception>
#include <sstream>

#include "Student.h"
#include "GenQueue.h"
#include "FileProcessor.h"
#include "Window.h"

using namespace std;


class Simulation{
    public:
        Simulation(string file); //default constructor
        ~Simulation(); //default destructor
        void setup(); //setup all necessary file checking/information handling
        void run(); //run the simulation
        void printStats(GenLinkedList<int> *windowIdles, GenLinkedList<int> *studentWait, int *arrOverFive); //print all necessary stats of the simulation
    private:
        FileProcessor *fp; //stores the file information
        Window *window; //intialize how many windows are needed
        GenLinkedList<int> *waitTime; //linkedlist that stores the waitTimes of the windows
        GenLinkedList<int> *studentWaitTimes; //linkedList representing the number of windows and will hold student objects
        string fileName; //string holding the name of the file
        int clockTick; //increment the clock ticks
        int windowsOpen; //number of registars
        int idleTime; //student idle time
};

#endif