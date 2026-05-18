#include "server.hpp"
#include "alpaca/client.hpp"
#include <crow.h>
#include <nlohmann/json.hpp>

void runServer(const char *ma_key, const char *ma_secret, const char *rsi_key,
               const char *rsi_secret) {
  crow::SimpleApp app;

  AlpacaClient maClient(ma_key, ma_secret);
  AlpacaClient rsiClient(rsi_key, rsi_secret);

  auto addCORS = [](crow::response &res) {
    res.add_header("Access-Control-Allow-Origin", "*");
    res.add_header("Access-Control-Allow-Methods", "GET, OPTIONS");
    res.add_header("Access-Control-Allow-Headers", "Content-Type");
  };

  CROW_ROUTE(app, "/api/clock")([&]() {
    Clock clock = maClient.getClock();
    nlohmann::json data = {{"is_open", clock.is_open},
                           {"next_open", clock.next_open},
                           {"next_close", clock.next_close}};
    crow::response res(data.dump());
    addCORS(res);
    return res;
  });

  CROW_ROUTE(app, "/api/ma/account")([&]() {
    Account account = maClient.getAccount();
    nlohmann::json data = {{"id", account.id},
                           {"account_number", account.account_number},
                           {"cash", account.cash},
                           {"portfolio_value", account.portfolio_value}};
    crow::response res(data.dump());
    addCORS(res);
    return res;
  });

  CROW_ROUTE(app, "/api/ma/positions")([&]() {
    std::vector<Position> positions = maClient.getPositions();
    nlohmann::json data = nlohmann::json::array();
    for (auto &p : positions) {
      data.push_back({{"symbol", p.symbol},
                      {"shares", p.shares},
                      {"market_value", p.market_value},
                      {"unrealized_pl", p.unrealized_pl}});
    }
    crow::response res(data.dump());
    addCORS(res);
    return res;
  });

  CROW_ROUTE(app, "/api/ma/orders")([&]() {
    std::vector<Orders> orders = maClient.getOrders();
    nlohmann::json data = nlohmann::json::array();
    for (auto &o : orders) {
      data.push_back(
          {{"symbol", o.symbol}, {"status", o.status}, {"side", o.side}});
    }
    crow::response res(data.dump());
    addCORS(res);
    return res;
  });

  CROW_ROUTE(app, "/api/rsi/account")([&]() {
    Account account = rsiClient.getAccount();
    nlohmann::json data = {{"id", account.id},
                           {"account_number", account.account_number},
                           {"cash", account.cash},
                           {"portfolio_value", account.portfolio_value}};
    crow::response res(data.dump());
    addCORS(res);
    return res;
  });

  CROW_ROUTE(app, "/api/rsi/positions")([&]() {
    std::vector<Position> positions = rsiClient.getPositions();
    nlohmann::json data = nlohmann::json::array();
    for (auto &p : positions) {
      data.push_back({{"symbol", p.symbol},
                      {"shares", p.shares},
                      {"market_value", p.market_value},
                      {"unrealized_pl", p.unrealized_pl}});
    }
    crow::response res(data.dump());
    addCORS(res);
    return res;
  });

  CROW_ROUTE(app, "/api/rsi/orders")([&]() {
    std::vector<Orders> orders = rsiClient.getOrders();
    nlohmann::json data = nlohmann::json::array();
    for (auto &o : orders) {
      data.push_back(
          {{"symbol", o.symbol}, {"status", o.status}, {"side", o.side}});
    }
    crow::response res(data.dump());
    addCORS(res);
    return res;
  });

  app.port(8080).multithreaded().run();
}
