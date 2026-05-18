#include "client.hpp"
#include <curl/curl.h>
#include <iostream>
#include <nlohmann/json.hpp>

// Curl callback
size_t WriteCallback(void *contents, size_t size, size_t nmemb,
                     std::string *output) {
  output->append((char *)contents, size * nmemb);
  return size * nmemb;
}

// Constructor
AlpacaClient::AlpacaClient(const std::string &key, const std::string &secret) {
  this->apiKey = key;
  this->apiSecret = secret;
  baseUrl = "https://paper-api.alpaca.markets";
}

// Private HTTP methods
std::string AlpacaClient::get(const std::string &endpoint,
                              const std::string &base) {
  CURL *curl = curl_easy_init();
  std::string response;
  if (curl) {
    curl_easy_setopt(curl, CURLOPT_URL, (base + endpoint).c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
    struct curl_slist *headers = nullptr;
    headers =
        curl_slist_append(headers, ("APCA-API-KEY-ID: " + apiKey).c_str());
    headers = curl_slist_append(headers,
                                ("APCA-API-SECRET-KEY: " + apiSecret).c_str());
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_perform(curl);
    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);
  } else {
    response += "FAILURE";
    return response;
  }
  return response;
}

std::string AlpacaClient::post(const std::string &endpoint,
                               const std::string &body) {
  CURL *curl = curl_easy_init();
  std::string response;
  if (curl) {
    curl_easy_setopt(curl, CURLOPT_URL, (baseUrl + endpoint).c_str());
    curl_easy_setopt(curl, CURLOPT_POST, 1L);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
    struct curl_slist *headers = nullptr;
    headers =
        curl_slist_append(headers, ("APCA-API-KEY-ID: " + apiKey).c_str());
    headers = curl_slist_append(headers,
                                ("APCA-API-SECRET-KEY: " + apiSecret).c_str());
    headers = curl_slist_append(headers, "Content-Type: application/json");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_perform(curl);
    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);
  }
  return response;
}

// Public API methods
Account AlpacaClient::getAccount() {
  std::string response = get("/v2/account", baseUrl);
  Account returned_account;
  try {
    auto json = nlohmann::json::parse(response);
    returned_account.id = json["id"];
    returned_account.account_number = json["account_number"];
    returned_account.cash = json["cash"];
    returned_account.portfolio_value = json["portfolio_value"];
  } catch (const std::exception &e) {
    std::cerr << "Account parse error: " << e.what() << std::endl;
    std::cerr << "Response: " << response << std::endl;
  }
  return returned_account;
}

std::vector<Position> AlpacaClient::getPositions() {
  std::string response = get("/v2/positions", baseUrl);
  std::vector<Position> position_list;
  auto json = nlohmann::json::parse(response);
  for (auto &item : json) {
    try {
      Position position;
      position.symbol = item["symbol"];
      position.shares = item["qty"];
      position.market_value = item["market_value"];
      position.unrealized_pl = item["unrealized_pl"];
      position_list.push_back(position);
    } catch (const std::exception &e) {
      std::cerr << "Position parse error: " << e.what() << std::endl;
      std::cerr << "Item: " << item.dump(2) << std::endl;
    }
  }
  return position_list;
}

std::vector<Orders> AlpacaClient::getOrders() {
  std::string response = get("/v2/orders", baseUrl);
  std::vector<Orders> order_list;
  auto json = nlohmann::json::parse(response);
  for (auto &item : json) {
    try {
      Orders order;
      order.symbol = item["symbol"];
      order.status = item["status"];
      order.side = item["side"];
      order_list.push_back(order);
    } catch (const std::exception &e) {
      std::cerr << "Order parse error: " << e.what() << std::endl;
      std::cerr << "Item: " << item.dump(2) << std::endl;
    }
  }
  return order_list;
}

std::vector<Bar> AlpacaClient::getMarketData(const std::string &symbol) {
  std::string endpoint =
      "/v2/stocks/" + symbol +
      "/bars?timeframe=1Day&limit=200&feed=iex&start=2025-01-01";
  std::string dataUrl = "https://data.alpaca.markets";
  std::string response = get(endpoint, dataUrl);
  std::vector<Bar> this_bar;
  try {
    auto json = nlohmann::json::parse(response);
    for (auto &item : json["bars"]) {
      Bar bar;
      bar.timestamp = item["t"];
      bar.open = item["o"];
      bar.high = item["h"];
      bar.low = item["l"];
      bar.close = item["c"];
      bar.volume = item["v"];
      this_bar.push_back(bar);
    }
  } catch (const std::exception &e) {
    std::cerr << "Market data parse error: " << e.what() << std::endl;
    std::cerr << "Response: " << response << std::endl;
  }
  return this_bar;
}

std::string AlpacaClient::placeOrder(const std::string &symbol, int qty,
                                     const std::string &side) {
  nlohmann::json body = {{"symbol", symbol},
                         {"qty", qty},
                         {"side", side},
                         {"type", "market"},
                         {"time_in_force", "day"}};
  std::string bodyStr = body.dump();
  std::string endpoint = "/v2/orders";
  return post(endpoint, bodyStr);
}
