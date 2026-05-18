#include "ma.hpp"
#include "../alpaca/client.hpp"
#include "strategy.hpp"
#include <iostream>
#include <vector>

void runMAStrategy(const std::string &symbol, const char *key,
                   const char *secret) {
  AlpacaClient client(key, secret);

  Account account = client.getAccount();
  std::cout << "Account: " << account.account_number << std::endl;
  std::cout << "Cash: " << account.cash << std::endl;
  std::cout << "Portfolio Value: " << account.portfolio_value << std::endl;

  std::vector<Bar> bars = client.getMarketData(symbol);
  std::vector<Position> positions = client.getPositions();
  std::vector<Orders> orders = client.getOrders();

  double fast = Strategy::movingAverage(bars, 50);
  double slow = Strategy::movingAverage(bars, 200);

  std::cout << "50 day MA:  " << fast << std::endl;
  std::cout << "200 day MA: " << slow << std::endl;

  if (fast > slow) {
    if (Strategy::hasPosition(positions, symbol) ||
        Strategy::hasOrder(orders, symbol)) {
      std::cout << "Already own " << symbol << ", holding" << std::endl;
    } else {
      std::cout << "Signal: BUY - Placing buy order" << std::endl;
      std::string result = client.placeOrder(symbol, 1, "buy");
      std::cout << "Order response: " << result << std::endl;
    }
  } else {
    if (Strategy::hasPosition(positions, symbol) ||
        Strategy::hasOrder(orders, symbol)) {
      std::cout << "Signal: SELL - Placing sell order" << std::endl;
      std::string result = client.placeOrder(symbol, 1, "sell");
      std::cout << "Order response: " << result << std::endl;
    } else {
      std::cout << "Nothing to sell" << std::endl;
    }
  }
}
