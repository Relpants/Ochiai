#include <iostream>
#include "queue.h"
using namespace std;

Queue::Queue()
{
  //cout << " starting constructor " << endl;
    int count = 0;
    rearPtr = NULL;

  //cout<< " done with constructor" << endl;
}
Queue::~Queue()
{
 //cout << " starting deconstructor " << endl;
	while( count != 0 )
	{
      	 
        	Dequeue();
	}

  //cout<<" done with deconstructor"<< endl;
}
void Queue::MakeEmpty()
{
  //cout << " starting makeEmpty " << endl;
	while( count != 0 )
	{
       	 
        	Dequeue();
	}

  //cout<<" Done with makeEmpty" << endl;

}
void Queue::Enqueue(int n)
{
 	//cout << " starting enqueue" << endl;
 	if(IsFull())
 	{
   	throw QueueFull();
 	}
 	else
 	{
    count++;
    if(count==1)
    {    
   	 rearPtr = new Node;
   	 rearPtr->data = n;
   	 rearPtr->nextPtr = rearPtr;
    }
    else
    {
   	 Node *tempPtr2;
   	 Node *tempPtr = new Node;
   	 tempPtr->data = n;
   	 tempPtr2 = rearPtr;
   	 for(int i = 0; i < ( count); i++)
   	 {
   		 tempPtr2 = tempPtr2->nextPtr;
   	 }
   	 tempPtr->nextPtr = tempPtr2;
   	 rearPtr->nextPtr = tempPtr;
   	 rearPtr = tempPtr;
    }
   		 
 	}

 //cout << " done with enqueue" << endl;
}
void Queue::Dequeue()
{
 	//cout<<"starting dequeue"<<endl;
 	if(IsEmpty())
 	{
             	 
    	throw QueueEmpty();
 	}
	else
 	{
    	count--;
    Node *tempPtr;
    tempPtr = rearPtr->nextPtr;
    rearPtr->nextPtr = tempPtr->nextPtr;
    delete tempPtr;
    if(count == 0 )
    {
   	 rearPtr = NULL;
    }
 	}

  //cout << "Done with dequeue"<<endl;

}
int Queue::Front() const
{
  //cout<<"starting Front"<<endl;
	if(IsEmpty())
	{
            	 
   	throw QueueEmpty();
	}
	else
	{
   	 
    	Node* tempPtr;
    	tempPtr = rearPtr;
   	 
    	for(int i = 0; i < (count); i++)            	// could be count-1
    	{
           	 
       	tempPtr = rearPtr->nextPtr;
    	}
   	 
  	return(tempPtr->data);
	}

  //cout<<"done with Front"<<endl;

}
int Queue::Rear() const
{
  //cout<<"starting Rear"<<endl;
	if(IsEmpty())
	{
            	 
  	throw QueueEmpty();
	}
	else
	{
   	 
    	return (rearPtr->data);
	}

  //cout<<"Done with Rear"<<endl;

}
int Queue::Peek(int n) const
{
  //cout<<"starting Peek"<<endl;
	Node* tempPtr;
	tempPtr = rearPtr;
    
	if(IsEmpty())
	{
            	 
  	throw QueueEmpty();
	}
	if( ( n > ( count - 1 )) || ( n < 0 )  )
	{
   	throw QueueInvalidPeek();
	}
	else
	{
   	for(int i = 0; i < ((count+1) + (n)); i++)
   	{
       	 
      	tempPtr = tempPtr->nextPtr;
   	}
	}
   	 
    	return(tempPtr->data);

  //cout<<"Done with Peek"<<endl;
}
bool Queue::IsFull() const
{
  //cout<<"starting IsFull"<<endl;
    
	try
	{
      	Node* tempPtr;
      	tempPtr = new Node;
      	delete tempPtr;
      	return false;
	}
	catch(std::bad_alloc)
	{
                    	 
     	return true;
	}

  //cout<<"done with IsFull"<<endl;
}
bool Queue::IsEmpty() const
{
  //cout<<"starting IsEmpty"<<endl;
    return(rearPtr == NULL);

  //cout<<"done with IsEmpty"<<endl;

}
int Queue::Size() const
{
  //cout<<"starting size"<<endl;
    return count;
 // cout<<"done with size"<<endl;
    
}
