#pragma once

#if __cplusplus == 201103L
#include <memory>

// Stub for std::make_unique which will be added in c++14
namespace std
{
  template<typename T, typename... Args>
  std::unique_ptr<T> make_unique(Args&&... args)
  {
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
  }
}
#endif
