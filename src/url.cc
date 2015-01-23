#include "camshaft/url.hh"

#include <cassert>
#include <iostream>
#include <regex>

using namespace std;

multimap<string, string> parseQueryString(string queryString)
{
  static const regex reg("([^?=&]+)(=([^&]*))?");

  multimap<string, string> map;

  auto matchesBegin = sregex_iterator(queryString.begin(), queryString.end(), reg);
  auto matchesEnd = sregex_iterator();

  for (auto it = matchesBegin; it != matchesEnd; it++)
  {
    assert(it->size() == 4);
    auto const& match = *it;
    map.insert(make_pair(match[1], match[3]));
  }

  return map;
}
