#include "MeanReversionStrategy.h"
#include "Utils.h"
#include <cmath>
#include <iostream>

MeanReversionStrategy::MeanReversionStrategy() : Strategy(), window(0), threshold(1)
{
}

MeanReversionStrategy::MeanReversionStrategy(const string &name, int window, int threshold): Strategy(name),window(window), threshold(threshold)
{
}

Action MeanReversionStrategy::decideAction(Market *market, int index, double currentHolding) const
{
    double MA = calculateMovingAverage(market, index, window);
    double ta = (threshold/100.0)*MA;
    if (currentHolding == 1.0 && market->getPrice(index) > (MA + ta))
    {
        //currentHolding = 0.0;
        return SELL;
    }
    else if (currentHolding == 0.0 && market->getPrice(index) < (MA - ta))
    {
        //currentHolding = 1.0;
        return BUY;
    }
    return HOLD;
}

MeanReversionStrategy **MeanReversionStrategy::generateStrategySet(const string &baseName, int minWindow, int maxWindow, int windowStep, int minThreshold, int maxThreshold, int thresholdStep)
{
    int arrlen = (((maxWindow-minWindow)/windowStep)+1) * (((maxThreshold-minThreshold)/thresholdStep)+1);
    MeanReversionStrategy **meanrevstrat = new MeanReversionStrategy*[arrlen];
    
    int k = 0;

    for (int i = minWindow ; i <= maxWindow; i+=windowStep)
    {
        for (int j = minThreshold; j <= maxThreshold; j+=thresholdStep)
        {
            string fullstratname = baseName + "_" + to_string(i) + "_" + to_string(j);
            meanrevstrat[k++] = new MeanReversionStrategy(fullstratname, i, j);
        }
    }
    return meanrevstrat;
}