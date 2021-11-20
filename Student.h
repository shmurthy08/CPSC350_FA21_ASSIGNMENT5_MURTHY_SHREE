/*
 * Shree Murthy
 * 2374658
 * shmurthy@chapman.edu
 * CPSC 350-03
 * Assignment 5 
 **/


#ifndef STUDENT_H
#define STUDENT_H
#include <iostream>


using namespace std;
class Student{
    public:
        Student(); //default constructor
        Student(int timeNecessary); //constructor given a specfic time needed
        ~Student(); //destructor
        void decrementTimeServiced();//increment the timeServiced variable 
        int getTimeNeeded(); //get the time a student needs

    private:
        int timeNeeded; //time necessary at the window
};


#endif