/*
 * =====================================================================================
 *
 *       Filename:  DecoratorPattern.cpp
 *
 *    Description:  Decorator pattern is to add additional behaviour to existing object dynamically without affecting the other instance of the same class.
 *                  Example: Pizza could be different types depending on the base but the same types can have different topings.
 *                  This allow user to add extra decoration to existing pizza types.
 *
 *                  Pizza could be: ThinCrust, FlatBread, CheeseBust, Greek
 *                  Toping could be: Tomato, Paneer, chicken, Jalapeno
 *
 *        Version:  1.0
 *        Created:  10/16/18 00:02:21
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Atul Das (ad), atuldas.ind@gmail.com
 *   Organization:
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <iostream>
#include <string>

using namespace std;

/* This is the base class, from which all the type of pizza and topings class derived*/
class Pizza {
    public:
        virtual string getDescription () {
            return m_strName;
        }

        virtual int cost () = 0;

    protected:
        string m_strName;
};

/* This is toping class derived from pizza so that it holds pizza for decoration */
class Topings: public Pizza {
     public:
         virtual string getDescription () = 0;
         virtual int cost () = 0;

};

/* Implementation for the basic pizza types */
class ThinCrust : public Pizza {

    public:
        ThinCrust () { m_strName = "ThinCrust";  }

        virtual int cost () { return 500; }
};

class FlatBread : public Pizza {

    public:
        FlatBread () { m_strName = "FlatBread"; }

        virtual int cost () { return 400; }
};

class CheeseBust : public Pizza {

    public:
        CheeseBust () { m_strName = "CheeseBust"; }

        virtual int cost () { return 600; }
};

class Greek : public Pizza {

    public:
        Greek () { m_strName = "Greek"; }

        virtual int cost () { return 400; }
};



/* Implementation for the Toping types */
class Tomato : public Topings {
    public:
        Tomato (Pizza * pPizza) : m_pPizza (pPizza) {}

        virtual string getDescription () { return m_pPizza->getDescription () + " + Tomato"; }

        virtual int cost () { return 50 + m_pPizza->cost (); }

        virtual ~Tomato () { delete m_pPizza; }

     protected:
         Pizza *m_pPizza;
};

class Paneer : public Topings {
    public:
        Paneer (Pizza * pPizza) : m_pPizza (pPizza) {}

        virtual string getDescription () {  return (m_pPizza->getDescription () + " + Paneer"); }

        virtual int cost () { return 70 + m_pPizza->cost (); }

        virtual ~Paneer () { delete m_pPizza; }

     protected:
         Pizza *m_pPizza;
};

class Chicken : public Topings {
    public:
        Chicken (Pizza * pPizza) : m_pPizza (pPizza) {}

        virtual string getDescription () { return m_pPizza->getDescription () + " + Chicken"; }

        virtual int cost () { return 80 + m_pPizza->cost (); }

        virtual ~Chicken () { delete m_pPizza; }

     protected:
         Pizza *m_pPizza;
};

class Jalapeno : public Topings {
    public:
        Jalapeno (Pizza * pPizza) : m_pPizza (pPizza) {}

        virtual string getDescription () { return m_pPizza->getDescription () + " + Jalapeno"; }

        virtual int cost () { return 25 + m_pPizza->cost (); }

        virtual ~Jalapeno () { delete m_pPizza; }

     protected:
         Pizza *m_pPizza;
};

// Method to print description and cost of pizza
void printPizzaInfo (Pizza * pPizza) {
    cout << "Pizza Description is : " << pPizza->getDescription () << endl
         << "Pizza cost is : " << pPizza->cost () << endl << endl;
}

/* Main */
int main () {

    Pizza * pPizza1 = new FlatBread ();
    printPizzaInfo (pPizza1);
    delete pPizza1;

    Pizza * pPizza2 = new CheeseBust ();
    pPizza2 = new Tomato (pPizza2);
    pPizza2 = new Paneer (pPizza2);
    printPizzaInfo (pPizza2);
    delete pPizza2;

    Pizza * pPizza3 = new ThinCrust ();
    pPizza3 = new Tomato (pPizza3);
    pPizza3 = new Paneer (pPizza3);
    pPizza3 = new Jalapeno (pPizza3);
    pPizza3 = new Chicken (pPizza3);
    printPizzaInfo (pPizza3);
    delete pPizza3;

    return 0;
}
