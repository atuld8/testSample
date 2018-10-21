/*
 * =====================================================================================
 *
 *       Filename:  ChainOfRespPattern_Ex1.cpp
 *
 *    Description:  Chain of Responsibility pattern is Behavioral pattern, avoid coupling of the sender
 *                  request to its receiver by giving more than one object the chance of handling the request.
 *
 *                  Base class always has next pointer and one chain method always delegate the request to next object
 *                  if derived class can not handle the request, then delegate it to base class
 *
 *        Version:  1.0
 *        Created:  10/21/18 11:37:28
 *       Revision:  none
 *       Compiler:  gcc
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <iostream>

using namespace std;

class BaseofChainResp {

    public:
        BaseofChainResp () : _next (NULL) {}

        BaseofChainResp (BaseofChainResp * next): _next (next) {}

        void addRespToChain (BaseofChainResp * next) {
            if (_next)
                _next->addRespToChain (next);
            else
                 _next = next;
        }

        virtual void handleResponsibility (int iData) {
            if (_next)
                _next->handleResponsibility (iData);
        }
    private:
        BaseofChainResp * _next;
};

class Mod1Handler : public BaseofChainResp {

    public:

        virtual void handleResponsibility (int iData) {
            cout << "Mod1Hanlder ->  ";
            if (iData % 1) {
                BaseofChainResp::handleResponsibility (iData);
            } else {
                cout << iData << " is mod of 1" << endl;
            }
        }
};

class Mod2Handler : public BaseofChainResp {

    public:

        virtual void handleResponsibility (int iData) {
            cout << "Mod2Hanlder ->  ";
            if (iData % 2) {
                BaseofChainResp::handleResponsibility (iData);
            } else {
                cout << iData << " is mod of 2" << endl;
            }
        }
};

class Mod3Handler : public BaseofChainResp {

    public:

        virtual void handleResponsibility (int iData) {
            cout << "Mod3Hanlder ->  ";
            if (iData % 3) {
                BaseofChainResp::handleResponsibility (iData);
            } else {
                cout << iData << " is mod of 3" << endl;
            }
        }
};

class Mod4Handler : public BaseofChainResp {

    public:

        virtual void handleResponsibility (int iData) {
            cout << "Mod4Hanlder ->  ";
            if (iData % 4) {
                BaseofChainResp::handleResponsibility (iData);
            } else {
                cout << iData << " is mod of 4" << endl;
            }
        }
};

class Mod5Handler : public BaseofChainResp {

    public:

        virtual void handleResponsibility (int iData) {
            cout << "Mod5Hanlder ->  ";
            if (iData % 5) {
                BaseofChainResp::handleResponsibility (iData);
            } else {
                cout << iData << " is mod of 5" << endl;
            }
        }
};

int main () {
    const int MAX_RANGE = 2000;

    Mod5Handler rootHandler;
    rootHandler.addRespToChain (new Mod4Handler ());
    rootHandler.addRespToChain (new Mod3Handler ());
    rootHandler.addRespToChain (new Mod2Handler ());
    rootHandler.addRespToChain (new Mod1Handler ());

    cout << "Calling data " << endl;
    for (int i = 0; i < 10; i++) {
        int data = rand () % MAX_RANGE;
        cout << i+1 << ": Random generated data is " << data << endl;
        rootHandler.handleResponsibility (data);
    }

    return 0;
}
