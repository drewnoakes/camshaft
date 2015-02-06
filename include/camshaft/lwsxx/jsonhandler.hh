#pragma once

#include <iostream>
#include <string>
#include <vector>

#include <camshaft/lwsxx/websocketjsonbuffer.hh>
#include <camshaft/log.hh>

#include <rapidjson/writer.h>
#include <rapidjson/document.h>
#include <rapidjson/error/en.h>

#include <lwsxx/websockethandler.hh>
#include <lwsxx/websocketsession.hh>
#include <lwsxx/http.hh>

namespace lwsxx { class WebSocketSession; }

namespace camshaft
{
  template<typename T>
  class JsonHandler : public T
  {
  protected:
    void receiveMessage(lwsxx::WebSocketSession* session, std::vector<byte>& message) override
    {
      message.push_back('\0');

      rapidjson::Document doc;
      doc.ParseInsitu(reinterpret_cast<char*>(message.data()));

      if (doc.HasParseError())
      {
        onJsonParseError(session, doc);
      }
      else
      {
        try
        {
          onDocument(session, doc);
        }
        catch (lwsxx::http_exception& ex)
        {
          WebSocketJsonBuffer buffer;
          rapidjson::Writer<WebSocketJsonBuffer> writer(buffer);
          writer.StartObject();
          {
            writer.String("error");
            writer.String(ex.what());
            writer.String("status");
            writer.Int((int)ex.httpStatus());
          }
          writer.EndObject();
          session->send(buffer);
        }
        catch (std::exception& ex)
        {
          WebSocketJsonBuffer buffer;
          rapidjson::Writer<WebSocketJsonBuffer> writer(buffer);
          writer.StartObject();
          {
            writer.String("error");
            writer.String(ex.what());
          }
          writer.EndObject();
          session->send(buffer);
        }
      }
    }

    virtual void onDocument(lwsxx::WebSocketSession* session, const rapidjson::Document& doc) = 0;

    virtual void onJsonParseError(lwsxx::WebSocketSession* session, const rapidjson::Document& doc)
    {
      log::warning("JsonHandler::onJsonParseError")
        << "Error parsing command JSON message at offset "
        << doc.GetErrorOffset()
        << ": "
        << GetParseError_En(doc.GetParseError());

      WebSocketJsonBuffer buffer;
      rapidjson::Writer<WebSocketJsonBuffer> writer(buffer);
      writer.StartObject();
      {
        writer.String("error");
        writer.String("JSON parse error");
        writer.String("offset");
        writer.Int64(doc.GetErrorOffset());
        writer.String("message");
        writer.String(rapidjson::GetParseError_En(doc.GetParseError()));
      }
      writer.EndObject();
      T::send(buffer);
    }
  };
}
