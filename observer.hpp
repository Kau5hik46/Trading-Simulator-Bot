#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>

using namespace std;

class Observer;
class Stock;


// Abstract Class Subject which will notify everytime there is a change in its value
class Subject
{

protected:
    set<Observer*> observers;

public:
    Subject(){}

    virtual ~Subject() = default;

    void attach(Observer* o)
    {
        observers.insert(o);
    }

    virtual void notify()
    {
    }

    virtual float get_value() = 0;

    void detach(Observer* o)
    {
        observers.erase(o);
    }
};

// Abstract class Observer which will perform some kind of action() whenever there is a notification from Subject
class Observer
{
protected:
    map<Subject*, int> subjects;

public:
    virtual ~Observer(){}

    void subscribe(Subject* sub, int quantity = 0)
    {
        if(subjects[sub])
        {
            subjects[sub] += quantity;
        }
        else
        {
            subjects[sub] = quantity;
        }
        sub->attach(this);
    }

    void unsubscribe(Subject* sub)
    {
        // subjects.erase(sub);
        sub->detach(this);
    }

    void update(Subject* sub, float val)
    {
        for(auto&e:subjects)
        {
            if(sub == e.first)
            {
                action(sub);
                break;
            }
        }
    }

    // virtual void action() = 0;
    virtual void action(Subject*) = 0;
    virtual void action(Stock*) = 0;
    virtual void get_info(){}
};
