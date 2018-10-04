/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.

   * File Name : SingaltonPattern.cpp

   * Purpose :

   * Creation Date : 10-01-2015

   * Last Modified : Mon Mar  2 07:46:55 2015

   * Created By : Atul_Das

   _._._._._._._._._._._._._._._._._._._._._.*/
#include <stdio.h>
#include <iostream>

class SingaltonPattern {
public:
        static SingaltonPattern * GetInstance() {
            // for thread safe Singalton, put double check of null like below
            // if (s_pSp == NULL )
            // check_semaphore call to lock the mutex, the again check to no conflicts
            if (s_pSp == NULL )
                s_pSp = new SingaltonPattern();

            return s_pSp;
        }

        int getData() { return m_data; }

        void setData(int idata) { m_data = idata; }

protected:
        SingaltonPattern(): m_data(0) { 
        }

        SingaltonPattern(const SingaltonPattern& sp):m_data(sp.m_data) { 
        }

        virtual ~SingaltonPattern() { 
            if (s_pSp != NULL) 
            {
                delete s_pSp;
                s_pSp = NULL;
            }
        }

        SingaltonPattern & operator= (const SingaltonPattern& sp) {
            return (*this);
        }

private:
        static  SingaltonPattern* s_pSp;
        int     m_data;
};

SingaltonPattern * SingaltonPattern::s_pSp = NULL;

int main() {
    SingaltonPattern::GetInstance()->setData(5);
    printf("The value set in SingaltonPattern is %d\n", SingaltonPattern::GetInstance()->getData());

    SingaltonPattern::GetInstance()->setData(2);
    printf("The value set in SingaltonPattern is %d\n", SingaltonPattern::GetInstance()->getData());
    return 0;
}
