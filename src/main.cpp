#include "alpaca/client.hpp"
#include <cstdlib>
#include <iostream>
#include <nlohmann/json.hpp>

int main() {
  const char *ma_key = std::getenv("ALPACA_MA_KEY");
  const char *ma_secret = std::getenv("ALPACA_MA_SECRET");

  if (ma_key == NULL || ma_secret == NULL) {
    std::cout << "No Environment Vars set" << std::endl;
    exit(1);
  }

  AlpacaClient testClient = AlpacaClient(ma_key, ma_secret);

  Account test_account = testClient.getAccount();

  std::cout << test_account.id << std::endl;
  std::cout << test_account.account_number << std::endl;
  std::cout << test_account.cash << std::endl;
  std::cout << test_account.portfolio_value << std::endl;

  return 0;
}
