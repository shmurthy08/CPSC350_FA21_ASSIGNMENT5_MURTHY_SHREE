/*
 * Shree Murthy
 * 2374658
 * shmurthy@chapman.edu
 * CPSC 350-03
 * Assignment 5 
 **/

//generic list class
 
#ifndef MYLIST_H
#define MYLIST_H


#include "GenLinkedList.h"

#include <iostream>

using namespace std;


template<typename T>
class List{
    public:
        virtual ~List(){} //destructor
        virtual void append(T objName) const=0; //add to the end
        virtual void prepend(T objName) const=0; //add to the front
        virtual T remove() const=0; //remove a node at a specfic position
        virtual int search(T objName) const=0; //search for a specific node and return the position
        virtual void print() const=0; //print from the head
        virtual void printReverse() const=0; //print from the tail
        virtual void sort() const=0; //sort in ascending order
        virtual bool isEmpty() const =0; //is the list empty
        virtual unsigned int getLength() const=0; //length of the list
};

template<typename T>
class MyList{
    public:
        MyList(); //constructor
        ~MyList(); //destructor
        void append(T objName); //add to the end
        void prepend(T objName); //add to the front
        T remove(); //remove a node at a specific position
        int search(T objName); //search for a specific node and return the position
        void print(); //print from the head
        void printReverse(); //print from the tail
        void sort(); //sort in ascending order
        bool isEmpty(); //is the list empty
        unsigned int getLength();  //length of the list
    private:
        GenLinkedList<T> *LinkList;
};

template<typename T>
/**
 * Default constructor
 */
MyList<T>::MyList(){
    LinkList = new GenLinkedList<T>();
}

template<typename T>
/**
 * Default Destructor
 */
MyList<T>::~MyList(){
    delete LinkList;
}


template<typename T>
/** Append an object to the end of the list
 * param: T objName representing the object to be inserted
 */
void MyList<T>::append(T objName){
    LinkList->insertTail(objName);
}

template<typename T>
/** Prepend an object to the front of the list
 * param: T objName representing the object to be inserted
 */
void MyList<T>::prepend(T objName){
    LinkList->insertHead(objName);
}

template<typename T>
/** Remove an object from the list given a specific position
 * param: int pos representing the position of the list to remove
 */
T MyList<T>::remove(){
    return LinkList->removeHead();
}

template<typename T>
/** Find a specific object and return the position of the 
 * param: T objName representing the object to search for 
 */
int MyList<T>::search(T objName){
    return LinkList->find(objName);
}

template<typename T>
/** Print out the entire list
 */
void MyList<T>::print(){
    LinkList->print();
}

template<typename T>
/** Print the list in reverse
*/
void MyList<T>::printReverse(){
    LinkList->printReverse();
}

template<typename T>
/** sort the list in ascending order
 */
void MyList<T>::sort(){
    LinkList->sort();
}


template<typename T>
/** Checks if the list is empty
 * return: bool representing if the list is empty
 */
bool MyList<T>::isEmpty(){
    return LinkList->isEmpty();
}

template<typename T>
/** Get the length of the list
 * return: unsigned int representing the size of the list
 */
unsigned int MyList<T>::getLength(){
    return LinkList->getSize();
}

#endif