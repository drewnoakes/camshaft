#include "camshaft/lwsxx/jsonhandler.hh"

#include "camshaft/lwsxx/websocketjsonbuffer.hh"

#include <rapidjson/error/en.h>
#include <rapidjson/writer.h>

#include <lwsxx/websocketsession.hh>
#include <lwsxx/http.hh>

#include <camshaft/log.hh>

using namespace camshaft;
using namespace rapidjson;
using namespace std;
using namespace lwsxx;

void JsonHandler::receiveMessage(lwsxx::WebSocketSession* session, std::vector<byte>& message)
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
      Writer<WebSocketJsonBuffer> writer(buffer);
      writer.StartObject();
      {
        writer.String("error");
        writer.String(ex.what());
        writer.String("status");
        writer.Int((int)ex.httpStatus());
      }
      writer.EndObject();
      send(buffer);
    }
    catch (exception& ex)
    {
      WebSocketJsonBuffer buffer;
      Writer<WebSocketJsonBuffer> writer(buffer);
      writer.StartObject();
      {
        writer.String("error");
        writer.String(ex.what());
      }
      writer.EndObject();
      send(buffer);
    }
  }
}

void JsonHandler::onJsonParseError(lwsxx::WebSocketSession*, const rapidjson::Document& doc)
{
  log::warning("JsonHandler::onJsonParseError")
    << "Error parsing command JSON message at offset "
    << doc.GetErrorOffset()
    << ": "
    << GetParseError_En(doc.GetParseError());

  WebSocketJsonBuffer buffer;
  Writer<WebSocketJsonBuffer> writer(buffer);
  writer.StartObject();
  {
    writer.String("error");
    writer.String("JSON parse error");
    writer.String("offset");
    writer.Int64(doc.GetErrorOffset());
    writer.String("message");
    writer.String(GetParseError_En(doc.GetParseError()));
  }
  writer.EndObject();
  send(buffer);
}
