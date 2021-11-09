/*
 * Shree Murthy
 * 2374658
 * shmurthy@chapman.edu
 * CPSC 350-03
 * Assignment 5 
 **/

//Generic queue file

#ifndef GENQUEUE_H
#define GENQUEUE_H
#include <iostream>
#include <exception>
#include "GenLinkedList.h"

using namespace std;

template <typename T>
class GenQueue{

    public: 
        GenQueue(); //default constructor
        ~GenQueue(); //default destructor

        //core functions
        void push(T data); //push data onto the queue
        T pop(); //pop off the element on the top of the queue
        void insertPriQueue(T data); //priority queue insert

        //aux functions
        T peek(); //look at the first element in the queue
        unsigned int getSize(); //the size of the queue
        bool isEmpty(); //is the queue empty
    private:
        unsigned int mSize; //size of the queue
        GenLinkedList<T> *myQueue;

};


template <typename T>
/**
 * Default Constructor
 */
GenQueue<T>::GenQueue(){
    mSize = 0;
    myQueue = new GenLinkedList<T>();
}

template <typename T>
/**
 * Default Destructor
 */
GenQueue<T>::~GenQueue(){
    delete myQueue;
}

template <typename T>
/** Insert data to the front of the queue
 * param: data of any type representing the data to be inserted
 */
void GenQueue<T>::insert(T data){
    list->insertTail(data); //Follow the FIFO model so every node is added to the end of the LinkedList
    ++mSize; //increment size
    
}

template <typename T>
/** remove data to the front of the queue
 * return: data at the front of the queue
 */
T GenQueue<T>::pop(){
    //error checking
    if(isEmpty()){
        throw runtime_error("Queue is empty");
    }
    T data = myQueue->removeHead(); //pop the first element in the queue
    --mSize; //decrement size of queue
    return data;

}

template <typename T>
/** peek data at the front of the queue
 * return: data at the front of the queue
 */
T GenQueue<T>::peek(){
    //error check
    if(isEmpty()){
        throw runtime_error("EMPTY STACK!!!");
    }
    //peek at the data
    T data = list->removeHead();
    list->insertHead(data);
    return data;
}

// template <typename T>
// T GenQueue::insertPriQueue(T data){
//     if(isFull()){
//         throw runtime_error("priority queue is full!");

//     }
//     int i = numElements - 1;
//     while(i>=0 && data < myQueue[i]){
//         myQueue[i+1] = myQueue[i];
//         i--;
//     }
//     myQueue[i+1] = data;
//     numElements++;
// }

template <typename T>
/** Checks if the queue is empty
 * return: boolean T/F depending on the size of the queue
 */
bool GenQueue<T>::isEmpty(){
    return (mSize == 0);
}


template <typename T>
/** This method provides the size of the queue
 * return: int representing the size of the queue
 */
unsigned int GenQueue<T>::getSize(){
    return mSize;
}


#endif