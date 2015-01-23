#pragma once

#include <iostream>
#include <string>
#include <vector>

#include <lwsxx/websockethandler.hh>

#include <rapidjson/document.h>

namespace lwsxx { class WebSocketSession; }

namespace camshaft
{
  class JsonHandler : public lwsxx::WebSocketHandler
  {
  protected:
    void receiveMessage(lwsxx::WebSocketSession* session, std::vector<byte>& message) override;

    virtual void onDocument(lwsxx::WebSocketSession* session, const rapidjson::Document& doc) = 0;

    virtual void onJsonParseError(lwsxx::WebSocketSession* session, const rapidjson::Document& doc);
  };
}
