/*
 * =====================================================================================
 *
 *       Filename:  ProxyPattern_Ex2.cpp
 *
 *    Description:  Proxy Pattern which can be used to control the flow by adding control access to real subject.
 *                  Another use case is change the behaviour of the operation depending on the operator
 *
 *        Version:  1.0
 *        Created:  10/21/18 09:33:18
 *       Revision:  none
 *       Compiler:  gcc
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <iostream>
#include <string>

using namespace std;

class Subject {
    public:
        virtual void execute () = 0;
};

class RealSubject {
    public:
        RealSubject (string strUser): _strUser(strUser) {}

        virtual void execute () {
            cout << _strUser << ": Executing the realSubject operation" << endl;
            cout << endl << endl;
        }

        string getUser () { return _strUser; }

        void setSudoUser () {
            _strUser = "Root";
        }

    protected:
        string _strUser;
};

class ProxyControllerSubject {
    public:
        ProxyControllerSubject (string strUser): _realSubject (strUser) {}

        virtual void execute () {

            if (_realSubject.getUser ().compare ("Root") == 0) {
                cout << _realSubject.getUser () << ": You are the super User " << endl;
                _realSubject.execute ();
            } else {
                if (_realSubject.getUser ().compare ("User1") == 0) {
                    cout << _realSubject.getUser () << ": you have permission to perform this operation" << endl;
                    _realSubject.execute ();
                }
                else
                    cout << _realSubject.getUser () << ": you do not have permission to perform this operation" << endl;
            }

        }

        RealSubject * operator-> () {

            cout << "Original User is " << _realSubject.getUser () << endl;
            _realSubject.setSudoUser ();
            return &_realSubject;
        }

    protected:

        RealSubject _realSubject;

};

int main () {

    ProxyControllerSubject proxyControllerSubjectForUser1 ("User1");
    proxyControllerSubjectForUser1.execute ();

    ProxyControllerSubject proxyControllerSubjectForUser2 ("User2");
    proxyControllerSubjectForUser2.execute ();
    // In below case, when -> operator returns RealSubject pointer, it will execute 'execute' method of RealSubject
    proxyControllerSubjectForUser2->execute ();

    ProxyControllerSubject *pSudoProxyControllerSubjectForUser3 = new ProxyControllerSubject ("User3");
    // in this call, execute of ProxyControllerSubject object will be called, not like above example
    pSudoProxyControllerSubjectForUser3->execute ();
    // In below case, when -> operator returns RealSubject pointer, it will execute 'execute' method of RealSubject
    (*pSudoProxyControllerSubjectForUser3)->execute ();
    delete pSudoProxyControllerSubjectForUser3;

    return 0;
}
