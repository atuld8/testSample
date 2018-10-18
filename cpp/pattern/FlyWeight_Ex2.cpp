/*
 * =====================================================================================
 *
 *       Filename:  FlyWeight_Ex2.cpp
 *
 *    Description:  FlyWeight pattern.
 *                  In this example, X is intrinsic and Y is extrinsic values.
 *                  Ojbect does not keep any state of operation, it is expected that client should send to object every time.
 *
 *        Version:  1.0
 *        Created:  10/19/18 00:26:30
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

using namespace std;

class Gazillion
{
    public:
        Gazillion(int value_one)
        {
            m_value_one = value_one;
            cout << "ctor: " << m_value_one << '\n';
        }
        ~Gazillion()
        {
            cout << m_value_one << ' ';
        }
        void report(int value_two)
        {
            cout << m_value_one << value_two << ' ';
        }
    private:
        int m_value_one;
};

class Factory
{
    public:
        static Gazillion *get_fly(int in)
        {
            if (!s_pool[in])
                s_pool[in] = new Gazillion(in);
            return s_pool[in];
        }
        static void clean_up()
        {
            cout << "dtors: ";
            for (int i = 0; i < X; ++i)
                if (s_pool[i])
                    delete s_pool[i];
            cout << '\n';
        }
        static int X, Y;
    private:
        static Gazillion *s_pool[];
};

int Factory::X = 6, Factory::Y = 10;
Gazillion *Factory::s_pool[] = 
{
    0, 0, 0, 0, 0, 0
};

int main()
{
    for (int i = 0; i < Factory::X; ++i)
    {
        for (int j = 0; j < Factory::Y; ++j)
            Factory::get_fly(i)->report(j);
        cout << '\n';
    }
    Factory::clean_up();
}
