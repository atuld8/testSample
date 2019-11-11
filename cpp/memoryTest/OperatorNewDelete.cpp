/*
 * =====================================================================================
 *
 *       Filename:  OperatorNewDelete.cpp
 *
 *    Description:  The sample program to test the new and delete operator
 *
 *        Version:  1.0
 *        Created:  12/23/18 21:06:19
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Atul Das (ad), atuldas.ind@gmail.com
 *   Organization:  Anonymus private company ltd.
 *
 * =====================================================================================
 */
#include <stdlib.h>

#include <iostream>
#include <string>

using namespace std;

class CMemoryManager {

    public:
        void * operator new (size_t size) {
            cout << "CMemoryManager: new operator call" << endl;

            if (size <= 0)
                return NULL;

            return (void *) malloc(size);
        }

        void operator delete (void * pointer) {
            cout << "CMemoryManager: delete operator call" << endl;

            if (pointer)
                free(pointer);
        }
};

class CStudent : public CMemoryManager {
    public:
        CStudent (char * name, int age)
            :   _name(name),
                _age(age) {
            cout << "CStudent C'tor" << endl;
        }

        void display () {
            cout << "Name: " << _name << " Age: " << _age << endl;
        }

    private:
        char * _name;
        int    _age;
};

class CEmployee {
    public:
        CEmployee (string name, int experience)
            : _name (name),
              _experience (experience) {
            cout << "CEmployee C'tor" << endl;
       }

        void display () {
            cout << "Name: " << _name << " Experience: " << _experience << endl;
        }

    private:
        string  _name;
        int     _experience;
};

void * operator new (size_t size) {
     cout << "Global new operator" << endl;

     if (size <= 0)
         return NULL;

     return (void *) malloc (size);
}

void operator delete (void * pointer) {
     cout << "Global delete operator" << endl;
    if (pointer)
        free (pointer);
}


int main() {
    CStudent  * pStudent  = new CStudent ((char * )"student1", 18);
    CEmployee * pEmployee = new CEmployee ("Employee1", 10);

    pStudent->display ();
    pEmployee->display ();

    delete (pStudent);
    delete (pEmployee);

    return 0;
}
