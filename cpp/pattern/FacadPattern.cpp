/*
 * =====================================================================================
 *
 *       Filename:  FacadPattern.cpp
 *
 *    Description:  Facad pattern provide unified interface to client by encapsulating the complex subsystems.
 *                  Used to decouple the complex subsystem from its potential clients
 *
 *                  Reference: https://sourcemaking.com/design_patterns/facade/cpp/1
 *
 *        Version:  1.0
 *        Created:  10/17/18 22:54:01
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

using namespace std;

class MisDepartment {
    public:
        void submitNetworkRequest () { _state = 0; }

        bool checkOnStatus () {
            _state++;
            if (_state == Complete)
                return 1;
            return 0;
        }

    private:
        enum States {
            Received,                      DenyAllKnowledge,     ReferClientToFacilities,
            FacilitiesHasNotSentPaperwork, ElectricianIsNotDone, ElectricianDidItWrong,
            DispatchTechnician,            SignedOff,            DoesNotWork,
            FixElectriciansWiring,         Complete
        };
        int _state;
};

class ElectricianUnion {
    public:
        void submitNetworkRequest () { _state = 0; }

        bool checkOnStatus () {
            _state++;
            if (_state == Complete)
                return 1;
            return 0;
        }

    private:
        enum States {
            Received,             RejectTheForm,      SizeTheJob,       SmokeAndJokeBreak,
            WaitForAuthorization, DoTheWrongJob,      BlameTheEngineer, WaitToPunchOut,
            DoHalfAJob,           ComplainToEngineer, GetClarification, CompleteTheJob,
            TurnInThePaperwork,   Complete
        };
        int _state;
};

class FacilitiesDepartment {
    public:
        void submitNetworkRequest () { _state = 0; }

        bool checkOnStatus () {
            _state++;
            if (_state == Complete)
                return 1;
            return 0;
        }

    private:
        enum States {
            Received,                  AssignToEngineer,    EngineerResearches,      RequestIsNotPossible,
            EngineerLeavesCompany,     AssignToNewEngineer, NewEngineerResearches,
            ReassignEngineer,          EngineerReturns,     EngineerResearchesAgain,
            EngineerFillsOutPaperWork, Complete
        };
        int _state;
};

class FacilitiesFacade {
    public:
        FacilitiesFacade () { _count = 0; }

        void submitNetworkRequest () { _state = 0; }

        bool checkOnStatus () {
            _count++;

            /* Job request has just been received */
            if (_state == Received) {
                _state++;
                /* Forward the job request to the engineer */
                _engineer.submitNetworkRequest ();
                cout << "submitted to Facilities - " << _count <<
                    " phone calls so far" << endl;

            } else if (_state == SubmitToEngineer) {
                /* If engineer is complete, forward to electrician */
                if (_engineer.checkOnStatus ())
                {
                    _state++;
                    _electrician.submitNetworkRequest ();
                    cout << "submitted to Electrician - " << _count <<
                        " phone calls so far" << endl;
                }
            } else if (_state == SubmitToElectrician) {
                /* If electrician is complete, forward to technician */
                if (_electrician.checkOnStatus ()) {
                    _state++;
                    _technician.submitNetworkRequest ();
                    cout << "submitted to MIS - " << _count <<
                        " phone calls so far" << endl;
                }
            } else if (_state == SubmitToTechnician) {
                /* If technician is complete, job is done */
                if (_technician.checkOnStatus ())
                    return 1;
            }
            /* The job is not entirely complete */
            return 0;
        }

        int getNumberOfCalls () { return _count; }

    private:
        enum States {
            Received, SubmitToEngineer, SubmitToElectrician, SubmitToTechnician
        };

        int                  _state;
        int                  _count;
        FacilitiesDepartment _engineer;
        ElectricianUnion     _electrician;
        MisDepartment        _technician;
};

int main () {
    FacilitiesFacade facilities;

    facilities.submitNetworkRequest ();

    /* Keep checking until job is complete */
    while (!facilities.checkOnStatus ())
        ;

    cout << "job completed after only " << facilities.getNumberOfCalls () << " phone calls" << endl;
}

