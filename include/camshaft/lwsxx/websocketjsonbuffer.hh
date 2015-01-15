#pragma once

#include <lwsxx/websocketbuffer.hh>

typedef unsigned char byte;

namespace camshaft
{
  class WebSocketJsonBuffer : public lwsxx::WebSocketBuffer
  {
  public:
    inline void Put(byte b) { append(b); }

    void Flush() {};
  };
}
