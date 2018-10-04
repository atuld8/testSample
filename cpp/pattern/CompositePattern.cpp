/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.

   * File Name : compositePattern.cpp

   * Purpose :

   * Creation Date : 11-01-2015

   * Last Modified : Sun, Jan 11, 2015  7:00:30 PM

   * Created By : Atul_Das

   * This pattern represent tree structure data or objects like xml, directory
   _._._._._._._._._._._._._._._._._._._._._.*/
#include <stdio.h>
#include <string>
#include <vector>

using std::string;
using std::vector;

class Component {
    public:
        virtual void execute(string print) = 0;
};

class Leaf : public Component {
 public:

     Leaf(int num) {
         data = num;
     }

     void execute(string print) {
         printf ("%sLeaf %d\n", print.c_str(), data);  
     }

 protected:
     int data;
};

class Composite: public Component {
    public:

     void add(Component * comp) {
         m_comp.push_back(comp);
     }

     void execute(string print) {

         printf("%sComposite-\n", print.c_str());
         
         string newprint("\t");
         newprint += print;
         
         for (vector<Component *>::iterator it = m_comp.begin(); it != m_comp.end(); it++) {
             (*it)->execute(newprint);
         }
     }

    private:
        vector<Component *> m_comp; 
};


int main() {
    Composite * composite = new Composite();

    composite->add(new Leaf(10));
    composite->add(new Leaf(20));
    composite->add(new Leaf(30));

    Composite * composite2 = new Composite();
    composite2->add(new Leaf(1));
    composite2->add(new Leaf(2));
    composite2->add(new Leaf(3));

    composite->add(composite2);

    composite->execute("");
}
