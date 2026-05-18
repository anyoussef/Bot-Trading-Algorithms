#include "strategy.hpp"
#include <cmath>

double Strategy::movingAverage(const std::vector<Bar> &bars, int n) {
  double sum = 0.0;
  int i = bars.size() - n;
  for (; i < bars.size(); ++i) {
    sum += bars[i].close;
  }
  sum /= n;
  return sum;
}

double Strategy::calculateRSI(const std::vector<Bar> &bars) {
  double avg_gain = 0.0;
  double avg_loss = 0.0;
  int num_positive = 0;
  int num_negative = 0;

  int i = bars.size() - 14;
  for (; i < bars.size(); ++i) {
    double change = bars[i].close - bars[i - 1].close;
    if (change <= 0) {
      num_negative++;
      avg_loss += std::abs(change);
    } else {
      num_positive++;
      avg_gain += change;
    }
  }

  if (num_positive > 0)
    avg_gain /= num_positive;
  if (num_negative > 0)
    avg_loss /= num_negative;

  if (avg_loss == 0)
    return 100.0;

  double RS = avg_gain / avg_loss;
  double RSI = 100.0 - (100.0 / (1.0 + RS));
  return RSI;
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
