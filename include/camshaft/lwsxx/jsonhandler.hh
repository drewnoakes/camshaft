#pragma once

#include <iostream>
#include <string>
#include <vector>

#include <rapidjson/document.h>
#include <rapidjson/error/en.h>

#include <lwsxx/websockethandler.hh>

namespace camshaft
{
  namespace lwsxx
  {
    class JsonHandler : public ::lwsxx::WebSocketHandler
    {
    protected:
      void receiveMessage(std::vector<byte>& message) override
      {
        message.push_back('\0');

        rapidjson::Document doc;
        doc.ParseInsitu(reinterpret_cast<char*>(message.data()));

        if (doc.HasParseError())
          onJsonParseError(doc);
        else
          onDocument(doc);
      }

      virtual void onDocument(const rapidjson::Document& doc) = 0;

      virtual void onJsonParseError(const rapidjson::Document& doc)
      {
        std::cerr << "Error parsing command JSON message at offset " << doc.GetErrorOffset()
          << ": " << GetParseError_En(doc.GetParseError()) << std::endl;
      };
    };
  }
}
