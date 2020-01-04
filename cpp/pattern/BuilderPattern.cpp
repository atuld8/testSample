/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.

   * File Name : BuilderPattern.cpp

   * Purpose :

   * Creation Date : 11-01-2015

   * Last Modified : Sun, Jan 11, 2015  2:49:45 PM

   * In BuilderPattern, we have builder class which has all the methods to build the product.
   * In case of kid meals, he can knows what meal contents. Burger, kids toy, cold drink, fries.
   * receiver/construction class is resposible for algorithm to build the product
   _._._._._._._._._._._._._._._._._._._._._.
*/
#include <stdio.h>
#include <string>

using std::string;

class Animal {
    public:

       virtual ~Animal() {}

       string getHead() { return m_head; }
       void setHead(string  str) { m_head = str; }

       string getBody() { return m_body; }
       void setBody(string  str) { m_body = str; }

       string getLeg() { return m_leg; }
       void setLeg(string  str) { m_leg = str; }

       string getArm() { return m_arm; }
       void setArm(string  str) { m_arm = str; }

       string getTail() { return m_tail; }
       void setTail(string  str) { m_tail = str; }

       void showresult(){
           printf("%s%s%s%s%s", m_head.c_str(), m_body.c_str(), m_leg.c_str(), m_arm.c_str(), m_tail.c_str());
           eat();
       }

    // Other logic to keep value / information about Animal
    protected:

       virtual void eat() = 0;

       string m_head;
       string m_body;
       string m_leg;
       string m_arm;
       string m_tail;
};

class MonkeyAnimal: public Animal {
    protected:
       virtual void eat() {
         printf ("\tI like Banana\n");
       }
};

class KittyAnimal: public Animal {
    protected:
    virtual void eat() {
        printf ("\tI like Milk\n");
    }

};

class AnimalToyBuilder {
    public:
        virtual ~AnimalToyBuilder() {
        }

        virtual void BuildAnimalHead() = 0;
        virtual void BuildAnimalBody() = 0;
        virtual void BuildAnimalLeg() = 0;
        virtual void BuildAnimalArm() = 0;
        virtual void BuildAnimalTail() = 0;

        Animal * getresult(){
            return m_animal;
        }
    protected:
        Animal * m_animal;
};

class MonkeyAnimalToyBuilder: public AnimalToyBuilder {
    public:
        virtual void BuildAnimalHead();
        virtual void BuildAnimalBody();
        virtual void BuildAnimalLeg();
        virtual void BuildAnimalArm();
        virtual void BuildAnimalTail();

        MonkeyAnimalToyBuilder();
        ~MonkeyAnimalToyBuilder();
};

MonkeyAnimalToyBuilder::MonkeyAnimalToyBuilder() {
    m_animal = new MonkeyAnimal();
}

MonkeyAnimalToyBuilder::~MonkeyAnimalToyBuilder() {
    if (m_animal != NULL){
        delete m_animal;
    }
}

void MonkeyAnimalToyBuilder::BuildAnimalHead() {
    m_animal->setHead("\tMonkey's Head is created\n");
}

void MonkeyAnimalToyBuilder::BuildAnimalBody() {
    m_animal->setBody("\tMonkey's Body is created\n");
}

void MonkeyAnimalToyBuilder::BuildAnimalLeg() {
    m_animal->setLeg("\tMonkey's Leg is created\n");
}

void MonkeyAnimalToyBuilder::BuildAnimalArm() {
    m_animal->setArm("\tMonkey's Arm is created\n");
}

void MonkeyAnimalToyBuilder::BuildAnimalTail() {
    m_animal->setTail("\tMonkey's Tail is created\n");
}

class KittyAnimalToyBuilder: public AnimalToyBuilder {
    public:
        virtual void BuildAnimalHead();
        virtual void BuildAnimalBody();
        virtual void BuildAnimalLeg();
        virtual void BuildAnimalArm();
        virtual void BuildAnimalTail();

        KittyAnimalToyBuilder();
        ~KittyAnimalToyBuilder();
};

KittyAnimalToyBuilder::KittyAnimalToyBuilder() {
    m_animal = new KittyAnimal();
}

KittyAnimalToyBuilder::~KittyAnimalToyBuilder() {
    if (m_animal != NULL){
        delete m_animal;
    }
}

void KittyAnimalToyBuilder::BuildAnimalHead() {
    m_animal->setHead("\tKitty's Head is created\n");
}

void KittyAnimalToyBuilder::BuildAnimalBody() {
    m_animal->setBody("\tKitty's Body is created\n");
}

void KittyAnimalToyBuilder::BuildAnimalLeg() {
    m_animal->setLeg("\tKitty's Leg is created\n");
}

void KittyAnimalToyBuilder::BuildAnimalArm() {
    m_animal->setArm("\tKitty's Arm is created\n");
}

void KittyAnimalToyBuilder::BuildAnimalTail() {
    m_animal->setTail("\tKitty's Tail is created\n");
}

/////// constructor

class Kid {
    public:
        Kid(string name, AnimalToyBuilder * atb):m_name(name) {
            m_atb = atb;
        }

        void SetAnimalToyBuilder(AnimalToyBuilder * atb) {
            m_atb = atb;
        }

        void makeToy() {
            m_atb->BuildAnimalHead();
            m_atb->BuildAnimalBody();
            m_atb->BuildAnimalLeg();
            m_atb->BuildAnimalArm();
            m_atb->BuildAnimalTail();
        }

        string getName() { return m_name; }
    private:
        string m_name;
        AnimalToyBuilder * m_atb;
};

int main() {
    AnimalToyBuilder * atb = new MonkeyAnimalToyBuilder();
    Kid kid("Reva", atb);
    kid.makeToy();
    printf ("kid %s has built the Monkey\n", kid.getName().c_str());
    atb->getresult()->showresult();
    delete atb;

    AnimalToyBuilder * atb1 = new KittyAnimalToyBuilder();
    kid.SetAnimalToyBuilder(atb1);
    kid.makeToy();
    printf ("kid %s has built the Kitty\n", kid.getName().c_str());
    atb1->getresult()->showresult();
    delete atb1;
}


/*
vim:set makeopt=g++\ %
 * */
