/*
 * Shree Murthy
 * 2374658
 * shmurthy@chapman.edu
 * CPSC 350-03
 * Assignment 5 
 **/
 
#ifndef FILEPROCESSOR_H
#define FILEPROCESSOR_H

#include <iostream>
#include <exception>
#include <fstream>
#include <sstream>

using namespace std;


//Class to handle all file processing
class FileProcessor{

    public:
        FileProcessor(string fileInput); //default constructor
        ~FileProcessor(); //default destructor
        bool processInputFile(); //void method that will read from a file
        bool validFile(); //check if file is valid

    private: 
        string fileName; //store the name of the file
        ifstream inFile; //stream to read file
};




#endif