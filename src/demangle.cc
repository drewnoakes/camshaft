#include "camshaft/demangle.hh"

#ifdef __GNUG__

#include <memory>
#include <cxxabi.h>

std::string demangle(const char* name)
{
  int status = -4; // some arbitrary value to eliminate the compiler warning

  std::unique_ptr<char, void(*)(void*)> res {
    abi::__cxa_demangle(name, NULL, NULL, &status),
    std::free
  };

  return status == 0 ? res.get() : name;
}

#else

std::string demangle(const char* name)
{
  // return the string unchanged if not gcc
  return name;
}

#endif

std::string demangle(const std::type_info& typeInfo)
{
  return demangle(typeInfo.name());
}
