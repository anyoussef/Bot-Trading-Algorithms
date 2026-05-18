#pragma once
#include "../alpaca/bar.hpp"
#include "../alpaca/order.hpp"
#include "../alpaca/positions.hpp"
#include <vector>

namespace Strategy {
double movingAverage(const std::vector<Bar> &bars, int n);
double calculateRSI(const std::vector<Bar> &bars);

bool hasPosition(const std::vector<Position> &positions,
                 const std::string &symbol);
bool hasOrder(const std::vector<Orders> &orders, const std::string &symbol);
} // namespace Strategy
