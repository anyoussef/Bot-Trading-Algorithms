#include "alpaca/client.hpp"
#include "strategy/strategy.hpp"
#include <cstdlib>
#include <iostream>
#include <vector>

int main() {
  const char *ma_key = std::getenv("ALPACA_MA_KEY");
  const char *ma_secret = std::getenv("ALPACA_MA_SECRET");

  if (ma_key == nullptr || ma_secret == nullptr) {
    std::cerr << "No Environment Vars set" << std::endl;
    exit(1);
  }

  AlpacaClient client(ma_key, ma_secret);

  Account account = client.getAccount();
  std::cout << "Account: " << account.account_number << std::endl;
  std::cout << "Cash: " << account.cash << std::endl;
  std::cout << "Portfolio Value: " << account.portfolio_value << std::endl;

  std::vector<Bar> bars = client.getMarketData("AAPL");
  std::vector<Position> positions = client.getPositions();
  std::vector<Orders> orders = client.getOrders();

  double fast = Strategy::movingAverage(bars, 50);
  double slow = Strategy::movingAverage(bars, 200);

  std::cout << "50 day MA:  " << fast << std::endl;
  std::cout << "200 day MA: " << slow << std::endl;

  if (fast > slow) {
    if (Strategy::hasPosition(positions, "AAPL") ||
        Strategy::hasOrder(orders, "AAPL")) {
      std::cout << "Already own AAPL, holding" << std::endl;
    } else {
      std::cout << "Signal: BUY - Placing buy order" << std::endl;
      std::string result = client.placeOrder("AAPL", 1, "buy");
      std::cout << "Order response: " << result << std::endl;
    }
  } else {
    if (Strategy::hasPosition(positions, "AAPL") ||
        Strategy::hasOrder(orders, "AAPL")) {
      std::cout << "Signal: SELL - Placing sell order" << std::endl;
      std::string result = client.placeOrder("AAPL", 1, "sell");
      std::cout << "Order response: " << result << std::endl;
    } else {
      std::cout << "Nothing to sell" << std::endl;
    }
  }

  return 0;
}
