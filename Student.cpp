/*
 * Shree Murthy
 * 2374658
 * shmurthy@chapman.edu
 * CPSC 350-03
 * Assignment 5 
 **/




#include "Student.h"

//default constructor
Student::Student(){
    timeNeeded = 0;
}

/** overloaded constructor
 * param: int timeNecessary representing the time needed at a window
 */
Student::Student(int timeNecessary){
    timeNeeded = timeNecessary;
}
//default destructor
Student::~Student(){

}

/** return the time needed at the window
 * return: int of the time needed at the window
 */
int Student::getTimeNeeded(){
    return timeNeeded;
}

/** Decremement the time at the window
 */
void Student::decrementTimeServiced(){
    --timeNeeded;
}

