#pragma once

#include <iostream>
#include <string>
#include <vector>

#include <rapidjson/document.h>
#include <rapidjson/error/en.h>

#include <lwsxx/websockethandler.hh>
#include <lwsxx/websocketsession.hh>

namespace camshaft
{
  class JsonHandler : public lwsxx::WebSocketHandler
  {
  protected:
    void receiveMessage(lwsxx::WebSocketSession* session, std::vector<byte>& message) override
    {
      message.push_back('\0');

      rapidjson::Document doc;
      doc.ParseInsitu(reinterpret_cast<char*>(message.data()));

      if (doc.HasParseError())
        onJsonParseError(session, doc);
      else
        onDocument(session, doc);
    }

    virtual void onDocument(lwsxx::WebSocketSession* session, const rapidjson::Document& doc) = 0;

    virtual void onJsonParseError(lwsxx::WebSocketSession* session, const rapidjson::Document& doc)
    {
      std::cerr << "Error parsing command JSON message at offset " << doc.GetErrorOffset()
        << ": " << GetParseError_En(doc.GetParseError()) << std::endl;
    };
  };
}
