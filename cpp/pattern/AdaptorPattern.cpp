/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.

   * File Name : AdaptorPattern.cpp

   * Purpose : A wrapper class over existing interface so that user can reuse the implementation

   * Creation Date : 11-01-2015

   * Last Modified : Sun, Jan 11, 2015  7:38:34 PM

   * Created By : Atul_Das

   _._._._._._._._._._._._._._._._._._._._._.*/
#include <stdio.h>

class oldClass {
    public:
        void print_the_data() {
            printf("Printing the data using print_the_data call\n");
        }
};

class Interface {
    public:
    virtual ~Interface() {}
    virtual void printData() = 0;
};

class newClass : public Interface {
    public:
        void printData() {
            printf("transfering call to oldClass to perform task\n");
            oc.print_the_data();
        }

    private:
        oldClass oc;
};

int main() {
    Interface * interface = new newClass();
    
    interface->printData();

    delete interface;

    return 0;
}

