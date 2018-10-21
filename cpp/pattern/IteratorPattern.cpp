/*
 * =====================================================================================
 *
 *       Filename:  IteratorPattern.cpp
 *
 *    Description:  Iterator pattern is to provide the way to acces the elements of a aggregated object
 *                  sequentially without exposing its underlying representation.
 *
 *                  In this example, we have stack object and the stack iterator to access stack ojects.
 *
 *        Version:  1.0
 *        Created:  10/21/18 18:55:44
 *       Revision:  none
 *       Compiler:  gcc
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <iostream>

using namespace std;

#define MAX_STACK_ITEMS 10

class StackIterator;

class Stack {
    public:

        friend class StackIterator;

        Stack () : _iStackPointer (-1) { }

        void push (int iData) {
            if (_iStackPointer < MAX_STACK_ITEMS) {
                _arrItems[++_iStackPointer] = iData;
            }
        }

        int pop () {
            if (_iStackPointer > -1 ) {
                _iStackPointer--;
                return _arrItems [_iStackPointer+1];
            }

            return -1;
        }

    private:
        int _arrItems [MAX_STACK_ITEMS];
        int _iStackPointer;
};

class StackIterator {
    public:
        StackIterator (const Stack & cStack) : _cStack(cStack), _iIndex (0) { }

        // this is prefix operator ++x
        void operator++ () { _iIndex++; }

        // this is post operator x++
        void operator++ (int) { _iIndex++; }

        bool operator() () {
            return _iIndex != (_cStack._iStackPointer + 1);
        }

        int operator* () {
            return _cStack._arrItems[_iIndex];
        }

    private:
        const Stack &_cStack;
        int _iIndex;

};

bool operator== (const Stack& cStack1, const Stack& cStack2) {
    StackIterator stackIt1 (cStack1), stackIt2 (cStack2);

    while (stackIt1 ()) {
        if (*stackIt1 != *stackIt2)
            break;

        ++stackIt1;
        stackIt2++;
    }

    return !stackIt1 () && !stackIt2 ();
}

int main () {

    Stack stack1;

    stack1.push (1);
    stack1.push (2);
    stack1.push (3);
    stack1.push (4);
    stack1.push (5);


    Stack stack2 (stack1);
    Stack stack3 (stack1);
    Stack stack4 (stack1);
    Stack stack5 (stack1);

    stack3.pop ();
    stack4.pop ();

    stack4.push (6);
    stack5.push (7);

    cout << " Stack1 == Stack2 is " << (stack1 == stack2) << endl;
    cout << " Stack1 == Stack3 is " << (stack1 == stack3) << endl;
    cout << " Stack1 == Stack4 is " << (stack1 == stack4) << endl;
    cout << " Stack1 == Stack5 is " << (stack1 == stack5) << endl;

    return 0;
}
