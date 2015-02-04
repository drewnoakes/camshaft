#pragma once

#include <string>

class Stopwatch
{
  typedef unsigned long long mark;

public:
  Stopwatch()
  : _mark(makeMark())
  {}

  void reset() { _mark = makeMark(); }

  double seconds() const { return (makeMark() - _mark) / 1e6; }
  double millis() const { return (makeMark() - _mark) / 1e3; }
  double micros() const { return makeMark() - _mark; }

  inline std::string describe() const { return describeSeconds(seconds()); }

  static std::string describeSeconds(double seconds);

private:
  mark _mark;
  static mark makeMark();
};
