#include "alpaca/client.hpp"
#include <cstdlib>
#include <iostream>
#include <nlohmann/json.hpp>
#include <vector>

int main() {
  const char *ma_key = std::getenv("ALPACA_MA_KEY");
  const char *ma_secret = std::getenv("ALPACA_MA_SECRET");
  if (ma_key == nullptr || ma_secret == nullptr) {
    std::cerr << "No Environment Vars set" << std::endl;
    exit(1);
  }
  AlpacaClient testClient = AlpacaClient(ma_key, ma_secret);

  // debug - see raw response
  std::cerr << "Fetching market data..." << std::endl;

  std::vector<Bar> bars = testClient.getMarketData("AAPL");
  std::cout << "Last close: " << bars.back().close << std::endl;
  std::cout << "Last timestamp: " << bars.back().timestamp << std::endl;

  Account test_account = testClient.getAccount();
  std::cout << test_account.id << std::endl;
  std::cout << test_account.account_number << std::endl;
  std::cout << test_account.cash << std::endl;
  std::cout << test_account.portfolio_value << std::endl;
  return 0;
}
