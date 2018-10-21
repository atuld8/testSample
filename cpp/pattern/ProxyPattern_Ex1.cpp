/*
 * =====================================================================================
 *
 *       Filename:  ProxyPattern_Ex1.cpp
 *
 *    Description:  Proxy pattern has multiple use cases, one is to delay the object created when really required.
 *
 *        Version:  1.0
 *        Created:  10/20/18 23:02:57
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

using namespace std;

class Subject {
    public:
        virtual void execute () = 0;
};

class RealSubject : public Subject {

    public:
        RealSubject (int iData) : _iData (iData) {}

        virtual void execute () {
            cout << " I am real subject, value is" << _iData << endl;
        }

    protected:
        int _iData;
};

class ProxySubject : public Subject {

    public:

        ProxySubject (int iData) : _iData (iData), _pRealSubject (NULL) { }

        virtual void execute () {

            cout << "I am proxy subject, calling real subject " << endl;

            if (NULL == _pRealSubject) {
                cout << " creating real subject" << endl;
                _pRealSubject = new RealSubject (_iData);
            }

            if (_pRealSubject)
                _pRealSubject->execute ();

            cout << endl << endl;
        }

        virtual ~ProxySubject () {
            if (_pRealSubject)
                delete _pRealSubject;
        }

    protected:
        RealSubject *_pRealSubject;
        int         _iData;
};

int main () {

    ProxySubject proxySubject (100);

    proxySubject.execute ();

    proxySubject.execute ();

    return 0;
}
