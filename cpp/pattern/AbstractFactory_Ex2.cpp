/*
 * =====================================================================================
 *
 *       Filename:  AbstractFactory_Ex2.cpp
 *
 *    Description:  AbstractFactory Example # 2
 *                  Example from http://www.codeproject.com/Articles/331304/Understanding-and-Implementing-Abstract-Factory
 *
 *        Version:  1.0
 *        Created:  10/24/2016 18:03:34
 *       Revision:  none
 *       Compiler:  gcc
 *
 * =====================================================================================
 */

#include <iostream>

using namespace std;


// Abstract Product
class SmartInterface {
    public:
        virtual string Name() = 0;
};

class DumpInterface {
    public:
        virtual string Name() = 0;
};



// Concreate Product
class Asha: public DumpInterface {
    public:
        string Name() {
            return "Asha";
        }
};

class Primo: public DumpInterface {
    public:
        string Name() {
            return "Primo";
        }
};

class Genie: public DumpInterface {
    public:
        string Name() {
            return "Genie";
        }
};

class GalaxyS2: public SmartInterface {
    public:
        string Name() {
            return "GalaxyS2";
        }
};

class Titan: public SmartInterface {
    public:
        string Name() {
            return "Titan";
        }
};

class Lumia: public SmartInterface {
    public:
        string Name() {
            return "Lumia";
        }
};



// Abstract Factory
class APhoneFactory {
    public:
        enum PHONE_FACTORIES {
            SAMSUNG,
            HTC,
            NOKIA
        };

    virtual SmartInterface* GetSmart() = 0;
    virtual DumpInterface*  GetDump()  = 0;

    static APhoneFactory*   CreateFactory(PHONE_FACTORIES factory);
};

// Concreate Factory
class SamsungFactory: public APhoneFactory {
    public:
        SmartInterface* GetSmart() {
            return new GalaxyS2();
        }

        DumpInterface*  GetDump() {
            return new Primo();
        }
};


class HTCFactory: public APhoneFactory {
    public:
        SmartInterface* GetSmart() {
            return new Titan();
        }

        DumpInterface*  GetDump() {
            return new Genie();
        }
};

class NOKIAFacotry: public APhoneFactory {
    public:
        SmartInterface* GetSmart() {
            return new Lumia();
        }

        DumpInterface*  GetDump() {
            return new Asha();
        }
};

APhoneFactory*  APhoneFactory::CreateFactory(PHONE_FACTORIES factory) {
    if (factory == APhoneFactory::PHONE_FACTORIES::SAMSUNG)
        return new SamsungFactory();
    else
        if (factory == PHONE_FACTORIES::HTC)
            return new HTCFactory();
        else
            if (factory == PHONE_FACTORIES::NOKIA)
                return new NOKIAFacotry();

    return NULL;
}

int main(int argc, char *arv[]) {
    APhoneFactory* factory = APhoneFactory::CreateFactory(APhoneFactory::PHONE_FACTORIES::SAMSUNG);
    cout << "Dump  phone from Samsung : " << factory->GetDump()->Name() << endl;
    cout << "Smart phone from Samsung : " << factory->GetSmart()->Name() << endl;
    delete factory;


    factory = APhoneFactory::CreateFactory(APhoneFactory::PHONE_FACTORIES::HTC);
    cout << "Dump  phone from HTC     : " << factory->GetDump()->Name() << endl;
    cout << "Smart phone from HTC     : " << factory->GetSmart()->Name() << endl;
    delete factory;

    factory = APhoneFactory::CreateFactory(APhoneFactory::PHONE_FACTORIES::SAMSUNG);
    cout << "Dump  phone from NOKIA   : " << factory->GetDump()->Name() << endl;
    cout << "Smart phone from NOKIA   : " << factory->GetSmart()->Name() << endl;
    delete factory;

    return 0;
}
