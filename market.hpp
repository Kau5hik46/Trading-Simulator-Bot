#include <iostream>
#include <vector>
#include <unistd.h>
#include "csvhandler.hpp"

#ifndef ASSET_HPP
#define ASSET_HPP
#include "asset.hpp"
#endif

// #include "observer.hpp"

using namespace std;

// Concrete class Market that holds the data of stocks and updates them accordingly
class Market
{
    CSV* market_data; //input data
    int time; // day wise time data
    map<string, Stock*> stocks; // stock names and pointer pairs
    
public:
    Market(CSV* ip)
    {
        time = 2; //input data column 3
        market_data = ip; // data copy
        make_stocks(); 
    }

    // utility function to create different stocks dynamically
    void make_stocks()
    {
        auto d = market_data->data;
        for(int i = 1; i < d.size(); i++)
        {
            Stock* n = new Stock(d[i][0], d[i][1], stof(d[i][time]));
            stocks[d[i][0]] = n;
        }
        current_info();
    }

    // utility function that returns all the stocks as a set
    set<Stock*> get_all_stocks()
    {
        set<Stock*> s;
        for(auto e : stocks)
            s.insert(e.second);
        return s;
    }

    // utility function that returns the stocks based on its name
    Stock* get_stock(string s)
    {
        if(stocks[s])
            return stocks[s];
        return nullptr;
    }

    // Advances the time by one unit
    void advance()
    {
        time++;
        auto d = market_data->data;
        for(int i = 1; i < d.size(); i++)
        {
            try
            {
                stocks[d[i][0]]->set_value(stof(d[i][time]));
            }
            catch(const std::invalid_argument& ia)
            {
            }
            
        }
        current_info();
    }

    // prints the information of all the stocks at one place based on the current price
    void current_info()
    {
        for(auto i : stocks)
        {
            i.second->get_info();
        }
        cout << endl;
    }

    // endpoint to start the market cycle
    void run()
    {
        while(time < market_data->data[0].size())
        {
            sleep(1); // takes rest for 1 second before each execution
            this->advance();
        }
    }

    ~Market()
    {
        for(auto e:stocks)
            delete e.second;
    }
    
};