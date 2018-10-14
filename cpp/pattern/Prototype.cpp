/*
 * =====================================================================================
 *
 *       Filename:  Prototype.cpp
 *
 *    Description:  This is prototype pattern mainly used for performance improvement where
 *                  Object creation is costly operation.
 *
 *                  Example here is: bullet creation in which the common operation takes long time and
 *                  common for all type of bullets and there are some specific operation which varies with the type
 *
 *                  Prototype is mainly create the instance of object once and create copy of the same instance every time
 *                  when it is getting called for new creation. Here we will save the time required for creation.
 *
 *                  Code referred from http://cppnuts.com/prototype-design-pattern-cpp/
 *        Version:  1.0
 *        Created:  10/14/18 18:43:05
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
#include <string>
#include <memory>
#include <unordered_map>

using namespace std;

class Bullet {
    protected:
        string  _strBulletName;
        int     _iSpeed;
        int     _iFirePower;
        int     _iDamage;
        int     _iDirection;

    public:
        Bullet () { }

        Bullet (string strBulletName, int iSpeed, int iFirePower, int iDamage )
                :_strBulletName(strBulletName),
                 _iSpeed(iSpeed),
                 _iFirePower(iFirePower),
                 _iDamage(iDamage) { cout << " I am in the Bullet C'tor, the time required to create new instance is huge then coping my already created instance!!!" << endl; }

        virtual ~Bullet () { }

        virtual unique_ptr<Bullet> clone () = 0;

        void fire (int iDirection) {
            _iDirection = iDirection;

            cout << "Name       : " << _strBulletName << endl
                 << "Speed      : " << _iSpeed << endl
                 << "FirePower  : " << _iFirePower << endl
                 << "Damage     : " << _iDamage << endl
                 << "Direction  : " << _iDirection << endl
                 << endl ;

        }

};

class SimpleBullet : public Bullet {

    public:
        SimpleBullet (string strBulletName, int iSpeed, int iFirePower, int iDamage )
            :Bullet (strBulletName, iSpeed, iFirePower, iDamage ) { }

        virtual unique_ptr<Bullet> clone () {
            return make_unique<SimpleBullet> (*this);
        }
};

class PowerBullet : public Bullet {

    public:
        PowerBullet (string strBulletName, int iSpeed, int iFirePower, int iDamage )
            :Bullet (strBulletName, iSpeed, iFirePower, iDamage ) { }

        virtual unique_ptr<Bullet> clone () {
            return make_unique<PowerBullet> (*this);
        }
};

enum BulletType {
    SIMPLE,
    POWER
};


class BulletFactory {
    private:
        unordered_map<BulletType, unique_ptr<Bullet>, hash<int>> _mapBullets;

    public:
        BulletFactory () {
            _mapBullets[SIMPLE] = make_unique<SimpleBullet> ("Simple Bullet", 75, 50, 50);
            _mapBullets[POWER] = make_unique<SimpleBullet> ("Power Bullet", 100, 100, 100);
        }

        unique_ptr<Bullet> createBullet (BulletType eBulletType) {
            return _mapBullets[eBulletType]->clone ();
        }
};

int main () {
    BulletFactory bulletFactory;

    auto bullet = bulletFactory.createBullet (SIMPLE);
    bullet->fire (80);

    bullet = bulletFactory.createBullet (SIMPLE);
    bullet->fire (90);

    bullet = bulletFactory.createBullet(POWER);
    bullet->fire (100);

    bullet = bulletFactory.createBullet(POWER);
    bullet->fire (110);
}
