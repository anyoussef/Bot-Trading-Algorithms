#pragma once
#include <string>

struct Clock {
  bool is_open;
  std::string next_open;
  std::string next_close;
};
