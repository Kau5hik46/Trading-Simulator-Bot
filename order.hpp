#include <iostream>
#include <set>
#include <cstdio>
#include <string>

#ifndef ACCOUNT_HPP
#define ACCOUNT_HPP
#include "account.hpp"
#endif

#ifndef ASSET_HPP
#define ASSET_HPP
#include "asset.hpp"
#endif

#ifndef MARKET_HPP
#define MARKET_HPP
#include "market.hpp"
#endif

using namespace std;

// class Market;
// class Account;

class Order
{
protected:
    static set<Order*> orders;
    static int num_orders;
    int order_number;
    string order;
    Account * account;
    Market * market;
    int side;
    int quantity;
    Stock* stock;
    bool limit;
public:
    Order(Market* m, int _s, string s, int q,  bool l = 0) // type = 0 => market order, type = 1 => limit
    {
        this->num_orders++;
        market = m;
        side = _s;
        quantity = q;
        limit = l;
        stock = market->get_stock(s);
    }

    Order* execute(Account* acc)
    {
        if(side > 0)
        {
            account = acc;
            float val = stock->get_value();
            val*=quantity;
            if(val < account->get_cash_balance())
            {
                account->withdraw(val);
                account->deposit(stock, quantity);
                set_details();
            }
            else
            {
                order = "Order" + to_string(order_number) + " unsuccessful due to insufficient balance\n\n";
            }
        }
        else if(side < 0)
        {
            account = acc;
            float val = stock->get_value();
            val*=quantity;
            if(val < account->get_cash_balance())
            {
                account->withdraw(val);
                account->subscribe(stock, quantity);
                set_details();
            }
            else
            {
                order = "Order" + to_string(order_number) + " unsuccessful due to insufficient balance\n\n";
            }
        }
        // orders.insert(this);       
        cout << this->get_details();
        // acc->information();
        return this; 
    }
    string set_details()
    {
        order = "Order successfully executed on day " + to_string(market->time - 1) + ":\n" + account->get_account_name() + " placed a ";
        string s = side > 0 ? "buy " : "sell ";
        s = limit? "limit order " : "market order ";
        order+=s;
        order+= "for " + stock->name + " for a quantity of " + to_string(quantity) + " ";
        order+= "at " + to_string(stock->get_value()) + "\n\n";

        return order;
    }

    string get_details()
    {
        return order;
    }
    void print_all()
    {
        for(auto e : orders)
            cout << e->get_details();
    }
    ~Order()
    {
        for(auto o : orders)
        {
            delete o;
        }
    }  
};

int Order::num_orders = 0;