#include "TrendFollowingStrategy.h"
#include "Utils.h"
#include <iostream>

TrendFollowingStrategy::TrendFollowingStrategy() : Strategy()
{
}

TrendFollowingStrategy::TrendFollowingStrategy(const std::string &name, int shortWindow, int longWindow) : Strategy(name), shortMovingAverageWindow(shortWindow), longMovingAverageWindow(longWindow)
{
}

Action TrendFollowingStrategy::decideAction(Market *market, int index, double currentHolding) const 
{
    double MA_short = calculateMovingAverage(market,index,shortMovingAverageWindow);
    double MA_long = calculateMovingAverage(market, index, longMovingAverageWindow);
    if (MA_short > MA_long && currentHolding == 0.0)
    {
        return BUY;
    }
    else if (MA_short < MA_long && currentHolding == 1.0)
    {
        return SELL;
    }
    return HOLD;
}

TrendFollowingStrategy **TrendFollowingStrategy::generateStrategySet(const string &baseName, int minShortWindow, int maxShortWindow, int stepShortWindow, int minLongWindow, int maxLongWindow, int stepLongWindow)
{
    int arrlen = (((maxShortWindow-minShortWindow)/stepShortWindow)+1) * (((maxLongWindow-minLongWindow)/stepLongWindow)+1);
    TrendFollowingStrategy **trendfolstrat = new TrendFollowingStrategy*[arrlen];
    
    int k = 0;

    for (int i = minShortWindow ; i <= maxShortWindow; i+=stepShortWindow)
    {
        for (int j = minLongWindow; j <= maxLongWindow; j+=stepLongWindow)
        {
            string fullstratname = baseName + "_" + to_string(i) + "_" + to_string(j);
            trendfolstrat[k++] = new TrendFollowingStrategy(fullstratname, i, j);
        }
    }
    return trendfolstrat;
}
