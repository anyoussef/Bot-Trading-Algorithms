#include "strategy/ma.hpp"
#include <chrono>
#include <cstdlib>
#include <iostream>
#include <thread>

int main() {
  const char *ma_key = std::getenv("ALPACA_MA_KEY");
  const char *ma_secret = std::getenv("ALPACA_MA_SECRET");

  if (ma_key == nullptr || ma_secret == nullptr) {
    std::cerr << "No Environment Vars set" << std::endl;
    exit(1);
  }

  while (true) {
    runMAStrategy("AAPL", ma_key, ma_secret);
    std::cout << "Sleeping for 24 hours..." << std::endl;
    std::this_thread::sleep_for(std::chrono::hours(24));
  }

  return 0;
}
