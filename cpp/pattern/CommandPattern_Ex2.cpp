/*
 * =====================================================================================
 *
 *       Filename:  CommandPattern_Ex2.cpp
 *
 *    Description:  Command Pattern, in this example we have basic double number method. using the same we can implement quadra, octal and hexa operations.
 *
 *        Version:  1.0
 *        Created:  10/21/18 14:12:43
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
#include <vector>

using namespace std;

class Number {
    public:
        void doubleIt (int & iData) {
            iData *= 2;
        }
};

class Command {

    public:
        virtual void execute (int &) = 0;
};


class SingleCommand : public Command {
    private:
        typedef void (Number:: *Action) (int &);

    public:

        SingleCommand (Number * pReceiver, Action  fpAction) {
            _pReceiver = pReceiver;
            _fpAction  = fpAction;
        }

        virtual void execute (int & iData) {
            (_pReceiver->*_fpAction) (iData);
        }

    private:

        Number * _pReceiver;
        Action   _fpAction;

};

class ComplexCommand : public Command {
    public:
        void addCommand (Command * pCommand) {
            _vCommands.push_back (pCommand);
        }

        virtual void execute (int & iData) {
            for (int i = 0; i < _vCommands.size ( ); i++)
                _vCommands [i]->execute (iData);
        }

    private:
        vector <Command *> _vCommands;
};

void executeCommand (Command * pCommand, int number, string operation) {

    int iData = number;
    cout << endl << "Input value " << iData;
    pCommand->execute (iData);
    cout << ", Value after " << operation << ": " << iData << endl;
}

int main () {
    Number number;

    SingleCommand  doubleIt = SingleCommand (&number, &Number::doubleIt);

    ComplexCommand quadraIt;
    quadraIt.addCommand (&doubleIt);
    quadraIt.addCommand (&doubleIt);

    ComplexCommand octaIt;
    octaIt.addCommand (&quadraIt);
    octaIt.addCommand (&doubleIt);

    ComplexCommand hexaIt;
    hexaIt.addCommand (&octaIt);
    hexaIt.addCommand (&doubleIt);

    int n = 3;
    executeCommand (&doubleIt, n, "Double");
    executeCommand (&quadraIt, n, "Quadra");
    executeCommand (&octaIt,   n, "Octa");
    executeCommand (&hexaIt,   n, "Hexa");

    return 0;
}
