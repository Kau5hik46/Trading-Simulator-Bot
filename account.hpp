#include <iostream>
#include <vector>

#ifndef ASSET_HPP
#define ASSET_HPP
#include "asset.hpp"
#endif

using namespace std;

// Implemented the account system based on "Observer pattern"

// required endpoints
// -> deposit
// -> withdraw
// -> balance

class Stock;

// Concrete class Account which derives the value of assets from the class Subject with Observer dependency
class Account : public Observer // Account class inherited from Observer base class
{
private:
    static int num_accounts;
    float cash; // amount of liquid cash in the account
    float total_value; // total value of the account (asset value + cash value)
    string name; // Account holder name
    int ac_number; //. acoount number

public:

    Account(string n, float starting = 0) 
    // Name is compulsory parameter and starting value is optional parameter defaulted to 0
    {
        this->cash = 0;
        this->name = n;
        this->deposit(starting);
        ac_number = ++num_accounts;
        information();
    }

    // Endpoint to deposit cash
    void deposit(float add)
    {
        if(add>0)
        {
            this->cash += add;
            this->set_total_value();
        }
        else
        {
            cout << "Invalid amount to be deposited" << '\n';
        }
    }

    // endpoint to deposit stocks
    void deposit(Stock*s, int q)
    {
        this->subscribe(s, q);
        this->set_total_value();
    }

    string get_account_name()
    {
        return name;
    }

    int get_account_number()
    {
        return ac_number;
    }

    // endpoint to withdraw cash
    float withdraw(float amount)
    {
        if(amount > 0 and amount < cash)
        {
            cash-=amount;
            set_total_value();
            return this->get_total_value();
        }
        return 0;
    }

    // endpoint to withdraw stocks
    float withdraw(Stock* s, int q)
    {
        if(subjects[s]>=q)
        {
            subjects[s]-=q;
            this->deposit(s->get_value()*q);
        }
        set_total_value();
        return this->get_total_value();
    }

    // overrided method from baseclass 
    virtual void action(Stock*s) override
    {
        set_total_value();
        // information();
    }

    virtual void action(Subject*s) override
    {
        set_total_value();
        // information();
    }

    float set_total_value()
    {
        total_value = cash;
        for(auto e : subjects)
        {
           total_value += e.first->get_value()*e.second;
        }
        return total_value;
    }

    // endpoint to check total balance
    float get_total_value()
    {
        return total_value;
    }

    //endpoint to get cash balance
    float get_cash_balance()
    {
        return cash;
    }
    //endpoint to get asset value
    float get_asset_value()
    {
        return total_value - cash;
    }

    //utility function to print out all the data related to account
    void information()
    {
        cout << "Account: " << name << endl;
        cout << "Cash Balance: " << get_cash_balance() << endl;
        cout << "Asset Value: " << get_asset_value() << endl;
        cout << "Total Value: " << get_total_value() << endl;
        cout << endl;
    }

    ~Account(){}
};

int Account::num_accounts = 0;