#include "WeightedTrendFollowingStrategy.h"
#include "Utils.h"
#include <cmath>

WeightedTrendFollowingStrategy::WeightedTrendFollowingStrategy() : TrendFollowingStrategy()
{
}

WeightedTrendFollowingStrategy::WeightedTrendFollowingStrategy(const string &name, int shortWindow, int longWindow) : TrendFollowingStrategy(name,shortWindow,longWindow)
{
}

double WeightedTrendFollowingStrategy::calculateExponentialWeight(int index) const
{
    return pow(1.1,index);
}

double WeightedTrendFollowingStrategy::calculateMovingAverage(Market *market, int index, int window) const
{
    int startIndex = max(0, index - window + 1);

    double wsum = 0.0;
    double esum = 0.0;
    for (int i = startIndex; i <= index; ++i) {
        wsum += market->getPrice(i) * calculateExponentialWeight(i);
        esum += calculateExponentialWeight(i);
    }
    return wsum / esum;
}

/*
The static function generateStrategySet(const string &name, int minShortWindow, int maxShortWindow, int stepShortWindow, int minLongWindow, int maxLongWindow, int stepLongWindow) generates a dynamic array of WeightedTrendFollowingStrategy objects. It iterates over the range of window sizes for the short and long windows, creating a new strategy for each combination. Minimum and maximum values are inclusive. Each strategy is named using this code snippet: baseName + "_" + to_string(shortWindow) + "_" + to_string(longWindow). For example, the baseName is "WeightedTrendFollowing", shortWindow is 10, and longWindow is 25, the strategy name would be "WeightedTrendFollowing_10_25".
*/

WeightedTrendFollowingStrategy **WeightedTrendFollowingStrategy::generateStrategySet(const string &baseName, int minShortWindow, int maxShortWindow, int stepShortWindow, int minLongWindow, int maxLongWindow, int stepLongWindow)
{
    int arrlen = (((maxShortWindow-minShortWindow)/stepShortWindow)+1) * (((maxLongWindow-minLongWindow)/stepLongWindow)+1);
    WeightedTrendFollowingStrategy **weightedtrendfolstrat = new WeightedTrendFollowingStrategy*[arrlen];
    

    int k = 0;
    for (int i = minShortWindow ; i <= maxShortWindow; i+=stepShortWindow)
    {
        
        for (int j = minLongWindow; j <= maxLongWindow; j+=stepLongWindow)
        {
            
            string fullstratname = baseName + "_" + to_string(i) + "_" + to_string(j);
            weightedtrendfolstrat[k++] = new WeightedTrendFollowingStrategy(fullstratname, i, j);
        }
    }
    return weightedtrendfolstrat;
}
