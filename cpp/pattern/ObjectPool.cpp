/*
 * =====================================================================================
 *
 *       Filename:  ObjectPool.cpp
 *
 *    Description: This is example of Object pool pattern
 *
 *                 key notes: implemented as singleton class and it creates the objects and manage the pool
 *
 *        Version:  1.0
 *        Created:  11/17/2016 08:57:41
 *       Revision:  none
 *       Compiler:  gcc
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>

#include <iostream>

template <typename T>
class DefaultMemoryAllocator {
    public:
        static inline void * allocate(size_t size) {
            return ::operator new(size, ::std::nothrow);
        }

        static inline void deallocate(void * ptr, size_t size) {
            ::operator delete(pointer);
        }
};

template<typename T, class TMemoryAllocator=DefaultMemoryAllocator>
class ObjectPoolPatter {

};

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
int
main ( int argc, char *argv[] )
{

    return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
