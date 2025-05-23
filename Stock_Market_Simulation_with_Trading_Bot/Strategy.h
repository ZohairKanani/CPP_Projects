#ifndef STRATEGY_H
#define STRATEGY_H

#include <string>
#include "Market.h"

using namespace std;

const int EVALUATION_WINDOW = 100;

enum Action
    {
        BUY,
        SELL,
        HOLD
    };

class Strategy
{
private:
    string name;
    // TODO: fill out this part if needed

protected:
    
    // TODO: fill out this part if needed
    
public:
    
    Strategy();
    Strategy(const string& name);
    virtual ~Strategy();

    string getName() const;
    virtual Action decideAction(Market *market, int index, double currentHolding) const = 0;
    virtual double calculateMovingAverage(Market *market, int index, int window) const;
    // TODO: fill out this part if needed
};

#endif