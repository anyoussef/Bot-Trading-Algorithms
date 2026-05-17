#pragma once
#include "account.hpp"
#include "bar.hpp"
#include "positions.hpp"
#include <string>
#include <vector>

class AlpacaClient {
public:
  AlpacaClient(const std::string &key, const std::string &secret);

  Account getAccount();
  std::vector<Position> getPositions();
  bool hasPosition(const std::vector<Position> &positions,
                   const std::string &symbol);
  std::vector<Bar> getMarketData(const std::string &symbol);
  std::string placeOrder(const std::string &symbol, int qty,
                         const std::string &side);

private:
  std::string apiKey;
  std::string apiSecret;
  std::string baseUrl;

  std::string get(const std::string &endpoint, const std::string &base);
  std::string post(const std::string &endpoint, const std::string &body);
};
