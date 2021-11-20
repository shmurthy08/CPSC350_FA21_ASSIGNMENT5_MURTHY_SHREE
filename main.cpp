/*
 * Shree Murthy
 * 2374658
 * shmurthy@chapman.edu
 * CPSC 350-03
 * Assignment 5 
 **/

//main method that handles user input

#include "Simulation.h"

using namespace std;

int main(int argc, char** argv){
    //Error checking: is a file provided or are too many arguments provided?
    if(argc == 1 || argc > 2){
        cout << "INVALID INPUT: FILE NOT PROVIDED OR TOO MANY ARGUMENTS PROVIDED" << endl;
    }
    else{
        Simulation *s = new Simulation(argv[1]);
        s->run();
        delete s;
    }

    
    




    return 1;
}