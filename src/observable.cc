#include "camshaft/observable.hh"

unsigned Observable::ctorCount = 0;
unsigned Observable::dtorCount = 0;
unsigned Observable::copyCount = 0;
unsigned Observable::moveCount = 0;
unsigned Observable::assignCount = 0;
