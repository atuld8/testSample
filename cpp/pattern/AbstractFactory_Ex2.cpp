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
        virtual ~SmartInterface() {
        }

        virtual string Name() = 0;
};

class DumpInterface {
    public:
        virtual ~DumpInterface() {
        }

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

    virtual ~APhoneFactory() {
    }

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

class NOKIAFactory: public APhoneFactory {
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
                return new NOKIAFactory();

    return NULL;
}

void createInstanceOfEachBrandAndPrintDumpSmartModel(APhoneFactory::PHONE_FACTORIES phoneFactoryId, string phoneFactoryName) {

    APhoneFactory* factory = APhoneFactory::CreateFactory(phoneFactoryId);
    SmartInterface* smart  = factory->GetSmart();
    DumpInterface*  dump   = factory->GetDump();

    cout << "Dump  phone from " << phoneFactoryName.c_str() << " : " << dump->Name().c_str() << endl;
    cout << "Smart phone from " << phoneFactoryName.c_str() << " : " << smart->Name().c_str() << endl;

    delete smart;
    delete dump;
    delete factory;
}

int main(int argc, char *arv[]) {

    createInstanceOfEachBrandAndPrintDumpSmartModel(APhoneFactory::PHONE_FACTORIES::SAMSUNG, "Samsung");

    createInstanceOfEachBrandAndPrintDumpSmartModel(APhoneFactory::PHONE_FACTORIES::HTC, "HTC");

    createInstanceOfEachBrandAndPrintDumpSmartModel(APhoneFactory::PHONE_FACTORIES::NOKIA, "NOKIA");

    return 0;
}
