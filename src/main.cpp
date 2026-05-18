#include "strategy/ma.hpp"
#include "strategy/rsi.hpp"
#include <chrono>
#include <cstdlib>
#include <curl/curl.h>
#include <iostream>
#include <thread>

int main() {

  curl_global_init(CURL_GLOBAL_ALL); // add this as the very first line

  const char *ma_key = std::getenv("ALPACA_MA_KEY");
  const char *ma_secret = std::getenv("ALPACA_MA_SECRET");
  const char *rsi_key = std::getenv("ALPACA_RSI_KEY");
  const char *rsi_secret = std::getenv("ALPACA_RSI_SECRET");

  if (ma_key == nullptr || ma_secret == nullptr) {
    std::cerr << "No Environment Vars set" << std::endl;
    exit(1);
  }
  if (rsi_key == nullptr || rsi_secret == nullptr) {
    std::cerr << "No Environment Vars set" << std::endl;
    exit(1);
  }

  while (true) {
    std::thread maThread(runMAStrategy, "AAPL", ma_key, ma_secret);
    std::thread rsiThread(runRSIStrategy, "AAPL", rsi_key, rsi_secret);

    maThread.join();
    rsiThread.join();

    std::cout << "Sleeping for 24 hours..." << std::endl;
    std::this_thread::sleep_for(std::chrono::hours(24));
  }

  curl_global_cleanup(); // add before return 0
  return 0;
}
