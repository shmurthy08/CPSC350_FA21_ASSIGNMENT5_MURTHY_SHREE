/*
 * Shree Murthy
 * 2374658
 * shmurthy@chapman.edu
 * CPSC 350-03
 * Assignment 5 
 **/



#include "Simulation.h"

/** Default constructor given name of a file
* param: string file representing name of the file
*/
Simulation::Simulation(string file){
    fp = new FileProcessor(file);
    clockTick = 0;
    idleTime = 0;
    fileName = file;
    studentWaitTimes = new GenLinkedList<int>();

    
}

//default destructor
Simulation::~Simulation(){
    delete fp;
    delete studentWaitTimes;
    delete window;
    
}

/** Handles setup process (i.e number of windows)
*/
void Simulation::setup(){
    //if we reached this method then the file given was a valid one 
    ifstream inFile(fileName);
    int windowsNeeded;
    string line;
    getline(inFile, line);
    windowsNeeded = stoi(line);
    windowsOpen = windowsNeeded;
    window = new Window(windowsNeeded); //create Window object of x windows
    
    
}

/** Run everything regarding the simulation
*/
void Simulation::run(){
    try{
        //intially check if the file is a valid file before proceeding
        if(fp->validFile()){
            setup(); //setup the window information
            
            ifstream inFile(fileName);
            string line;
            //skip the first line (windows open line parsed in the setup method)
            getline(inFile, line);

            //set the first clock tick when students arrive
            getline(inFile, line);
            clockTick = stoi(line);
            

            GenQueue<Student*> *st = new GenQueue<Student*>(); //queue to hold the students
            Student* *windows = new Student*[windowsOpen]; //array that holds students
            waitTime = new GenLinkedList<int>(); //holds the window idle information
            GenLinkedList<int> *stWaitTimes = new GenLinkedList<int>(); //list holding student's time waiting in line
            int *isWindowAboveFive = new int[windowsOpen]; //set the position to 1 if the window's idle time is > 5
            int *windowIdle = new int[windowsOpen]; //holds the idle time of a window at any given point

            int studentsComing; //variable accounts for how many students will be arriving to the line
            int tempClockTick = 0; //variable that tracks every minute
            int timeNeeded; //how many minutes will a student require at the window
            while(true){ 
                
                if(tempClockTick != clockTick){
                    ++tempClockTick; //increment the clockTick
                    //if any window is not busy then incremement its idle time
                    for(int i = 0; i < windowsOpen; ++i){
                        if(window->isWindowBusy(i) == false){
                            windowIdle[i]++;
                            if(windowIdle[i] > 5){
                                isWindowAboveFive[i] = 1;
                            }
                        }
                        
                    }
                    //increment student waiting in line variable
                    if(st->getSize() > 0){
                        ++idleTime;
                    }
                    //decerement the students in the window time
                    int tempIdle = 0;
                    for(int i = 0; i < windowsOpen; ++i){
                        //if all the windows are busy
                        if(window->allWindowsBusy()){
                            windows[i]->decrementTimeServiced();
                            //if any students are ready to be removed and the queue has a size > 0
                            if(windows[i]->getTimeNeeded() == 0 && st->getSize() > 0){
                                tempIdle = idleTime;
                                windows[i] = NULL;
                                windows[i] = st->pop();
                                window->setToBusy(i);
                            }
                            //the queue is empty so just empty the spot
                            else if(windows[i]->getTimeNeeded() == 0){
                                windows[i] = NULL;
                                window->setToNotBusy(i);
                            }
                        }
                        else{
                            //if the window is busy then decrement the students time at window and update windows with new students in the queue
                            if(windows[i] != NULL){
                                windows[i]->decrementTimeServiced();
                                if(windows[i]->getTimeNeeded() == 0 && st->getSize() > 0){
                                    tempIdle = idleTime;
                                    windows[i] = NULL;
                                    windows[i] = st->pop();
                                    window->setToBusy(i);
                                }
                                else if(windows[i]->getTimeNeeded() == 0){
                                    windows[i] = NULL;
                                }
                            }
                            if(tempIdle > 0){
                                stWaitTimes->insertTail(tempIdle);
                                tempIdle = 0;
                            }
                            
                        }
                    }
                    
                    //after doing any removals necessary check if there are open spots and then insert new students into the windows
                    if(!window->allWindowsBusy()){
                        int i = 0;
                        while(st->getSize() > 0){
                            
                            windows[i] = st->pop();
                            window->setToBusy(i);
                            waitTime->insertTail(windowIdle[i]);
                            if(isWindowAboveFive[i] != 1 && windowIdle[i] > 5){
                                isWindowAboveFive[i] = 1;
                            }
                            windowIdle[i] = 0;
                            
                            ++i;
                        }
                    }
                    
                   
                }
                else{
                    inFile >> studentsComing; //how many students are incoming
                    //while we parse those students in add them to the queue
                    while(studentsComing != 0){
                        inFile >> timeNeeded;
                        st->push(new Student(timeNeeded));
                        --studentsComing;
                    }

                    int i = 0;
                    while(!window->allWindowsBusy() && i < windowsOpen){
                        if(!window->isWindowBusy(i) && st->getSize() > 0){
                            windows[i] = st->pop(); //update window with new student
                            window->setToBusy(i); //window is now busy
                            waitTime->insertTail(windowIdle[i]); //insert the window's idle time
                            //if the idle time is above 5 min
                            if( isWindowAboveFive[i] != 1 && windowIdle[i] > 5){
                                isWindowAboveFive[i] = 1;
                            }
                            windowIdle[i] = 0; //reset the window's idle time since it's busy
                            stWaitTimes->insertTail(0); //student didn't wait in line so insert a 0
                           

                            
                        }
                        ++i;
                    }

                    //we have now parsed all the lines prior to the next clock tick...update clocktick
                    inFile >> clockTick;
                    //check if you reached the end of the file
                    if(inFile.eof()){
                        break;
                    }
        
                }     

            }
            
            //after the file has been read continue the simulation if the windows are still in use
            while(window->atLeastOneBusy()){
                //if the window is busy increment its idle time
                for(int i = 0; i < windowsOpen; ++i){
                    if(window->isWindowBusy(i) == false){
                        windowIdle[i]++;
                        if(windowIdle[i] > 5){
                            isWindowAboveFive[i] = 1;
                        }
                    }
                    
                }
                //update student's idle time in line
                if(st->getSize() > 0){
                    ++idleTime;
                }
                int tempIdle = 0;
                for(int i = 0; i < windowsOpen; ++i){
                    
                    if(windows[i] != NULL && windows[i]->getTimeNeeded() > 0 ){
                        windows[i]->decrementTimeServiced(); //decrement the student's time at the window
                    }
                    if(!window->isWindowBusy(i) && st->getSize() > 0){
                            windows[i] = st->pop(); //update window with next guest
                            window->setToBusy(i); //window is now busy
                            waitTime->insertTail(windowIdle[i]); //insert the window idle value
                            //if the idle time is above 5 min
                            if( isWindowAboveFive[i] != 1 && windowIdle[i] > 5){
                                isWindowAboveFive[i] = 1;
                            }
                            windowIdle[i] = 0; //reset the window idle time
                            
                    }
                    if(windows[i] != NULL && windows[i]->getTimeNeeded() == 0){
                        if(st->getSize() > 0){
                            tempIdle = idleTime; //store the idle time in the temp variable
                            windows[i] = NULL; //remove the student in the window
                            windows[i] = st->pop(); //update the window with the next guest
                            window->setToBusy(i); //window is busy
                        }
                        else{
                            windows[i] = NULL; //clear the array
                            window->setToNotBusy(i); //window is no longer busy


                        }
                        if(tempIdle > 0){
                            stWaitTimes->insertTail(tempIdle); //insert the time of student waiting in line
                            tempIdle = 0; //reset the temp variable
                        }

                    }
                    
                    
                    
                   
                }
                
                

            }
            //add any leftover window idle times
            for(int i = 0; i < windowsOpen; ++i){
                if(windowIdle[i] > 0){
                    waitTime->insertTail(windowIdle[i]);
                    windowIdle[i] = 0;
                }
            }
            
            
            printStats(waitTime, stWaitTimes, isWindowAboveFive); //print simulation stats
            

            //complete all deletes necessary
            delete st;
            delete isWindowAboveFive;
            delete [] windowIdle;
            delete [] windows;

        }
    }
    //if any error occurs catch and return it
    catch(runtime_error &e){
        cerr << e.what() << endl;
    }
}



/**
 * param: int *arrOverFive is an array pointer that holds a 1 depending on if a specific window ever had an idle time over five minutes
 * param: GenLinkedList<int> *windowIdles is a LinkedList that holds all the window's idle times
 * param: GenLinkedlist<int> *studentWait is a LinkedList that holds the student waiting in line values
 */
void Simulation::printStats(GenLinkedList<int> *windowIdles, GenLinkedList<int> *studentWait, int *arrOverFive){
    //sort the window idle times
    windowIdles->sort();
    //sorth the student wait times
    studentWait->sort();

    //find the mean of student wait time
    double mean = 0;
    cout << "STATS AFTER SIMULATION: " << endl;
    cout << "MEAN STUDENT WAIT TIME: ";
    for(int i = 0; i < studentWait->getSize(); ++i){
        mean += studentWait->find(i);
    }
    cout << mean/(studentWait->getSize()) << endl;
    
    //find the median student wait time
    cout << "MEDIAN STUDENT WAIT TIME: ";
    double median = 0;
    if(studentWait->getSize() % 2 == 0){
        median += studentWait->find(studentWait->getSize() / 2);
        median += studentWait->find((studentWait->getSize() / 2) + 1);
        median /= 2;
    }
    else{
        median = studentWait->find(studentWait->getSize() / 2);
    }
    cout << median << endl;

    //find the longest student wait time
    cout << "LONGEST STUDENT WAIT TIME: ";
    int max = studentWait->find(0);
    for(int i = 1; i < studentWait->getSize(); ++i){
        if(max < studentWait->find(i)){
            max = studentWait->find(i);
        }
    }
    cout << max << endl;

    //number of students waiting over 10 minutes
    cout << "NUMBER OF STUDENTS WAITING OVER 10 MINUTES: ";
    int waitOverTen = 0;
    for(int i = 0; i < studentWait->getSize(); ++i){
        if(studentWait->find(i) > 10){
            waitOverTen++;
        }
    }
    cout << waitOverTen << endl;

    //mean of the window idle times
    cout << "MEAN WINDOW IDLE TIME: ";
    mean = 0;
    for(int i = 0; i < windowIdles->getSize(); ++i){
        mean += windowIdles->find(i);
    }
    cout << mean / windowsOpen << endl;

    //longest idle time for a window
    cout << "LONGEST WINDOW IDLE TIME: ";
    max = windowIdles->find(0);
    for(int i = 1; i < windowIdles->getSize(); ++i){
        if(max < windowIdles->find(i)){
            max = windowIdles->find(i);
        }
    }
    cout << max << endl;

    //number of windows > 5
    cout << "NUMBER OF WINDOWS IDLE FOR MORE THAN FIVE MINUTES: ";
    int waitOverFive = 0;
    for(int i = 0; i < windowsOpen; ++i){
        if(arrOverFive[i] == 1){
            waitOverFive++;
        }
    }
    cout << waitOverFive << endl;
}