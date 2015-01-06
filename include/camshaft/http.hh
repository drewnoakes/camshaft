#pragma once

#include <string>
#include <vector>

std::vector<char> download(std::string url, long* responseCode = nullptr);
