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

  inline void tokenize(const std::string& str, std::vector<std::string>& tokens, const std::string& delimiters = ",")
  {
    // From http://stackoverflow.com/a/12503736/24874

    // Skip delimiters at beginning.
    std::string::size_type lastPos = str.find_first_not_of(delimiters, 0);

    // Find first non-delimiter.
    std::string::size_type pos = str.find_first_of(delimiters, lastPos);

    while (std::string::npos != pos || std::string::npos != lastPos)
    {
      // Found a token, add it to the vector.
      tokens.push_back(str.substr(lastPos, pos - lastPos));

      // Skip delimiters.
      lastPos = str.find_first_not_of(delimiters, pos);

      // Find next non-delimiter.
      pos = str.find_first_of(delimiters, lastPos);
    }
  }
}
