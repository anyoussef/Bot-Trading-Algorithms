#include "strategy.hpp"

double Strategy::movingAverage(const std::vector<Bar> &bars, int n) {
  double sum = 0.0;
  int i = bars.size() - n;
  for (; i < bars.size(); ++i) {
    sum += bars[i].close;
  }
  sum /= n;
  return sum;
}
