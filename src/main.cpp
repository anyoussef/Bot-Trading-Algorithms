#include "alpaca/client.hpp"
#include <cstdlib>
#include <iostream>

int main() {
  const char *ma_key = std::getenv("ALPACA_MA_KEY");
  const char *ma_secret = std::getenv("ALPACA_MA_SECRET");

  AlpacaClient testClient = AlpacaClient(ma_key, ma_secret);

  std::string response = testClient.getAccount();
  std::cout << response << std::endl;

  return 1;
}
