/*
 * =====================================================================================
 *
 *       Filename:  FactoryMethod_SubFactClass.cpp
 *
 *    Description:  This is example of Factory method with concreate factory class to create
 *                  product object
 *
 *        Version:  1.0
 *        Created:  10/29/2016 21:10:02
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Atul Das (adas), atul.das1@
 *   Organization:
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <iostream>


using namespace std;

class CFan {
    public:
        virtual void test_operation() = 0;
};

class CTableFan : public CFan {
    public:
        virtual void test_operation() {
            cout << "test_operation from CTableFan" << endl;
        }
};

class CCeilingFan : public CFan {

    public:
        virtual void test_operation() {
            cout << "test_operation from CCeilingFan" << endl;
        }
};

class CFanFactory {
    public:
        virtual CFan * getFan() = 0;
};

class CTableFanFactory : public CFanFactory {
    public:
        virtual CFan * getFan() {
            return new CTableFan();
        }
};

class CCeilingFanFactory : public CFanFactory {
    public:
        virtual CFan * getFan() {
            return new CCeilingFan();
        }
};

int main() {

    CFanFactory *ff = new CCeilingFanFactory();

    CFan * fan = ff->getFan();

    fan->test_operation();

    return 0;
}



