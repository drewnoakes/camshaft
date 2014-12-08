#pragma once

class Observable
{
public:
  Observable()
  {
    ctorCount++;
  }

  ~Observable()
  {
    dtorCount++;
  }

  Observable(const Observable& other)
  {
    (void)other;
    copyCount++;
  }

  Observable(Observable&& other)
  {
    (void)other;
    moveCount++;
  }

  Observable& operator=(const Observable&)
  {
    assignCount++;
    return *this;
  }

  static void reset()
  {
    ctorCount = 0;
    dtorCount = 0;
    copyCount = 0;
    moveCount = 0;
    assignCount = 0;
  }

  static unsigned ctorCount;
  static unsigned dtorCount;
  static unsigned copyCount;
  static unsigned moveCount;
  static unsigned assignCount;
};
