#include "camshaft/log.hh"

#include "camshaft/ccolor.hh"

#include <unistd.h>

using namespace std;

LogLevel log::minLevel = LogLevel::Verbose;
LogRedirects log::redirects;

void writeLogTimestamp(ostream& o)
{
  time_t now = time(0);
  tm tstruct = *localtime(&now);
  char buf[80];
  // http://en.cppreference.com/w/cpp/chrono/c/strftime
  strftime(buf, sizeof(buf), "%X", &tstruct);
  o << buf << " ";
}

void writeLevelShortName(ostream& o, LogLevel level)
{
  switch (level)
  {
    case LogLevel::Trace:   o << "trc "; break;
    case LogLevel::Verbose: o << "vrb "; break;
    case LogLevel::Info:    o << "inf "; break;
    case LogLevel::Warning: o << "WRN "; break;
    case LogLevel::Error:   o << "ERR "; break;
    default:                o << "??? "; break;
  }
}

log::~log()
{
  if (!d_message)
    return;

  int fgColor = 39;
  int bgColor = 49;

  switch (d_level)
  {
    case LogLevel::Trace:
    case LogLevel::Verbose:
      fgColor = 37;
      break;
    case LogLevel::Info:
      break;
    case LogLevel::Warning:
      fgColor = 95;
      break;
    case LogLevel::Error:
      fgColor = 37;
      bgColor = 41;
      break;
  }

  auto& ostream = d_level == LogLevel::Error ? cerr : cout;
  bool isRedirected = d_level == LogLevel::Error ? redirects.isStdErrRedirected : redirects.isStdOutRedirected;

  if (isRedirected)
  {
    writeLogTimestamp(ostream);
    writeLevelShortName(ostream, d_level);

    if (d_scope.size())
      ostream << "[" << d_scope << "] ";

    ostream << d_message->str() << endl;
  }
  else
  {
    if (d_scope.size())
      ostream << ccolor::fore::lightblue << "[" << d_scope << "] ";

    ostream << "\033[" << fgColor << ";" << bgColor << "m"
      << d_message->str()
      << "\033[00m" << endl;
  }
}

LogRedirects::LogRedirects()
{
  isStdOutRedirected = isatty(STDOUT_FILENO) == 0;
  isStdErrRedirected = isatty(STDERR_FILENO) == 0;
}
