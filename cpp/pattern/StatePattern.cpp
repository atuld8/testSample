/*
 * =====================================================================================
 *
 *       Filename:  StatePattern.cpp
 *
 *    Description: The State pattern is a solution to the problem of how to make behavior depend on state.
 *
 *        Context Class:     This class is the one which has the states. The application will be using (interfering with) this class. The class is responsible to maintain current state.
 *        State Class:       This is an abstract base class which can hold the different states (sub classes). The context class will be using this class pointer as its member to point the current state.
 *        Concentrate Class: This class implements the behavior of the state and behavior of the object.
 *
 *        Version:  1.0
 *        Created:  11/10/18 12:06:18
 *       Revision:  none
 *       Compiler:  gcc
 *
 *        Example: In this example, we are displaying state of the sun like morning, afternoon, evening and night.
 *
 * =====================================================================================
 */
#include <stdlib.h>

#include <string>
#include <iostream>

// State Class
class CBaseState {
    public:
        virtual ~CBaseState () {}

        virtual CBaseState * getNextState () = 0;
        virtual const char * ToString () = 0;
};


// Concentrate class
class CMorning : public CBaseState {
    public:
        virtual CBaseState * getNextState ();
        virtual const char * ToString () { return "Morning"; }
};

class CAfternoon : public CBaseState {
    public:
        virtual CBaseState * getNextState ();
        virtual const char * ToString () { return "Afternoon"; }
};

class CEvening : public CBaseState {
    public:
        virtual CBaseState * getNextState ();
        virtual const char * ToString () { return "Evening"; }
};

class CNight : public CBaseState {
    public:
        virtual CBaseState * getNextState ();
        virtual const char * ToString () { return "Night"; }
};

CBaseState * CMorning::getNextState () {
    return new CAfternoon;
}

CBaseState * CAfternoon::getNextState () {
    return new CEvening;
}

CBaseState * CEvening::getNextState () {
    return new CNight;
}

CBaseState * CNight::getNextState () {
    return new CMorning;
}


// Context class
class CSun {
    public:
        CSun (CBaseState * pContext) {
            m_pCurrentState = pContext;
        }

        virtual ~CSun () {
            if (m_pCurrentState)
                delete m_pCurrentState;
        }

        void changeSate () {
            if (m_pCurrentState) {
                CBaseState * pState = m_pCurrentState->getNextState ();
                delete m_pCurrentState;
                m_pCurrentState = pState;
            }
        }

        const char * getCurrentState () {
            if (m_pCurrentState)
                return m_pCurrentState->ToString ();

            return "";
        }

    protected:
        CBaseState * m_pCurrentState;
};

int main () {
    CSun sun (new CMorning);
    printf ("\n\n Sun is saying, Good %s\n", sun.getCurrentState ());

    sun.changeSate ();
    printf ("\n\n Sun is saying, Good %s\n", sun.getCurrentState ());

    sun.changeSate ();
    printf ("\n\n Sun is saying, Good %s\n", sun.getCurrentState ());

    sun.changeSate ();
    printf ("\n\n Sun is saying, Good %s\n", sun.getCurrentState ());

    sun.changeSate ();
    printf ("\n\n Sun is saying, Good %s\n", sun.getCurrentState ());

    return 0;
}
