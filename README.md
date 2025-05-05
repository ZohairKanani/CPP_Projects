# Combined Projects Repository

This repository contains two C++ projects that demonstrate different Object-Oriented Programming (OOP) concepts. Each project is organized as a separate module within the repository and illustrates unique real-world system simulations.

---

## Project 1: Trading Bot Simulation

### Introduction
In this assignment, we explore the concepts of inheritance and polymorphism to develop a flexible and extensible system that simulates stock prices and trading strategies. The primary objective is to implement a trading bot capable of interacting with a simulated market environment to maximize profits.

### Key Classes
- **Market**:  
  Simulates the stock market, including conditions like bullish and bearish trends, and varying levels of volatility.
  
- **TradingBot**:  
  A base class for a trading bot that interacts with or simulates a market. It integrates various trading strategies with unique parameters to identify the most effective approach for current market conditions.
  
- **Strategy**:  
  An abstract base class that analyzes 100 days of market data to decide whether to **BUY**, **SELL**, or **HOLD** a stock each day. Specific trading strategies inherit from this class.
  
- **Mean Reversion Strategy**:  
  Inherits from the **Strategy** class and buys stocks when the price falls below the mean minus a defined threshold, then sells when it exceeds the mean plus that threshold.
  
- **Trend Following Strategy**:  
  Inherits from the **Strategy** class and compares short-term and long-term moving averages—buying when the short-term average exceeds the long-term average and selling when it falls below.
  
- **Weighted Trend Following Strategy**:  
  Inherits from the **Trend Following Strategy** with an enhanced algorithm that assigns greater weight to more recent market data in its moving average calculations.

### Build and Run Instructions
1. **Build the project** (using your preferred build system):
    ```bash
    make all
    ```
2. **Run the simulation**:
    ```bash
    ./trading_bot
    ```

*For additional details or configuration options, please refer to the project-specific documentation in the Trading Bot directory.*

---

## Project 2: Library Management System

### Introduction
In this assignment, we combine the core concepts of Object-Oriented Programming (OOP) in C++ to develop a library management system. This system simulates real-world library operations by modeling key entities as classes and objects.

### Key Classes
- **Book**:  
  Represents a book in the library, encapsulating details such as book ID, title, and author.
  
- **BookList**:  
  Manages a collection of books using a linked list structure, facilitating dynamic book storage and retrieval.
  
- **User**:  
  Represents a library user with associated attributes like user ID and name.
  
- **Library**:  
  Coordinates overall library operations, including managing the book inventory (via **BookList**) and user registrations.

### Build and Run Instructions
1. **Compile the project** using your preferred C++ compiler:
    ```bash
    g++ -o library_management main.cpp Book.cpp BookList.cpp User.cpp Library.cpp
    ```
2. **Execute the program**:
    ```bash
    ./library_management
    ```

*Refer to the Library Management System directory for more detailed build instructions and documentation.*

---

## Contributing
Contributions to either project are welcome! Please fork this repository and submit a pull request with your improvements or bug fixes.

## License
[Specify your license information here, e.g., MIT License]
