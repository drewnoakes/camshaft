#pragma once

#include <string>
#include <algorithm>

namespace camshaft
{
  inline std::string& trim_end(std::string& str)
  {
    if (!str.size())
      return str;

    // find the last whitespace chr, then delete from there to end.
    std::string::iterator iter = --str.end();
    while (isspace(*iter))
      --iter;
    str.erase(++iter, str.end());
    return str;
  }

  inline std::string& trim_front(std::string & str)
  {
    if (!str.size())
      return str;

    // find first non-whitespace, then delete from begin to there.
    std::string::iterator iter = str.begin();
    while (iter != str.end() && isspace(*iter))
      ++iter;
    str.erase(str.begin(), iter);
    return str;
  }

  inline std::string& trim(std::string& str)
  {
    return trim_end(trim_front(str));
  }

  inline std::string& remove_non_ascii(std::string& str)
  {
    str.erase(
      std::remove_if(
        str.begin(),
        str.end(),
        [](const char c) { return c < 0 || c > 127; }
      ),
      str.end());
    return str;
  }
}
