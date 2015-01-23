#pragma once

#include <map>

std::multimap<std::string,std::string> parseQueryString(std::string queryString, bool splitCsv = false);
