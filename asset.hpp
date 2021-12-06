#include <iostream>
#include <vector>

#ifndef OBSERVER_HPP
#define OBSERVER_HPP
#include "observer.hpp"
#endif

#ifndef INF
#define INF 1<<31
#endif

using namespace std;

class Account;
class Market;
class Observer;

class Asset
{
protected:
    bool liquid;
    // float value; implemented in subclasses
    Account* owner;

public:
    Asset()
    {
    }
    virtual ~Asset()
    {
    }
    
};

class Stock : public Asset, public Subject
{
protected:
    
    float value;
    float prev_value;

public:
    string name;
    string symbol;

    Stock(string n, string s, float v)
    {
        this->liquid = false;
        this->name = n;
        this->symbol = s;
        this->value = v;
        this->prev_value = 0;
    }

    //endpoint to print details of the stock
    void get_info()
    {
        cout << name << '\t' << symbol << '\t' << value << '\n';
    }
    
    // get endpoint for value
    float get_value() override
    {
        return this->value;
    }

    float get_prev_value()
    {
        return this->prev_value;
    }

    float set_value(float val)
    {
        this->prev_value = this->value;
        this->value = val;
        notify();
        return value;
    }

    void notify() override
    {
        for(auto e: observers)
        {
            e->update(this, value);
        }
    }

    ~Stock()
    {
    }

};
