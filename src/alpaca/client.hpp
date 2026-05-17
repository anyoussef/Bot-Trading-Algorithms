#pragma once
#include <string>

class AlpacaClient {
public:
  AlpacaClient(const std::string &key, const std::string &secret);

  std::string getAccount();
  std::string getPositions();
  std::string placeOrder(const std::string &symbol, int qty,
                         const std::string &side);

private:
  std::string apiKey;
  std::string apiSecret;
  std::string baseUrl;

  std::string get(const std::string &endpoint);
  std::string post(const std::string &endpoint, const std::string &body);
};
