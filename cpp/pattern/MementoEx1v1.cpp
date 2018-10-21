/*
 * =====================================================================================
 *
 *       Filename:  MementoEx1.cpp
 *
 *    Description:  A memento is an object that stores a snapshot of the internal state of another object.
 *
 *        Version:  1.0
 *        Created:  11/18/2016 21:00:52
 *       Revision:  none
 *       Compiler:  gcc
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdlib.h>

#include <iostream>
#include <vector>

class CNumber;
class CCommand;

// Memento class
class CMemento {
    public:
        CMemento (int val) {
            m_state = val;
        }

    private:
        friend class CNumber;
        int m_state;
};

// Originator class
class CNumber {
    public:
        CNumber (int val) {
            m_value = val;
        }

        void doubleTheNumber () {
            m_value *= 2;
        }

        void halfTheNumber () {
            m_value /= 2;
        }

        int getValue () {
            return m_value;
        }

        CMemento * createMemento () {
            return new CMemento (m_value);
        }

        void reinstallMemento (CMemento * memento) {
            m_value = memento->m_state;
        }

    private:
        int m_value;
};

// Caretaker class
class CCommand {
    public:
        typedef void (CNumber:: *Action) ();
        CCommand (CNumber * receiver, Action action) {
            m_pnumber = receiver;
            m_action  = action;

        }

        virtual void executeAction () {
            CMemento * m = m_pnumber->createMemento ();
            m_vMemento.push_back (m);
            m_vCommand.push_back (this);

            CCommand::m_commandcount++;

            if (m_commandcount > m_maxallowedcommands)
                m_maxallowedcommands = m_commandcount;

            (m_pnumber->*m_action) ();

        }

        static void undoAction () {
            if (m_commandcount == 0) {
                std::cout << "*** Attempt to run off the end!! *** " << std::endl;
                return;
            }

            m_vCommand[m_commandcount - 1]->m_pnumber->reinstallMemento (m_vMemento[m_commandcount - 1]);
            m_commandcount--;

        }

        static void redoAction () {
            if (m_commandcount >= m_maxallowedcommands) {
                std::cout << "*** Attempt to run off the end!! ***" << std::endl;
                return;
            }

            m_vCommand[m_commandcount]->m_pnumber->reinstallMemento (m_vMemento[m_commandcount]);
            m_commandcount++;

        }

    protected:
        CNumber                        *m_pnumber;
        Action                         m_action;
        static std::vector<CCommand *> m_vCommand;
        static std::vector<CMemento *> m_vMemento;
        static int                     m_commandcount;
        static int                     m_maxallowedcommands;
};

std::vector<CCommand *>       CCommand::m_vCommand;
std::vector<CMemento *>       CCommand::m_vMemento;
int                           CCommand::m_commandcount       = 0;
int                           CCommand::m_maxallowedcommands = 0;

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:
 * =====================================================================================
 */
int main (int argc, char *argv[]) {
    int input;

    std::cout << "Enter initiale interger number : " << std::endl;
    std::cin  >> input;

    CNumber * pnumber = new CNumber (input);

    CCommand * commandArray[3];
    commandArray[1] = new CCommand (pnumber, &CNumber::doubleTheNumber);
    commandArray[2] = new CCommand (pnumber, &CNumber::halfTheNumber);

    do {
    std::cout << "Exit[0], Double[1], Half[2], Undo[3], Redo[4]: ";
    std::cin >> input;

    if (3 == input)
        CCommand::undoAction ();
    else if (4 == input)
        CCommand::redoAction ();
    else if (2 == input || 1 == input)
        commandArray[input]->executeAction ();

    std::cout << "    " << pnumber->getValue () << std::endl;
    } while (input);

    return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */


