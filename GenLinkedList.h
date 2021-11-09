/*
 * Shree Murthy
 * 2374658
 * shmurthy@chapman.edu
 * CPSC 350-03
 * Assignment 5 
 **/


//generic linkedList file

#ifndef GENLINKEDLIST_H
#define GENLINKEDLIST_H


#include <iostream>
#include <exception>

using namespace std;

template <typename T>
class ListNode{
    public:
        ListNode(); //default constructor
        ListNode(T d); //default overloaded constructor
        ~ListNode(); //default destructor
        ListNode<T>* next; //a pointer that points to the next node in the list
        ListNode<T>* prev; //a pointer that points to the previous node in the list
        T data; //data that can store any type

};

template <typename T>
/**
 * Default constructor
 */
ListNode<T>::ListNode(){
    data = NULL;
    next = NULL;
    prev = NULL;
}

template <typename T>
/** Overloaded constructor that updates the data member variable
 * param: type T data representing the data that will be stored in the node
 */
ListNode<T>::ListNode(T d){
    data = d;
    next = NULL;
    prev = NULL;
}

template <typename T>
/**
 * Default destructor
 */
ListNode<T>::~ListNode(){
    delete next;
    delete prev;
}

template <typename T>
class GenLinkedList{
    public:
        GenLinkedList(); //general LinkedList
        ~GenLinkedList(); //destructor for LinkedList

        void insertHead(T d); //insert data at the head of the list
        void insertTail(T d); //insert data at the Tail of the list
        T removeHead(); //remove at the head and return the data
        T removeTail(); //remove at the tail and return the data
        T removeNode(T value); //find and remove a specific node and return the data
        int find(T value); //find a specfic value and return that data


        bool isEmpty(); //check if the LinkedList is empty
        unsigned int getSize(); //get the size of the LinkedList


    private:
        ListNode<T>* head; //node pointing to the head of the list
        ListNode<T>* tail; //node pointing to the tail of the list
        unsigned int size; //size of the LinkedList
    

};

/** A default constructor that sets size to 0 and head/tail to NULL
 */
template <typename T>
GenLinkedList<T>::GenLinkedList(){
    size = 0;
    head = NULL;
    tail = NULL;
}

/** A default destructor that loops thru the LinkedList and deletes every node
 */
template <typename T>
GenLinkedList<T>::~GenLinkedList(){
    //curr temp node that starts at the head (this will do the deletion)
    ListNode<T>* current = head;
    //a nxt temp node that will store the next node in the LinkedList that will be deleted on the next iteration
    ListNode<T>* nxt = current;
    //iterate while current hasn't reached the end
    while( current != NULL) {
        //update next to the next node in the list to be deleted
        nxt = nxt->next;
        //delete the curr node
        delete current;
        //update curr with the next node in the list
        current = nxt;
    }
   delete nxt;
}

template <typename T>
/** A method that inserts a new head into the linked list 
 * Parm: represents the data to be inserted (it can be any type of data)
 */
void GenLinkedList<T>::insertHead(T d){
    //temp node 
    ListNode<T>* node = new ListNode<T>(d);

    //if its empty make sure tail is also equal to the node
    if(isEmpty()){
        tail = node;
    }
    else{
        node->next = head;
        head->prev = node;

    }   
    //update head pntr
    head = node;
    //increment size
    ++size;
   
}

template <typename T>
/** A method that inserts a new tail into the linked list 
 * Parm: represents the data to be inserted (it can be any type of data)
 */
void GenLinkedList<T>::insertTail(T d){
    ListNode<T>* node = new ListNode<T>(d);

    //if list is empty then head is also equal to the node
    if(isEmpty()){
        head = node;
    }
    else{
        node->prev = tail;
        tail->next = node;

    }   
    //tail pntr equals the node
    tail = node;
    //increment size
    ++size;
   
}

template <typename T>
/** This method removes the head of the LinkedList and returns its information as well as update necessary pointers
 * return: type T representing the data stored in the head node
 */
T GenLinkedList<T>::removeHead(){
    //error check: is list empty
    if(isEmpty()){
        throw runtime_error("empty list");
    }
    //set temp node to the curr head
    ListNode<T>*temp = head;
    if(head->next == NULL){//if there is only one node, update the tail pointer as well as the head pointer
        tail = NULL;
    }
    else{ //else make the node after the head node the new head
        head->next->prev = NULL;
        

    }
    //update head pointer
    head = head->next;
    //store old head's data
    T data = temp->data;
    //clear the temp node
    temp->next = NULL;
    --size;

    //delete temp node
    delete temp;
    //return data
    return data;
}

template <typename T>
/** This method removes the tail and returns its information and update necessary pointers
 * return: type T representing the data stored in the head node
 */
T GenLinkedList<T>::removeTail(){
    //error check: is the list empty
    if(isEmpty()){
        throw runtime_error("empty list");
    }
    ListNode<T>*temp = tail;
    //check if there is only one element in the LinkedList
    if(tail->prev == NULL){
        head = NULL;
    }
    else{ //else update the second to last element to become the new tail
        tail->prev->next = NULL;
        

    }
    //update tail pointer
    tail = tail->prev;
    //store data from the old tail
    T data = temp->data;
    //null out the temp data such that it can be deleted
    temp->prev = NULL;
    --size;

    //delete temp node
    delete temp;
    //return data
    return data;
}

template <typename T>
/** This method removes the node with a specific value and updates pointers
 * param: type T value representing the value to remove
 * return: type T representing the data removed
 */
T GenLinkedList<T>::removeNode(T value){
    //Error check: is the list empty
    if(isEmpty()){
        throw runtime_error("List empty");
    }

    //set a curr temp node to the head of the LinkedList
    ListNode<T>*curr = head;
    //while the data doesn't match the value
    while(curr->data != value){
        //update curr
        curr = curr->next;
        if(curr == NULL){ //if you reach the end and the value is not found then return -1
            return -1;
        }
    }

    //if the value is inbetween head and tail
    if(curr != head && curr != tail){
        curr->prev->next = curr->next;
        curr->next->prev = curr->prev;
    }
    //if the value is the head
    if(curr == head){
        head = curr->next;
        head->prev = NULL;
    }
    //if the value is the tail
    if(curr == tail){
        tail = curr->prev;
        tail->next = NULL;
    }
    
    //clear up the curr node's pointers (i.e set next and prev to NULL)
    curr->next = NULL;
    curr->prev = NULL;
    //store curr's data
    T d = curr->data;

    //delete the curr node
    delete curr;
    //return the data
    return d;
}

template <typename T>
/** Find but not remove a specific node
 * param: type T value representing the node to find
 * return the position of the node
 */
int GenLinkedList<T>::find(T value){
    
    int pos = -1;
    //temp node set to the head
    ListNode<T>*curr = head;

    //loop to check every position  
    while(curr != NULL){

        ++pos; //incrememnt position
        if(curr->data == value){ //check if curr's data is the value
            break; //if it is then break from the loop
        }
        curr = curr->next; //update curr
       
    }
    //if curr reached the end without finding the value then position is -1
    if(curr == NULL){
        pos = -1; 
    }
    //delete curr
    delete curr;
    //return the position 
    return pos;
}

template <typename T>
/** A method that checks if the LinkedList is empty
 * return bool thatwill indicate if the list is empty or not
 */ 
bool GenLinkedList<T>::isEmpty(){
    return (size == 0);
}

template <typename T>
/** Get the size of the list
 * return: unsigned int representing the size of the LinkedList
 */
unsigned int GenLinkedList<T>::getSize(){
    return size;
}
#endif