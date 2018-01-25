 #include <iostream>
#include <new>
#include "ministack.h"
#include "bigstack.h"

BigStack::BigStack()
{
     headPtr = NULL;

}
void BigStack::Push(char ch)
{

 if(BigStack::IsEmpty())
 {
     headPtr = new ListNode;
     headPtr->previousPtr = NULL;
     headPtr->nextPtr = NULL;
     headPtr->stackPtr = new MiniStack();
 }
 else
 {
     if(headPtr->stackPtr->IsFull())
     {
           ListNode *tempPtr;
           tempPtr = headPtr;
           headPtr = new ListNode;
           tempPtr->nextPtr = headPtr;
           headPtr->previousPtr = tempPtr;
           headPtr->stackPtr = new MiniStack();
     }
  }
  
 headPtr->stackPtr->Push(ch);   
       

    
}
void BigStack::Pop()
{
     if(BigStack::IsEmpty())
     {
                            
     }
     else
     {
         headPtr->stackPtr->Pop();
         
         if(headPtr->stackPtr->IsEmpty())
         {
            ListNode *tempPtr;
            delete headPtr->stackPtr;
            tempPtr = headPtr->previousPtr;
            delete headPtr;
            headPtr = tempPtr;
            headPtr->nextPtr = NULL;
         }
     }    

}
char BigStack::Top()
{
     if(BigStack::IsEmpty())
     {
                            
     }
     else 
     {
          headPtr->stackPtr->Top();
          
     }
          
}
void BigStack::MakeEmpty()
{
     if(BigStack::IsEmpty())
     {
                            
     }
     else
     {
         while(headPtr != NULL)
         {
                       
           BigStack::Pop();
         }
        
        headPtr = NULL; 
     }         

}
bool BigStack::IsFull() const
{    
    ListNode* temp1;
    MiniStack* temp2;
    try
    {
       temp1 = new ListNode;
       temp2 = new MiniStack;
       delete temp1;
       delete temp2;
       return false;
    }
    catch(std::bad_alloc)
    {
      return true;
    }
}
bool BigStack::IsEmpty() const
{
   return ( headPtr == NULL );
}
BigStack::~BigStack()
{
     if(BigStack::IsEmpty())
     {
                            
     }
     else
     {
         while(headPtr != NULL)
         {
                       
           BigStack::Pop();
         }
        
     }         
}

