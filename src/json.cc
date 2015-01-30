#include "camshaft/json.hh"

#include <rapidjson/filereadstream.h>
#include <rapidjson/error/en.h>

#include <camshaft/log.hh>

using namespace rapidjson;
using namespace std;

void loadJsonFile(const string& path, Document& doc)
{
  FILE* file = fopen(path.c_str(), "rb");

  char buffer[65536];
  FileReadStream is(file, buffer, sizeof(buffer));

  doc.ParseStream<0, UTF8<>, FileReadStream>(is);

  if (doc.HasParseError())
    log::warning("loadJsonFile")
      << "Error parsing JSON file \"" << path << "\" at offset "
      << doc.GetErrorOffset()
      << ": "
      << GetParseError_En(doc.GetParseError());
}
