/*
 * Shree Murthy
 * 2374658
 * shmurthy@chapman.edu
 * CPSC 350-03
 * Assignment 5 
 **/

#ifndef WINDOW_H
#define WINDOW_H

#include <iostream>
#include <exception>
#include "GenLinkedList.h"
using namespace std;

//time idle and is occupied
class Window{
    public:
        Window(); //default constructor
        Window(int numWindow); //number of windows that will be open
        ~Window(); //default destructor
        bool isWindowBusy(int pos); //return if window is busy or not 
        bool allWindowsBusy(); //are all the windows busy
        void setToBusy(int pos); //set a window to busy
        void setToNotBusy(int pos); //set a window to busy
        bool atLeastOneBusy(); //is at least one window free
    private:
        int numWindows; //number of windows for the simulation
        int idleTime; //how long was a window idle
        bool isBusy; //is a window busy
        Window* *stats; //array of window information         
        
};




#endif