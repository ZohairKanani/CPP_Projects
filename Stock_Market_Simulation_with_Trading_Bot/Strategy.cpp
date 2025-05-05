#include "Strategy.h"
#include <iostream>

Strategy::Strategy(): name("")
{
}

Strategy::Strategy(const string &name): name(name)
{
}

double Strategy::calculateMovingAverage(Market *market, int index, int window) const
{
    
    // Adjust starting index if the window goes out of bounds
    int startIndex = max(0, index - window + 1);

    // Calculate the sum of prices within the window
    double sum = 0.0;
    for (int i = startIndex; i <= index; ++i) {
        sum += market->getPrice(i);
    }

    // Calculate and return the moving average
    int numPrices = index - startIndex + 1;
    return sum / numPrices;
}

string Strategy::getName() const
{
    return name;
}
Strategy::~Strategy()
{
    
}