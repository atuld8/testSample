/*
 * =====================================================================================
 *
 *       Filename:  Mediator.cpp
 *
 *    Description:  When we partition the system into many objects, we enhance the usability of the system but
 *                  any proliferation of interaction between these objects can hamper the enhancement.
 *                  To avoid this situation, we can encapsulate the interaction between these objects into different object like Mediator.
 *                  Mediator is responsible for interaction between these objects.
 *
 *                  Example, Dialogbox objects act like Mediator where small object could be file, directory, filter, selections.
 *                  when there is change is any of small object changes the above objects state.
 *                  ChildWidget are file, dir, filter, selection. Child widget does not care, who is the siblings
 *                  but it delegate the change to parent dialog for further action.
 *                  Parent handle the collective behaviour and interact with the objects.
 *
 *        Version:  1.0
 *        Created:  10/25/18 20:41:38
 *       Revision:  none
 *       Compiler:  gcc
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// This is Mediator class which handle the interaction between the objects
class FileSelectionDialog;


class Widget {

    public:
        Widget (FileSelectionDialog *mediator, const string & name) {

            _mediator = mediator;
            _name     = name;
        }

        virtual ~Widget() {
        }

        virtual void changed ();
        virtual void updateWidget () = 0;
        virtual void queryWidget  ()  = 0;

    protected:
        string _name;

    private:
        FileSelectionDialog * _mediator;
};


class List : public Widget {
    public:
        List (FileSelectionDialog * dir, const string & name) : Widget (dir, name) { }

        void updateWidget () {
            cout << "\t" << _name << " list updated " << endl;
        }

        void queryWidget () {
            cout << "\t" << _name << " list queried " << endl;
        }
};

class Edit : public Widget {
    public:
        Edit (FileSelectionDialog * dir, const string & name) : Widget (dir, name) { }

        void updateWidget () {
            cout << "\t" << _name << " edit updated " << endl;
        }

        void queryWidget () {
            cout << "\t" << _name << " edit queried " << endl;
        }

};


class FileSelectionDialog {

    public:
        enum WidgetType {
            FILTER_EDIT,
            DIR_LIST,
            FILE_LIST,
            SELECTION_EDIT,
            WidgetTypeCount
        };

        FileSelectionDialog () : _component (10) {
            _component [FILTER_EDIT]    = new Edit (this, "Filter");
            _component [DIR_LIST]       = new List (this, "Dir");
            _component [FILE_LIST]      = new List (this, "File");
            _component [SELECTION_EDIT] = new Edit (this, "Selection");
        }

        ~FileSelectionDialog () {
            for (size_t i = 0; i < WidgetTypeCount; i++)
                delete _component [i];
        }

        void handleEvent (WidgetType wt) {
            _component [wt]->changed ();
        }

        virtual void widgetChanged (Widget * changedWidget) {

            if (changedWidget == _component [FILTER_EDIT]) {

                _component [FILTER_EDIT]->queryWidget ();
                _component [DIR_LIST]->updateWidget ();
                _component [FILE_LIST]->updateWidget ();
                _component [SELECTION_EDIT]->updateWidget ();

            } else if (changedWidget == _component [DIR_LIST]) {

                _component [DIR_LIST]->queryWidget ();
                _component [FILTER_EDIT]->updateWidget ();
                _component [FILE_LIST]->updateWidget ();
                _component [SELECTION_EDIT]->updateWidget ();

            } else if (changedWidget == _component [FILE_LIST]) {

                _component [FILE_LIST]->queryWidget ();
                _component [SELECTION_EDIT]->updateWidget ();

            } else if (changedWidget == _component [SELECTION_EDIT]) {

                _component [SELECTION_EDIT]->queryWidget ();
                cout << "\tFile Selected and given to caller" << endl;
            }
        }

    private:
        std::vector<Widget *> _component;
};

void Widget::changed () {
    _mediator->widgetChanged (this);
}

int main () {
    FileSelectionDialog fileSelectionDialog;

    //Below are the sequence of events occurred

    //1. After opening the dialog box, user changed the filter
    cout << "FileSelectionDialog is opened...." << endl;
    cout << endl << "Filter updating..." << endl;
    fileSelectionDialog.handleEvent (FileSelectionDialog::WidgetType::FILTER_EDIT);

    //2. Dir selection
    cout << endl << "Dir updating..." << endl;
    fileSelectionDialog.handleEvent (FileSelectionDialog::WidgetType::DIR_LIST);

    //3. File selection
    cout << endl << "File updating..." << endl;
    fileSelectionDialog.handleEvent (FileSelectionDialog::WidgetType::FILE_LIST);

    //4. Update selection
    cout << endl << "Selection updating..." << endl;
    fileSelectionDialog.handleEvent (FileSelectionDialog::WidgetType::SELECTION_EDIT);
    return 0;

}
