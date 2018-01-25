//
// queue.h -- 2015 Spring -- Project04 Queues
//
// Queue class is a circular linked list implementation of the queue abstract data type  
//
// DO NOT MODIFY OR SUBMIT THIS FILE
//

#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
using namespace std;

//
// Exception classes
//
class QueueEmpty { /* Empty error class */ };  // Exception class for empty queue condition          

class QueueFull  { /* Empty error class */ };  // Exception class for full queue condition

class QueueInvalidPeek  { /* Empty error class */ };  // Exception class for invalid queue peek condition

//
// Queue Node Structure
//
struct Node                         // Linked circular queue node structure
{
	int         data;				// Field for storing data in the queue node
	Node*	    nextPtr;			// Points to successor node (node following current node)
};


//
// Queue class declaration
//
class Queue				            // Linked circular queue 
{
private:
    Node*       rearPtr;            // Points to rear of queue
	int			count;				// Number of values stored in queue
	
public:
	/**********  Start of functions you must implement for Queue  **************/
	// Implement the following nine public functions in the file named queue.cpp
	
	Queue();
	// Queue()
	// Initializes all private variables to indicate an empty queue
	
	~Queue();
	//~Queue()
	// Deallocates all queue nodes
	
	void MakeEmpty();
	// MakeEmpty()
	// Deallocates all queue nodes and returns queue to empty ready-to-use state 
	
    void Enqueue(int n);
	// Enqueue()
	// Adds value n to rear of queue and increments count.
	// If queue is already full, throws QueueFull exception

	void Dequeue();
	// Dequeue()
	// Removes front value from queue and decrements count.
	// If queue is empty, throws QueueEmpty exception

	int Front() const;
	// Front()
	// Returns integer from front of queue
	// If queue is empty, throws QueueEmpty exception
    // DOES NOT MODIFY THE QUEUE

	int Rear() const;
	// Rear()
	// Returns integer from rear of queue
	// If queue is empty, throws QueueEmpty exception
    // DOES NOT MODIFY THE QUEUE

	int Peek(int n) const;
	// Peek()
	// Returns integer n positions from front of queue
    // If queue is empty, throws QueueEmpty
	// If position n does not exist, throws QueueInvalidPeek
    // DOES NOT MODIFY THE QUEUE
	
	bool IsFull() const;
	// IsFull()
	// Returns true if queue is full.  Returns false otherwise.  DOES NOT MODIFY THE QUEUE
	
	bool IsEmpty() const;
	// IsEmpty()
	// Returns true if queue is empty.  Returns false otherwise.  DOES NOT MODIFY THE QUEUE
	
	int Size() const;
	// Size()
	// Returns number of items stored in queue.  DOES NOT MODIFY THE QUEUE

	/***********  End of functions you must implement for Queue ***************/
	
	void PrintQ() const
	// PrintQ() -- DO NOT MODIFY OR RELOCATE THIS FUNCTION
	// Prints contents of queue front to rear without modifying its contents 
	{
		cout << "Front { ";
        if (rearPtr != NULL)
        {
            Node* tempPtr = rearPtr->nextPtr;
            int n = 0;
   		    while (n < count)
   		    {
   			    cout << tempPtr->data << ' ';
			    n++;
   		        tempPtr = tempPtr->nextPtr;
   		    }
        }
		cout << "} Rear";
	}  // End Print()
	
};

#endif

