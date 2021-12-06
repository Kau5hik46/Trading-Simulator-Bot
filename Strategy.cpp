#include <iostream>

using namespace std;

class Bill;

class Strategy
{
public:
    Strategy(){}
    virtual ~Strategy(){}
    virtual float get_multiplier() = 0; 
};

class Bill
{
protected:
    float tax;
    float totalPrice;
    Strategy* strategy;

public:

    Bill(Strategy* stg) : strategy(stg)
    {
        totalPrice = 0;
        tax = 0.8;
    }

    Bill(float tax, Strategy* stg) : strategy(stg)
    {
        totalPrice = 0;
        this->tax = tax;
    }

    void add(float price)
    {
        totalPrice+=price;
    }

    void set_strategy(Strategy* stg)
    {
        delete this->strategy;
        strategy = stg;
    }

    float checkout()
    {
        return (strategy->get_multiplier())*(1+tax)*totalPrice;
    }

    ~Bill()
    {
        delete this->strategy;
    }  
};

class NormalBill : public Strategy
{
protected:
    float multiplier;

public:
    NormalBill()
    {
        multiplier = 1;
    }
    NormalBill(float discount)
    {
        multiplier = 1;
        multiplier-=(discount/100);
    }

    virtual float get_multiplier() override
    {
        return multiplier;
    }

    ~NormalBill(){}
};

class HolidayBill : public Strategy
{
protected:
    float multiplier;

public:
    HolidayBill()
    {
        multiplier = 1.2;
    }
    HolidayBill(float discount)
    {
        multiplier = 1;
        multiplier-=(discount/100);
    }

    float get_multiplier() override
    {
        return multiplier;
    }

    ~HolidayBill(){}
};

class HappyHourBill : public Strategy
{
protected:
    float multiplier;

public:
    HappyHourBill()
    {
        multiplier = 0.8;
    }
    HappyHourBill(float discount)
    {
        multiplier = 1;
        multiplier-=(discount/100);
    }

    float get_multiplier() override
    {
        return multiplier;
    }

    ~HappyHourBill(){}
};


int main()
{
    // bill can also have custom tax rate as constructor parameter
    Bill bill(new NormalBill);
    // the add method provides an end point for adding cost
    bill.add(123);

    cout << "The total price for the normal bill is: " << bill.checkout() << endl;

    // We can adjust the discount by creating the strategy object with discount parameter
    float discount_percent = 20;
    
    // The Bill::set_strategy(Strategy*) provides an endpoint for the client to update the strategy in runtime
    bill.set_strategy(new HappyHourBill(discount_percent));
    cout << "The total price for the happy hour bill is: " << bill.checkout() << endl;
    
    bill.set_strategy(new HolidayBill(-discount_percent));
    cout << "The total price for the holiday bill is: " << bill.checkout() << endl;

    return 0;
}
