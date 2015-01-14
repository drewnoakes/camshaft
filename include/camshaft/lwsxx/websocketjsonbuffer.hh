#pragma once

#include <lwsxx/websocketbuffer.hh>

namespace camshaft
{
  namespace lwsxx
  {
    class WebSocketJsonBuffer : public ::lwsxx::WebSocketBuffer
    {
    public:
      inline void Put(byte b) { append(b); }

      void Flush() {};
    };
  }
}
