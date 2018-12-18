/*
 * =====================================================================================
 *
 *       Filename:  TemplateMethodPattern.cpp
 *
 *    Description:  Define the skeleton of an algorithm in an operation, deferring some steps to client subclasses.
 *                  Template Method lets subclasses redefine certain steps of an algorithm without changing the algorithm's structure.
 *
 *                  In this example, We have game workflow and depending on the game style, the derived class will implement the flow.
 *
 *        Version:  1.0
 *        Created:  12/12/18 21:32:10
 *       Revision:  none
 *       Compiler:  gcc
 *
 * =====================================================================================
 */
#include <stdlib.h>

#include <iostream>


using namespace std;

class CGame {
    protected:
        virtual void initialize () = 0;
        virtual void start () = 0;
        virtual void teaBreak() = 0;
        virtual void resume() = 0;
        virtual void end() = 0;

    public:
        void playGame () {

            cout << endl << endl << endl << "-------------------------------" << endl;

            initialize ();

            start ();

            teaBreak ();

            resume ();

            end ();

            cout << "-------------------------------" << endl;
        }
};

class CCricket : public CGame {

    virtual void initialize () {
        cout << "Cricket Game Initialized!" << endl;
    }

    virtual void start () {
        cout << "Cricket Game Started!" << endl;
    }

    virtual void teaBreak () {
        cout << "Tea Break in the Cricket Game !" << endl;
    }

    virtual void resume () {
        cout << "Cricket Game resumed!" << endl;
    }

    virtual void end () {
        cout << "Cricket Game End!" << endl;
    }
};

class CFootball : public CGame {

    virtual void initialize () {
        cout << "Football Game Initialized!" << endl;
    }

    virtual void start () {
        cout << "Football Game Started!" << endl;
    }

    virtual void teaBreak () {
        cout << "Tea Break in the Football Game !" << endl;
    }

    virtual void resume () {
        cout << "Football Game resumed!" << endl;
    }

    virtual void end () {
        cout << "Football Game End!" << endl;
    }
};


int main () {

    CGame * pGame = new CCricket ();
    pGame->playGame ();
    delete pGame;

    pGame = new CFootball ();
    pGame->playGame ();
    delete pGame;

    return 0;
}
