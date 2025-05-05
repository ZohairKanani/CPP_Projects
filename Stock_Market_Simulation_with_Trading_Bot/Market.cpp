#include "Market.h"
#include "Utils.h"

Market::Market(double initialPrice, double volatility, double expectedYearlyReturn, int numTradingDays, int seed):initialPrice(initialPrice), volatility(volatility), expectedYearlyReturn(expectedYearlyReturn), numTradingDays(numTradingDays),prices(new double*[numTradingDays]),seed(seed)
{
    for (int i = 0 ; i < numTradingDays; ++i)
    {
        prices[i] = new double(0.0);
    }
}

Market::Market(const string &filename)
{
    loadFromFile(filename);
}

Market::~Market()
{
    int i = 0;
    for (; i < numTradingDays; ++i)
    {
        delete prices[i];
    }
    delete[] prices;
}

// ===== Don't modify below this line =====
// Helper function to generate a random number from a normal distribution
double Market::generateZ(int seed)
{
    static std::mt19937 gen(seed == -1 ? std::random_device{}() : seed);
    static std::normal_distribution<> d(0, 1);
    return d(gen);
}
// ===== Don't modify above this line =====

//Complete the function to simulate price movements for numTradingDays based on a geometric Brownian motion model and stored simulated prices in prices. Please start with initialPrice and iteratively apply GBM formula to the previous prices. initialPrice should be the first element in the prices array. Remember to use roundToDecimals to round the prices up to 3 decimal places.


void Market::simulate() 
{
    *prices[0] = initialPrice;
    
    // Constants
    double dt = 1.0 / TRADING_DAYS_PER_YEAR;  // Time step in years

    // Simulate prices for each trading day
    for (int t = 1; t < numTradingDays; ++t) 
    {
        double Z = generateZ(seed);  // Generate a random number from standard normal distribution
        double prevPrice = *prices[t - 1];

        // GBM Formula: S_t = S_{t-1} * exp((drift - 0.5 * volatility^2) * dt + volatility * sqrt(dt) * Z)
        double nextPrice = prevPrice * exp((expectedYearlyReturn - 0.5 * volatility * volatility) * dt +
                                           volatility * sqrt(dt) * Z);

        // Round to 3 decimal places and store the price
        *prices[t] = roundToDecimals(nextPrice, 3);
    }
}

double Market::getVolatility() const
{
    return volatility;
}

double Market::getExpectedYearlyReturn() const
{
    return expectedYearlyReturn;
}

double **Market::getPrices() const
{
    return prices;
}

double Market::getPrice(int index) const
{
    for (int i = 0 ; i < numTradingDays ; ++i)
    {
        if (i == index)
        {
            return *prices[i];
        }
    }
    return 0.0;
}

double Market::getLastPrice() const
{
    return *prices[numTradingDays-1];
}

int Market::getNumTradingDays() const
{
    /*
    for (int i = 0 ; i < numTradingDays; ++i)
    {
        if (prices[i] == nullptr)
        {
            return i;
        }
    }
    */
   return numTradingDays;
}

// ===== Don't modify below this line =====
void Market::createDirectory(const string &folder)
{
#ifdef _WIN32
    _mkdir(folder.c_str());
#else
    mkdir(folder.c_str(), 0777);
#endif
}

void Market::writeToFile(const string &filename)
{
    string folder = "data";
    string filePath = folder + "/" + filename;

    createDirectory(folder);

    ofstream outFile(filePath);
    if (!outFile)
    {
        cerr << "Error opening file for writing: " << filePath << endl;
        return;
    }

    outFile << initialPrice << " " << volatility << " "
            << expectedYearlyReturn << " " << numTradingDays << " " << seed << endl;

    for (int i = 0; i < numTradingDays; ++i)
    {
        outFile << *prices[i] << endl;
    }

    outFile.close();
    cout << "Market parameters and prices written to file: " << filePath << endl;
}

void Market::loadFromFile(const string &filename)
{
    string filePath = "data/" + filename;
    ifstream inFile(filePath);
    if (!inFile)
    {
        cerr << "Error opening file for reading: " << filePath << endl;
        return;
    }

    inFile >> initialPrice >> volatility >> expectedYearlyReturn >> numTradingDays >> seed;

    // Clear existing prices
    if (prices)
    {
        for (int i = 0; i < numTradingDays; i++)
        {
            delete prices[i];
        }
        delete[] prices;
    }

    // Count number of prices first
    ifstream countFile(filePath);
    string line;
    int count = 0;
    double dummy;
    countFile >> dummy >> dummy >> dummy >> dummy >> dummy; // Skip parameters
    while (countFile >> dummy)
        count++;
    countFile.close();

    // Allocate new array
    prices = new double *[count];
    for (int i = 0; i < count; i++)
    {
        prices[i] = new double(0.0);
    }

    // Read prices
    int pricesSize = 0;
    double price;
    while (inFile >> price)
    {
        *prices[pricesSize++] = price;
    }

    inFile.close();
    cout << "Loaded parameters from file: " << filePath << endl;
    cout << "Initial Price: " << initialPrice << ", Volatility: " << volatility
         << ", Expected Yearly Return: " << expectedYearlyReturn
         << ", Num of Trading Days: " << numTradingDays << ", Seed: " << seed << endl;
    cout << "Loaded " << pricesSize << " price entries." << endl;
}
// ===== Don't modify above this line =====

// TODO: Implement the member functions of the Market class
