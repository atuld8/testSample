/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.

   * File Name : SingletonPattern.cpp

   * Purpose :

   * Creation Date : 10-01-2015

   * Last Modified : Mon Mar  2 07:46:55 2015

   * Singleton class properties
   *    - private static variable
   *    - private contructor, copy contructor, assignment operator
   *    - public destructor
   *    - public static getInstance method
   _._._._._._._._._._._._._._._._._._._._._.*/
#include <stdio.h>
#include <iostream>

class SingletonPattern {
public:
        virtual ~SingletonPattern() {
        }

        static SingletonPattern * GetInstance() {
            // for thread safe Singleton, put double check of null like below
            // if (s_pSp == NULL )
            // check_semaphore call to lock the mutex, the again check to no conflicts
            if (s_pSp == NULL )
                s_pSp = new SingletonPattern();

            return s_pSp;
        }

        int getData() { return m_data; }

        void setData(int idata) { m_data = idata; }

protected:
        SingletonPattern(): m_data(0) {
        }

        SingletonPattern(const SingletonPattern& sp):m_data(sp.m_data) {
        }

        SingletonPattern & operator= (const SingletonPattern& sp) {
            return (*this);
        }

private:
        static  SingletonPattern* s_pSp;
        int     m_data;
};

SingletonPattern * SingletonPattern::s_pSp = NULL;

int main() {
    SingletonPattern::GetInstance()->setData(5);
    printf("The value set in SingletonPattern is %d\n", SingletonPattern::GetInstance()->getData());

    SingletonPattern::GetInstance()->setData(2);
    printf("The value set in SingletonPattern is %d\n", SingletonPattern::GetInstance()->getData());
    return 0;
}
