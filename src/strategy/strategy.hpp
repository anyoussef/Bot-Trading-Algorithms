#pragma once
#include "../alpaca/bar.hpp"
#include "../alpaca/positions.hpp"
#include <vector>

namespace Strategy {
double movingAverage(const std::vector<Bar> &bars, int n);
bool hasPosition(const std::vector<Position> &positions,
                 const std::string &symbol);
} // namespace Strategy
