/*
 * =====================================================================================
 *
 *       Filename:  MementoEx2.cpp
 *
 *    Description:  memento pattern simple example for understanding
 *
 *        Version:  1.0
 *        Created:  11/20/2016 12:52:46
 *       Revision:  none
 *       Compiler:  gcc
 *
 * =====================================================================================
 */
#include <stdlib.h>

#include <iostream>
#include <vector>

class CMemento {
    public:
        CMemento (std::string &str) {
            m_strDataState = str;
        }

        std::string getDataState () {
            return m_strDataState;
        }

    private:
        std::string m_strDataState;
};


class COriginator {
    public:

        void set(std::string str) {
            std::cout << "Originator: setting the data to " << str << std::endl;
            m_strData =  str;
        }

        CMemento * saveToMemento() {
            std::cout << "Originator: saving data to memento " << m_strData << std::endl;
            return new CMemento(m_strData);
        }

        void restoreFromMemento ( CMemento *m) {
            m_strData = m->getDataState();
            std::cout << "Originator: restoring data from memento " << m_strData << std::endl;
        }

   private:
        std::string m_strData;
};


class CCaretaker {
    public:
        void addMemento (CMemento * m) {
            m_vMemento.push_back(m);
        }

        CMemento * getMemento(int index) {
            return m_vMemento[index];
        }

    private:
            std::vector<CMemento *>   m_vMemento;
};

int main () {
    CCaretaker * ct = new CCaretaker ();


    COriginator * org = new COriginator();

    org->set("state1");
    org->set("state2");

    ct->addMemento(org->saveToMemento());

    org->set("state3");

    ct->addMemento(org->saveToMemento());

    org->set("state4");

    ct->addMemento(org->saveToMemento());

    org->restoreFromMemento(ct->getMemento(1));
    org->restoreFromMemento(ct->getMemento(0));
    org->restoreFromMemento(ct->getMemento(1));
    ct->addMemento(org->saveToMemento());

    return 0;
}
