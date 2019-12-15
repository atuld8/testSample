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
 * =====================================================================================
 */
#include <stdlib.h>
#include <iostream>


using namespace std;

class CFan {
    public:
        virtual ~CFan() { }

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
        virtual ~CFanFactory() { }

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

    if (ff == NULL) {
        std::cout << "Error: Failed to create CFanFactory instance" << std::endl;
        return -1;
    }

    CFan * fan = ff->getFan();

    if (fan == NULL) {
        std::cout << "Error: Failed to get the fan instance" << std::endl;
        delete (ff);
        return -1;
    }

    fan->test_operation();

    delete (fan);
    delete (ff);

    return 0;
}



