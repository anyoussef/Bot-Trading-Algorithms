#pragma once
#include "../alpaca/bar.hpp"
#include <vector>

namespace Strategy {
double movingAverage(const std::vector<Bar> &bars, int n);
}
