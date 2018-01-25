//
// bigstack.h
//
//
// DO NOT MODIFY OR SUBMIT THIS FILE
//

#include <iostream>
using namespace std;

#ifndef BIGSTACK_H
#define BIGSTACK_H

#include "ministack.h"


struct ListNode        	// Description of a ListNode struct
{
	MiniStack* stackPtr;  	// Pointer to a MiniStack object
	ListNode*  nextPtr;   	// Pointer to next ListNode
    ListNode*  previousPtr;   // Pointer to previous ListNode
};

// Client code responsible for all error handling
class BigStack         	// Represents a double-linked node implementation of the Stack ADT
{
  private:
	ListNode* headPtr; 	// Pointer to head of double-linked list of nodes representing bigstack

  public:
	BigStack();        	// Default constructor initializes empty bigstack object (no ListNodes)
	void Push(char ch);	// Adds element to top of bigstack assuming stack not full (creates ListNodes only as needed)
	void Pop();        	// Removes element from top of stack assuming bigstack not empty (deallocating only as needed)
	char Top();        	// Returns copy of top value assuming bigstack not empty
	void MakeEmpty();  	// Empties bigstack
	bool IsFull() const;   // Returns true if bigstack full; false otherwise
	bool IsEmpty() const;  // Returns true if bigstack empty; false otherwise
	~BigStack();       	// Destructor deallocates all dynamic memory associated with bigstack object including
                       	// all list nodes

	void Print() const 	// Prints stack contents, top to bottom and bottom to top
	{
    	ListNode* tempPtr = headPtr;

    	// Forward print
    	cout << "Top [ ";
    	while (tempPtr != NULL)
    	{
        	tempPtr->stackPtr->FwdPrint();
   		 
   		 if (tempPtr->nextPtr == NULL)
   			 break;
   		 
        	tempPtr = tempPtr->nextPtr;
    	}
    	cout << " ] Bottom [ ";
   	 // Reverse print
   	 while (tempPtr != NULL)
   	 {
   		 tempPtr->stackPtr->RevPrint();  
   		 tempPtr = tempPtr->previousPtr;
   	 }
   	 cout << "] Top" << endl;

	} // End BigStack::Print()
};

#endif