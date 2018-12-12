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
        virtual void initializeGame () = 0;
        virtual void startGame () = 0;
        virtual void breakGame () = 0;
        virtual void resumeGame () = 0;
        virtual void endGame () = 0;

    public:
        void playGame () {

            cout << endl << endl << endl << "-------------------------------" << endl;

            initializeGame ();

            startGame ();

            breakGame ();

            resumeGame ();

            endGame ();

            cout << "-------------------------------" << endl;
        }
};

class CCricket : public CGame {

    virtual void initializeGame () {
        cout << "Cricket Game Initialized!" << endl;
    }

    virtual void startGame () {
        cout << "Cricket Game Started!" << endl;
    }

    virtual void breakGame () {
        cout << "Break in the Cricket Game !" << endl;
    }

    virtual void resumeGame () {
        cout << "Cricket Game resumed!" << endl;
    }

    virtual void endGame () {
        cout << "Cricket Game End!" << endl;
    }
};

class CFootball : public CGame {

    virtual void initializeGame () {
        cout << "Football Game Initialized!" << endl;
    }

    virtual void startGame () {
        cout << "Football Game Started!" << endl;
    }

    virtual void breakGame () {
        cout << "Break in the Football Game !" << endl;
    }

    virtual void resumeGame () {
        cout << "Football Game resumed!" << endl;
    }

    virtual void endGame () {
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
