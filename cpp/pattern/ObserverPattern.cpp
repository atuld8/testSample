/*
 * =====================================================================================
 *
 *       Filename:  ObserverPattern.cpp
 *
 *    Description:  This is example of observer pattern
 *
 *        Version:  1.0
 *        Created:  06/18/2016 15:19:27
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (),
 *   Organization:
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

class Subject;

class Observer {
   public:
      virtual void update(Subject * sub) = 0;
};


class Subject {
   public:
      virtual void registerObserver(Observer *observer) = 0;
      virtual void deregisterObserver(Observer *observer) = 0;
      virtual void notify() = 0;
};


class Loan : public Subject {

   public:
      Loan(): m_data(0) {

      }

      virtual void registerObserver(Observer *observer) {
         m_observerList.push_back(observer);
      }

      virtual void deregisterObserver(Observer *observer) {
         //vector<Observer*>::iterator it = std::find(m_observerList.begin(), m_observerList.end(),static_cast<const Observer *>(observer));
         for(vector<Observer *>::iterator it = m_observerList.begin(); it != m_observerList.end(); it++)
             if (*it == observer)
                m_observerList.erase(it);

      }

      virtual void notify();

      int getData() {
         return m_data;
      }

      void setData(int data) {
         m_data = data;
         notify();
      }

      virtual string type() {
         return "Loan";
      }

   private:
      vector<Observer *> m_observerList;
      int m_data;
};

class HomeLoan: public Loan {
   public:
      string type() {
         return "HomeLoan";
      }
};

class CarLoan: public Loan {
   public:
      string type() {
         return "CarLoan";
      }
};

class PersonalLoan: public Loan {
   public:
      string type() {
         return "PersonalLoan";
      }
};



class LoanObserver: public Observer {

   public:
      virtual void update(Subject * sub) = 0;

      virtual void addLoanObject(Loan * loan){
         m_ploan.push_back(loan);
      }

      virtual void printDataAndType () {
         cout << setfill('-') << setw(80) << "-" << setfill(' ') << endl;
         cout << std::setw(20) << "Type" << std::setw(20) << "Rate" << endl;
         cout << setfill('-') << setw(80) << "-" << setfill(' ') << endl;
         for (vector<Loan *>::iterator it = m_ploan.begin(); it != m_ploan.end(); it++) {
            Loan * loan  = *it;
            cout << std::setw(20) << loan->type() << std::setw(20) << (*it)->getData() << endl;
         }
         cout << setfill('-') << setw(80) << "-" << setfill(' ') << endl;
         cout << endl;

      }
   protected:
      vector<Loan *> m_ploan;
};

class Observer1: public LoanObserver {

   public:

      Observer1() {
      }

      virtual void update(Subject * sub) {
         cerr << "notification for Observer1: " << " from " << static_cast<Loan *>(sub)->type() << " about rate change " << static_cast<Loan *>(sub)->getData() << endl;
      }

      virtual void printDataAndType () {
         //cout << "\033[2J\033[1;1H";
         cout << endl;
         cout << "Observer1:" << endl;
         LoanObserver::printDataAndType();
      }
};

class Observer2: public LoanObserver {

   public:

      Observer2() {
      }

      virtual void update(Subject * sub) {
         cerr << "notification for Observer2: " << " from " << static_cast<Loan *>(sub)->type() << " about rate change " << static_cast<Loan *>(sub)->getData() << endl;
      }

};

class Observer3: public LoanObserver {

   public:

      Observer3() {
      }

      virtual void update(Subject * sub) {
         cerr << "notification for Observer3: " << " from " << static_cast<Loan *>(sub)->type() << " about rate change " << static_cast<Loan *>(sub)->getData() << endl;
      }

};


void Loan::notify() {

   for (vector<Observer *>::iterator it = m_observerList.begin(); it != m_observerList.end(); it++) {
      Observer * obs  = *it;
      obs->update(this);
   }
}

int main() {

   //Loan           * loan = new Loan();
   HomeLoan       * homeloan     = new HomeLoan();
   CarLoan        * carloan      = new CarLoan();
   PersonalLoan   * personalloan = new PersonalLoan();

   class Observer1 * ob1   = new Observer1();
   class Observer2 * ob2   = new Observer2();
   class Observer3 * ob3   = new Observer3();

   ob1->addLoanObject(personalloan);
   ob2->addLoanObject(personalloan);
   ob3->addLoanObject(personalloan);
   ob1->addLoanObject(homeloan);
   ob2->addLoanObject(homeloan);
   ob3->addLoanObject(homeloan);
   ob1->addLoanObject(carloan);
   ob2->addLoanObject(carloan);
   ob3->addLoanObject(carloan);

   personalloan->registerObserver(ob1);
   personalloan->registerObserver(ob2);
   personalloan->registerObserver(ob3);

   homeloan->registerObserver(ob1);
   homeloan->registerObserver(ob2);
   homeloan->registerObserver(ob3);

   carloan->registerObserver(ob1);
   carloan->registerObserver(ob2);
   carloan->registerObserver(ob3);

   int pid = fork();
   if (pid == 0)
   {
       int count = 4;
       while (count--) {
          ob1->printDataAndType();
          sleep (1);
          homeloan->setData(count);
       }
   } else {
      personalloan->setData(10);
      ob1->printDataAndType();
      sleep (1);
      homeloan->setData(20);
      sleep (1);
      carloan->setData(30);
      sleep (1);
      ob1->printDataAndType();
      sleep(5);
   }

   return 0;
}
