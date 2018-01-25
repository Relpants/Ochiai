//
// ministack.h
//
//
// DO NOT MODIFY OR SUBMIT THIS FILE
//

#include <iostream>
using namespace std;

#ifndef MINISTACK_H

#define MINISTACK_H

const int MINI_STACK_SIZE = 5;  // Fixed number of elements in stack

// Client code responsible for all error handling
class MiniStack        	// Represents an array implementation of the Stack ADT
{
  private:
	int top;           	// Index of topmost value stored in MiniStack
	char* stackPtr;    	// Pointer to ministack array of MINI_STACK_SIZE chars

  public:
	MiniStack();       	// Default constructor creates an empty MiniStack object
	void Push(char ch);	// Adds element to top of ministack assuming stack not full
	void Pop();        	// Removes element from top of ministack assuming stack not empty
	void MakeEmpty();  	// Empties ministack
	char Top();        	// Returns copy of value stored at top of ministack assuming stack not empty
	bool IsFull() const;   // Returns true if ministack is full; false otherwise
	bool IsEmpty() const;  // Returns true if ministack empty; false otherwise
	~MiniStack();      	// Destructor deallocates ministack array

	void FwdPrint() const 	// Prints ministack contents, top to bottom
	{
    	cout << "( ";
    	for(int k = top; k >= 0; k--)
        	cout << stackPtr[k] << ' ';
    	cout << ")";
	} // End MiniStack::Print()
    
    void RevPrint() const 	// Prints ministack contents, top to bottom
	{
    	cout << "( ";
    	for(int k = 0; k <= top; k++)
        	cout << stackPtr[k] << ' ';
    	cout << ")";
	} // End MiniStack::Print()
};

#endif


