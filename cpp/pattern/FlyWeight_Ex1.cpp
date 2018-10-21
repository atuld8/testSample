/*
 * =====================================================================================
 *
 *       Filename:  FlyWeight_Ex1.cpp
 *
 *    Description:  FlyWeight pattern used when we need large number of similar objects to perform the operation
 *                  We can use already existing object to perform the operation.
 *
 *                  Some properties like object are immutable i.e. can not be changed once created.
 *                  There are 2 types of properties these object could have, Intrinsic which are common among property amoung the objects
 *                  and extrinsic which are specific to the instance.
 *
 *                  Example: Counter strike game, where Terrorist has common property called task i.e. plant the bomb. This is intrisic property
 *                  but Terrorist can carry different weapon during the activity hence it is extrinsic property
 *
 *        Version:  1.0
 *        Created:  10/18/18 22:25:40
 *       Revision:  none
 *       Compiler:  gcc
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <iostream>
#include <string>
#include <map>
#include <cstdlib>

using namespace std;

class Player {
    public:
        virtual void assignWeapon (string strWeapon) = 0;

        virtual void mission () = 0;

        virtual string getType () = 0;
};


class Terrorist : public Player {
    public:

        Terrorist () {
            _strTask = "Plant the bomb";
            _strType = "Terrorist";

            cout << "In the Terrorist c'tor" << endl;
        }

        virtual void assignWeapon (string strWeapon) {
            _strWeapon = strWeapon;
        }

        virtual void mission () {
            cout << "Terrorist with the weapon : " <<  _strWeapon << " to perform the task : " << _strTask << endl;
        }

        virtual string getType () {
            return _strType;
        }

    private:
        // intrinsic
        string _strTask;
        string _strType;

        // extrinsic
        string _strWeapon;
};

class CounterTerrorist : public Player {
    public:

        CounterTerrorist () {
            _strTask = "Diffuse the bomb";
            _strType = "CounterTerrorist";

            cout << "In the CounterTerrorist c'tor" << endl;
        }

        virtual void assignWeapon (string strWeapon) {
            _strWeapon = strWeapon;
        }

        virtual void mission () {
            cout << "CounterTerrorist with the weapon : " <<  _strWeapon << " to perform the task : " << _strTask << endl;
        }

        virtual string getType () {
            return _strType;
        }

    private:
        // intrinsic
        string _strTask;
        string _strType;

        // extrinsic
        string _strWeapon;
};

enum PLAYER_TYPE {
    TERRORIST_PLAYER,
    COUNTER_TERRORIST_PLAYER,
    PLAYER_TYPE_COUNT
};

enum WEAPONS_TYPE {
    AK47,
    MAVERICK,
    GUT_KNIFE,
    DESERT_EAGLE,
    WEAPON_TYPE_COUNT
};

string strWeaponTypeDesc [] = { "AK47", "Naverick", "Gut Knife", "Desert Eagle" };

class PlayerFactory {

    public:

        static Player * getPlayer (PLAYER_TYPE ePlayerType) {

            if (_mapPlayerType.find (ePlayerType) == _mapPlayerType.end ()) {

                switch (ePlayerType) {
                    case TERRORIST_PLAYER:
                        _mapPlayerType.insert (pair<PLAYER_TYPE, Player*> (TERRORIST_PLAYER, new Terrorist ()));
                        break;

                    case COUNTER_TERRORIST_PLAYER:
                        _mapPlayerType.insert (pair<PLAYER_TYPE, Player*> (COUNTER_TERRORIST_PLAYER, new CounterTerrorist ()));
                        break;

                    default:
                        cout << "No such type of player" << endl;
                }
            }

            map<PLAYER_TYPE,Player *>::iterator itPlayerType = _mapPlayerType.find (ePlayerType);
            if (itPlayerType != _mapPlayerType.end ())
                return itPlayerType->second;

            return NULL;
        }

    public:
        static map<PLAYER_TYPE, Player *> _mapPlayerType;
};

map<PLAYER_TYPE, Player *> PlayerFactory::_mapPlayerType;

PLAYER_TYPE getRandomPlayerType () {
    return static_cast<PLAYER_TYPE> (rand () % static_cast<int> (PLAYER_TYPE_COUNT));
}

WEAPONS_TYPE getRandomWeaponType () {
    return static_cast<WEAPONS_TYPE> (rand () % static_cast<int> (WEAPON_TYPE_COUNT));
}

int main () {

    for (int counter = 0; counter < 10; counter++) {

        Player * pPlayer = PlayerFactory::getPlayer (getRandomPlayerType ());

        pPlayer->assignWeapon (strWeaponTypeDesc [getRandomWeaponType ()]);

        pPlayer->mission ();
    }
}
