//
// lfsr.h -- 2015 Spring -- Project04 Queues
//
// Client code of queue container which implements a
// pseudo-random number generator by using a queue of integers 
// as a linear feedback shift register
//
//
// NOTE:
// Pattern of ones and zeros repeats ine queue eventually repeats
//
// DO NOT MODIFY OR SUBMIT THIS FILE
//

#include "queue.h"

#ifndef LFSR_H
#define LFSR_H

class LFSR
{
 private:
    Queue q;                    // Queue object

    int   t1, t2;               // Tap index values - two integers (peek offsets from front of queue)

    bool  XOR(int a, int b);
    // XOR(...)    
    // Exclusive OR function                            
    // a | b | a XOR b
    // ----------------
    // 0 | 0 |    0
    // 0 | 1 |    1
    // 1 | 0 |    1
    // 1 | 1 |    0

 public:
    LFSR(string seed, int tap1, int tap2); 
    // LFSR(...) 
    // Initializes t1 and t2 to tap1 and tap2, respectively
    // and parses seed string to loading queue with starting values
    
    void NextState();           
    // NextState()
    // Iterator method computes and queues next pseudo-random number in sequence 
    // Algorithm
    //  (1)  temp = Peek(tap1) XOR Peek(tap2)
    //  (2)  Dequeue
    //  (3)  Enqueue(temp)
                                
    void Print()
    // Print() -- DO NOT MODIFY OR RELOCATE THIS FUNCTION
    {
        int k = 0;
        int num = q.Size();
        
        while (k < num)
        {
            int temp = q.Front();
            q.Dequeue();
            q.Enqueue(temp);
            cout << temp;
            k++;
        }
    }
};

#endif



