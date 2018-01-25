#include <iostream>
#include "ministack.h"

MiniStack::MiniStack()
{
    top = -1;
    stackPtr = new char[5];
}
void MiniStack::Push(char ch)
{
    top++;
    stackPtr[top] = ch;
}
void MiniStack::Pop()
{
    top--;
}
void MiniStack::MakeEmpty()
{
    top = -1;
}
char MiniStack::Top()
{
    return stackPtr[top];    
}
bool MiniStack::IsFull() const
{
    return (top == (MINI_STACK_SIZE-1));
}
bool MiniStack::IsEmpty() const
{
    return (top == -1);
}
MiniStack::~MiniStack()
{

    top = -1;
    delete stackPtr;
}
