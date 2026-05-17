#pragma once
#include <string>

struct Position {
  std::string symbol;
  double shares;
  double market_value;
  double unrealized_pl;
};
