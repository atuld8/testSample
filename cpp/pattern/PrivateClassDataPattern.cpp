/*
 * =====================================================================================
 *
 *       Filename:  PrivateClassDataPattern.cpp
 *
 *    Description:  Private Class Data pattern is used to hide the data from client.
 *                  This can be achieved by writing the class to hold the data and another class which control the writting the data to it.
 *
 *
 *        Version:  1.0
 *        Created:  10/20/18 20:46:44
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <iostream>
#include <string>

using namespace std;

class PrivateData {
    public:

       PrivateData (int iData, string strData) : _iData (iData), _strData (strData) { }

       int  getNumber ()          { return _iData; }
       void setNumber (int iData) { _iData = iData; }

       string getString ()               { return _strData; }
       void   setString (string strData) { _strData = strData; }

    private:
        int    _iData;
        string _strData;
};

class PublicInterface {
    public:
       PublicInterface (int iData, string strData) : _privateData (iData, strData) {}

       int    getNumber () { return _privateData.getNumber (); }
       string getString () { return _privateData.getString (); }

       void   printData () { cout << _privateData.getNumber () << " " << _privateData.getString () << endl; }

       void   setData (int iData, string strData) {
           _privateData.setNumber (iData);
           _privateData.setString (strData);
       }
    private:
        PrivateData _privateData;
};

int main () {
    PublicInterface publicInterface (10, "string data");

    publicInterface.printData ();

    publicInterface.setData (20, "updated string data");

    publicInterface.printData ();

    return 0;
}
