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

bool Strategy::hasPosition(const std::vector<Position> &positions,
                           const std::string &symbol) {

  for (int i = 0; i < positions.size(); ++i) {
    if (positions[i].symbol == symbol)
      return true;
  }

  return false;
}

bool Strategy::hasOrder(const std::vector<Orders> &orders,
                        const std::string &symbol) {

  for (int i = 0; i < orders.size(); ++i) {
    if (orders[i].symbol == symbol)
      return true;
  }

  return false;
}
