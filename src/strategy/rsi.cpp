#include "rsi.hpp"
#include "../alpaca/client.hpp"
#include "strategy.hpp"
#include <iostream>
#include <vector>

void runRSIStrategy(const std::string &symbol, const char *key,
                    const char *secret) {
  AlpacaClient client(key, secret);

  Account account = client.getAccount();
  std::cout << "Account: " << account.account_number << std::endl;
  std::cout << "Cash: " << account.cash << std::endl;
  std::cout << "Portfolio Value: " << account.portfolio_value << std::endl;

  std::vector<Bar> bars = client.getMarketData(symbol);
  std::vector<Position> positions = client.getPositions();
  std::vector<Orders> orders = client.getOrders();

  double rsi = Strategy::calculateRSI(bars);
  std::cout << "RSI: " << rsi << std::endl;

  if (rsi < 30) {
    if (Strategy::hasPosition(positions, symbol) ||
        Strategy::hasOrder(orders, symbol)) {
      std::cout << "Already own " << symbol << ", holding" << std::endl;
    } else {
      std::cout << "Signal: BUY - RSI oversold" << std::endl;
      std::string result = client.placeOrder(symbol, 1, "buy");
      std::cout << "Order response: " << result << std::endl;
    }
  } else if (rsi > 70) {
    if (Strategy::hasPosition(positions, symbol) ||
        Strategy::hasOrder(orders, symbol)) {
      std::cout << "Signal: SELL - RSI overbought" << std::endl;
      std::string result = client.placeOrder(symbol, 1, "sell");
      std::cout << "Order response: " << result << std::endl;
    } else {
      std::cout << "Nothing to sell" << std::endl;
    }
  } else {
    std::cout << "RSI neutral (" << rsi << "), no action" << std::endl;
  }
}
