/*
 * Shree Murthy
 * 2374658
 * shmurthy@chapman.edu
 * CPSC 350-03
 * Assignment 5 
 **/


//Handle the file processing necessary for the simulation


#include "FileProcessor.h"

/**
 * param: given a file input set up the file processor
 */
FileProcessor::FileProcessor(string fileInput){
    fileName = fileInput;
}
//default destructor
FileProcessor::~FileProcessor(){

}

/** This will process the user's fileName file check if it exists
 * return: bool if the fileName file was found
 */
bool FileProcessor::processInputFile(){
    
    //Input file
    inFile.open(fileName);
    
   
    //Check if the fileName file is open to be read
    if(inFile.is_open()){
        //close the fileName file to avoid memory issues
        inFile.close();
        //close the output file to avoid memory issues
        //resultText.close();
        return true;
    }
    //if the file cannot be opened output this error
    else{
        return false;
    }



    
}


/** Checks if a file has proper inputs (i.e all integers)
 * return: validity of the file
 */
bool FileProcessor::validFile(){
    inFile.open(fileName);
    string line;
    getline(inFile, line);
    try{
        if(inFile.eof() != 0){ //if there is only 1 line in the file then end the 
            throw runtime_error("INVALID FILE: ONLY 1 LINE IN THE FILE");
            
        }
    }catch(runtime_error& e){
        cerr << e.what() << endl;
        return false;
    }
    while(getline(inFile, line)){
        istringstream iss(line);
        int number;
        try{
            if(iss >> number){
                continue;
            }
            else{
                throw runtime_error("INVALID FILE: PLEASE PROVIDE INTEGERS");
                
            }
        }catch(exception& e){
            cerr << e.what() << endl;
            return false;
        }
    
    }
    return true;
}