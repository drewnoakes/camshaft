#include "camshaft/uuid.hh"

#include <uuid/uuid.h>
#include <cassert>
#include <functional>

using namespace std;

Uuid Uuid::random()
{
  Uuid uuid;
  uuid_generate(uuid._bytes.data());
  return uuid;
}

Uuid Uuid::parse(const string& uuidString)
{
  Uuid uuid;
  uuid_parse(uuidString.c_str(), uuid._bytes.data());
  return uuid;
}

string Uuid::toString(UuidStringFormat format) const
{
  string s;
  s.resize(36);
  assert(s.size() == 36);
  std::function<void(const unsigned char*,char*)> unparse;
  switch (format)
  {
    case UuidStringFormat::Unspecified: unparse = uuid_unparse;       break;
    case UuidStringFormat::Lower:       unparse = uuid_unparse_lower; break;
    case UuidStringFormat::Upper:       unparse = uuid_unparse_upper; break;
  }
  unparse(this->_bytes.data(), const_cast<char*>(s.c_str()));
  return s;
}

bool Uuid::operator <(const Uuid& other) const
{
  return uuid_compare(this->_bytes.data(), other._bytes.data()) < 0;
}

bool Uuid::operator ==(const Uuid& other) const
{
  return uuid_compare(this->_bytes.data(), other._bytes.data()) == 0;
}

bool Uuid::operator !=(const Uuid& other) const
{
  return uuid_compare(this->_bytes.data(), other._bytes.data()) != 0;
}
