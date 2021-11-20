/*
 * Shree Murthy
 * 2374658
 * shmurthy@chapman.edu
 * CPSC 350-03
 * Assignment 5 
 **/

#include "Window.h"


//default constructor
Window::Window(){
    isBusy = false;
}
//number of windows that will be open
Window::Window(int numWindow){
    numWindows = numWindow;
    isBusy = false;
    stats = new Window*[numWindows];
    for(int i = 0; i < numWindow; ++i){
        stats[i] = new Window();
        
    }
}
//default destructor 
Window::~Window(){
    delete [] stats;
}


/** checks if a specific window is busy
 * param: int pos representing the position that we need to check
 * return: bool if the window is busy
 */
bool Window::isWindowBusy(int pos){
    return stats[pos]->isBusy;
}


/** Set a specfic window to  busy
 * param: int pos representing the position that will be set to true
 */
void Window::setToBusy(int pos){
    stats[pos]->isBusy = true;
}

/** Set a specfic window to not busy
 * param: int pos representing the position that will be set to false
 */
void Window::setToNotBusy(int pos){
    stats[pos]->isBusy = false;
}

/** Checks if all windows are busy
 * return bool if all windows are busy
 */
bool Window::allWindowsBusy(){
    for(int i = 0; i < numWindows; ++i){
        if(stats[i]->isBusy == false){
            return false;
        }
    }
    return true;
}

/** Checks if at least one window is busy
 * return bool that will return true if at least one window is busy
 */
bool Window::atLeastOneBusy(){
    for(int i = 0; i < numWindows; ++i){
        if(stats[i]->isBusy == true){
            return true;
        }
    }
    return false;
}
