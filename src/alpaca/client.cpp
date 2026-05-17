#include "client.hpp"
#include <cstddef>
#include <curl/curl.h>
#include <nlohmann/json.hpp>

size_t WriteCallback(void *contents, size_t size, size_t nmemb,
                     std::string *output) {

  output->append((char *)contents, size * nmemb);
  return size * nmemb;
}

AlpacaClient::AlpacaClient(const std::string &key, const std::string &secret) {
  this->apiKey = key;
  this->apiSecret = secret;
  baseUrl = "https://paper-api.alpaca.markets";
}

Account AlpacaClient::getAccount() {

  std::string response = get("/v2/account");
  Account returned_account;

  auto json = nlohmann::json::parse(response);
  returned_account.id = json["id"];
  returned_account.account_number = json["account_number"];
  returned_account.cash = json["cash"];
  returned_account.portfolio_value = json["portfolio_value"];

  return returned_account;
}

std::string AlpacaClient::get(const std::string &endpoint) {

  CURL *curl = curl_easy_init();
  std::string response;

  if (curl) {
    CURLcode result;

    curl_easy_setopt(curl, CURLOPT_URL, (baseUrl + endpoint).c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    struct curl_slist *headers = nullptr;
    headers =
        curl_slist_append(headers, ("APCA-API-KEY-ID: " + apiKey).c_str());
    headers = curl_slist_append(headers,
                                ("APCA-API-SECRET-KEY: " + apiSecret).c_str());
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

    result = curl_easy_perform(curl);

    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);

  } else {
    curl_easy_cleanup(curl);
    response += "FAILURE";
    return response;
  }

  return response;
}
