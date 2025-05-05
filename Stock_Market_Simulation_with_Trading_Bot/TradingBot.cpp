#include "TradingBot.h"
#include <limits>

TradingBot::TradingBot(Market *market, int initialCapacity): market(market),availableStrategies(new Strategy*[initialCapacity]),strategyCount(0),strategyCapacity(initialCapacity)
{
    for(int i = 0 ; i < strategyCapacity ; ++i)
    {
        availableStrategies[i] = nullptr;
    }
}

TradingBot::~TradingBot()
{
    for (int i = 0 ; i < strategyCount; ++i)
    {
        delete availableStrategies[i];
    }
    delete[] availableStrategies;
    availableStrategies = nullptr;
}

void TradingBot::addStrategy(Strategy *strategy)
{
    if (strategyCount >= strategyCapacity)
    {  
        int newCapacity = strategyCapacity * 2;
        
        // Allocate new array with larger capacity
        Strategy** newStrategies = new Strategy*[newCapacity];
        
        // Copy existing strategies to the new array
        for (int i = 0; i < newCapacity; ++i)
        {
            if (i < strategyCapacity)
            {
                newStrategies[i] = availableStrategies[i];
            }
            else
            {
                newStrategies[i] = nullptr;
            }
        }
        
        // Delete old array
        delete[] availableStrategies;
        
        // Update to new array and capacity
        availableStrategies = newStrategies;
        strategyCapacity = newCapacity;
    }
    availableStrategies[strategyCount++] = strategy;
    
}
/*
runSimulation(): This function executes the trading simulation using the available strategies for last 101 days. It returns a SimulationResult containing the best strategy and its total return. You should calculate return as follows:
1. Start with zero cumulative profit.

2. For each trading day, choose a strategy and decide on an action:

BUY: You can only perform a buy action if you currently do not hold a stock.
SELL: You can sell the stock only if you still hold one.
HOLD: No change in your holding position.
3. If the bot buys the stock, it records its purchase price; if it sells the stock, it calculates the profit (difference between current price and purchase price) and adds it to the cumulative profit.

4. On the last trading day, if you still hold a stock, add the price difference between the current price and the purchase price to the cumulative profit. This refers to the potential profit if you sell the stock.


SimulationResult struct
The provided code also includes a SimulationResult struct that stores the results of a trading simulation.
*/
SimulationResult TradingBot::runSimulation()
{
    SimulationResult simres;

    Strategy* bestStrategy = nullptr;
    double bestCumulativeProfit = numeric_limits<double>::lowest();

    // Loop through all available strategies
    for (int i = 0; i < strategyCount; ++i) {
        Strategy* currentStrategy = availableStrategies[i];
        double cumulativeProfit = 0.0;
        double holdingStock = 0.0;
        double purchasePrice = 0.0;
        


        // Simulate for the last 101 days
        int startIndex = max(0, market->getNumTradingDays() - 101);
        for (int day = startIndex; day < market->getNumTradingDays(); ++day) {
            double currentPrice = market->getPrice(day);

            if (currentStrategy->decideAction(market, day, holdingStock) == BUY) {
                
                holdingStock = 1.0;
                purchasePrice = currentPrice;
            } else if (currentStrategy->decideAction(market, day, holdingStock) == SELL) {
                cumulativeProfit += currentPrice - purchasePrice;
                holdingStock = 0.0;
            }
            // If action is "HOLD", do nothing
        }

        // Handle the last day if still holding a stock
        if (holdingStock == 1.0) {
            cumulativeProfit += market->getLastPrice() - purchasePrice;
        }

        // Update the best strategy if this one is better
        if (cumulativeProfit > bestCumulativeProfit) {
            bestCumulativeProfit = cumulativeProfit;
            bestStrategy = currentStrategy;
        }
    }

    // Return the result with the best strategy and its total profit
    simres.bestStrategy = bestStrategy;
    simres.totalReturn = bestCumulativeProfit;
    return simres;
}
