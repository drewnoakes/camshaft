#include "camshaft/stopwatch.hh"

#include <sys/time.h>
#include <sstream>
#include <cmath>

using namespace std;

std::string Stopwatch::describeSeconds(double seconds)
{
  seconds = fabs(seconds);

  int minutes = (int)(seconds / 60);
  int hours = (int)(seconds / (60 * 60));
  int days = (int)(seconds / (60 * 60 * 24));

  std::stringstream out;

  if (days > 2)
    out << days << " day" << (days == 1 ? "" : "s");
  else if (minutes > 90)
    out << hours << " hour" << (hours == 1 ? "" : "s");
  else if (seconds > 90)
    out << minutes << " minute" << (minutes == 1 ? "" : "s");
  else
    out << seconds << " second" << (seconds == 1 ? "" : "s");

  return out.str();
}

Stopwatch::mark Stopwatch::makeMark()
{
  struct timeval now;
  gettimeofday(&now, 0);
  return (mark)now.tv_usec + ((mark)now.tv_sec * (mark)1000000);
}
