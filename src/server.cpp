#include "server.hpp"
#include "alpaca/client.hpp"
#include <crow.h>
#include <nlohmann/json.hpp>

void runServer(const char *ma_key, const char *ma_secret, const char *rsi_key,
               const char *rsi_secret) {
  crow::SimpleApp app;

  AlpacaClient maClient(ma_key, ma_secret);
  AlpacaClient rsiClient(rsi_key, rsi_secret);

  CROW_ROUTE(app, "/api/clock")([&]() {
    Clock clock = maClient.getClock();
    nlohmann::json res = {{"is_open", clock.is_open},
                          {"next_open", clock.next_open},
                          {"next_close", clock.next_close}};
    return res.dump();
  });

  CROW_ROUTE(app, "/api/ma/account")([&]() {
    Account account = maClient.getAccount();
    nlohmann::json res = {{"id", account.id},
                          {"account_number", account.account_number},
                          {"cash", account.cash},
                          {"portfolio_value", account.portfolio_value}};
    return res.dump();
  });

  CROW_ROUTE(app, "/api/ma/positions")([&]() {
    std::vector<Position> positions = maClient.getPositions();
    nlohmann::json res = nlohmann::json::array();
    for (auto &p : positions) {
      res.push_back({{"symbol", p.symbol},
                     {"shares", p.shares},
                     {"market_value", p.market_value},
                     {"unrealized_pl", p.unrealized_pl}});
    }
    return res.dump();
  });

  CROW_ROUTE(app, "/api/ma/orders")([&]() {
    std::vector<Orders> orders = maClient.getOrders();
    nlohmann::json res = nlohmann::json::array();
    for (auto &o : orders) {
      res.push_back(
          {{"symbol", o.symbol}, {"status", o.status}, {"side", o.side}});
    }
    return res.dump();
  });

  CROW_ROUTE(app, "/api/rsi/account")([&]() {
    Account account = rsiClient.getAccount();
    nlohmann::json res = {{"id", account.id},
                          {"account_number", account.account_number},
                          {"cash", account.cash},
                          {"portfolio_value", account.portfolio_value}};
    return res.dump();
  });

  CROW_ROUTE(app, "/api/rsi/positions")([&]() {
    std::vector<Position> positions = rsiClient.getPositions();
    nlohmann::json res = nlohmann::json::array();
    for (auto &p : positions) {
      res.push_back({{"symbol", p.symbol},
                     {"shares", p.shares},
                     {"market_value", p.market_value},
                     {"unrealized_pl", p.unrealized_pl}});
    }
    return res.dump();
  });

  CROW_ROUTE(app, "/api/rsi/orders")([&]() {
    std::vector<Orders> orders = rsiClient.getOrders();
    nlohmann::json res = nlohmann::json::array();
    for (auto &o : orders) {
      res.push_back(
          {{"symbol", o.symbol}, {"status", o.status}, {"side", o.side}});
    }
    return res.dump();
  });

  app.port(8080).multithreaded().run();
}
