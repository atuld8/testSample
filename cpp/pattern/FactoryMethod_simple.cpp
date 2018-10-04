/*
 * =====================================================================================
 *
 *       Filename:  FactoryMethod_simple.cpp
 *
 *    Description:  This is example of Factory method with simple strategy
 *
 *        Version:  1.0
 *        Created:  10/29/2016 07:58:09
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

enum FanType {
    TableFan,
    CeilingFan,
    ExhaustFan
};

class IFan {
    public:
        virtual void switchOn()  = 0;
        virtual void switchOff() = 0;
};

class CTableFan : public IFan {
    public:
        virtual void switchOn() {
            cout << "TableFan is switched on" << endl;
        }

        virtual void switchOff() {
            cout << "TableFan is switched off" << endl;
        }
};

class CCeilingFan : public IFan {
    public:
        virtual void switchOn() {
            cout << "CeilingFan is switched on" << endl;
        }

        virtual void switchOff() {
            cout << "CeilingFan is switched off" << endl;
        }
};

class CExhaustFan : public IFan {
    public:
        virtual void switchOn() {
            cout << "ExhaustFan is switched on" << endl;
        }

        virtual void switchOff() {
            cout << "ExhaustFan is switched off" << endl;
        }
};

class IFanFactory {
    public:
        virtual IFan * createFan(FanType fantype) = 0;
};

// This is simple factory clas which takes decision for creation of any
// product object
// Difference bewtween Simple Factory and Factory method pattern is the creation is also
// delayed to sub classes. so that we not need to modify the createFan method for each time.
// client will get it depending on call.
class SimpleFanFactory : public IFanFactory {
    public:
        virtual IFan * createFan(FanType fantype) {
            switch (fantype) {
                case FanType::TableFan:
                    return new CTableFan();
                case FanType::CeilingFan:
                    return new CCeilingFan();
                case FanType::ExhaustFan:
                    return new CExhaustFan();
                default:
                    return NULL;
            }
        }
};

int main() {
    IFanFactory *fanfactory = new SimpleFanFactory();

    IFan * fan = fanfactory->createFan(FanType::TableFan);

    fan->switchOn();

    return 0;
}
