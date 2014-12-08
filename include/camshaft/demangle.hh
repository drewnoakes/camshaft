#pragma once

#include <string>
#include <typeinfo>

std::string demangle(const char* name);

std::string demangle(const std::type_info& typeInfo);

template <class T>
std::string type(const T& t)
{
  return demangle(typeid(t).name());
}
