#include "alpaca/client.hpp"
#include "server.hpp"
#include "strategy/ma.hpp"
#include "strategy/rsi.hpp"
#include <chrono>
#include <cstdlib>
#include <curl/curl.h>
#include <iostream>
#include <thread>

int main() {
  curl_global_init(CURL_GLOBAL_ALL);

  const char *ma_key = std::getenv("ALPACA_MA_KEY");
  const char *ma_secret = std::getenv("ALPACA_MA_SECRET");
  const char *rsi_key = std::getenv("ALPACA_RSI_KEY");
  const char *rsi_secret = std::getenv("ALPACA_RSI_SECRET");

  if (ma_key == nullptr || ma_secret == nullptr) {
    std::cerr << "MA environment vars not set" << std::endl;
    exit(1);
  }
  if (rsi_key == nullptr || rsi_secret == nullptr) {
    std::cerr << "RSI environment vars not set" << std::endl;
    exit(1);
  }

  // start server once
  std::thread serverThread(runServer, ma_key, ma_secret, rsi_key, rsi_secret);

  while (true) {
    AlpacaClient clockClient(ma_key, ma_secret);
    Clock clock = clockClient.getClock();

    if (clock.is_open) {
      std::cout << "Market is open, running strategies..." << std::endl;
      std::thread maThread(runMAStrategy, "AAPL", ma_key, ma_secret);
      std::thread rsiThread(runRSIStrategy, "AAPL", rsi_key, rsi_secret);
      maThread.join();
      rsiThread.join();
      std::cout << "Strategies complete, sleeping 1 hour..." << std::endl;
      std::this_thread::sleep_for(std::chrono::hours(1));
    } else {
      std::cout << "Market is closed. Next open: " << clock.next_open
                << std::endl;
      std::cout << "Sleeping 1 hour..." << std::endl;
      std::this_thread::sleep_for(std::chrono::hours(1));
    }
  }

  serverThread.join();
  curl_global_cleanup();
  return 0;
}
