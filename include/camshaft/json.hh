#pragma once

#include <stdexcept>
#include <string>
#include <vector>

#include <rapidjson/document.h>

void loadJsonFile(const std::string& path, rapidjson::Document& doc);

template<typename Encoding>
const char* getString(const rapidjson::GenericValue<Encoding>& value, const char* memberName, bool allowNull = true)
{
  auto member = value.FindMember(memberName);
  if (member == value.MemberEnd())
  {
    if (allowNull)
      return nullptr;
    throw std::runtime_error(std::string("Expected member name: ") + memberName);
  }
  if (member->value.IsNull())
  {
    if (allowNull)
      return nullptr;
    throw std::runtime_error(std::string("Member '") + memberName + "' cannot be null");
  }
  if (!member->value.IsString())
    throw std::runtime_error(std::string("Member '") + memberName + "' must be a string");
  return member->value.GetString();
}

template<typename Encoding>
bool tryGetString(const rapidjson::GenericValue<Encoding>& value, const char* memberName, std::string& out)
{
  auto member = value.FindMember(memberName);
  if (member == value.MemberEnd())
    return false;
  if (!member->value.IsString())
    return false;
  out = member->value.GetString();
  return true;
}

template<typename Encoding>
const rapidjson::GenericValue<Encoding>& getObject(const rapidjson::GenericValue<Encoding>& value, const char* memberName)
{
  auto member = value.FindMember(memberName);
  if (member == value.MemberEnd())
    throw std::runtime_error(std::string("Expected member name: ") + memberName);
  if (!member->value.IsObject())
    throw std::runtime_error(std::string("Member '") + memberName + "' must be an object");
  return member->value;
}

template<typename Encoding>
bool tryGetObject(const rapidjson::GenericValue<Encoding>& value, const char* memberName, const rapidjson::GenericValue<Encoding>** out)
{
  auto member = value.FindMember(memberName);
  if (member == value.MemberEnd())
    return false;
  if (!member->value.IsObject())
    return false;
  *out = &member->value;
  return true;
}

template<typename Encoding>
const rapidjson::GenericValue<Encoding>& getArray(const rapidjson::GenericValue<Encoding>& value, const char* memberName)
{
  auto member = value.FindMember(memberName);
  if (member == value.MemberEnd())
    throw std::runtime_error(std::string("Expected member name: ") + memberName);
  if (!member->value.IsArray())
    throw std::runtime_error(std::string("Member '") + memberName + "' must be an array");
  return member->value;
}

template<typename Encoding>
bool tryGetArray(const rapidjson::GenericValue<Encoding>& value, const char* memberName, const rapidjson::GenericValue<Encoding>** out)
{
  auto member = value.FindMember(memberName);
  if (member == value.MemberEnd())
    return false;
  if (!member->value.IsArray())
    return false;
  *out = &member->value;
  return true;
}

template<typename Encoding>
std::vector<std::string> getStringArray(const rapidjson::GenericValue<Encoding>& value, const char* memberName)
{
  std::vector<std::string> values;
  auto member = value.FindMember(memberName);
  if (member != value.MemberEnd() && member->value.IsArray())
  {
    for (auto it = member->value.Begin(); it != member->value.End(); it++)
    {
      // NOTE no coercion here to string
      if (it->IsString())
        values.push_back(it->GetString());
    }
  }
  return move(values);
}

template<typename Encoding>
double getDouble(const rapidjson::GenericValue<Encoding>& value, const char* memberName)
{
  auto member = value.FindMember(memberName);
  if (member == value.MemberEnd())
    throw std::runtime_error(std::string("Expected member name: ") + memberName);
  if (!member->value.IsNumber())
    throw std::runtime_error(std::string("Member '") + memberName + "' must be a number");
  return member->value.GetDouble();
}

template<typename Encoding>
bool tryGetDouble(const rapidjson::GenericValue<Encoding>& value, const char* memberName, double& out)
{
  auto member = value.FindMember(memberName);
  if (member == value.MemberEnd())
    return false;
  if (!member->value.IsNumber())
    return false;
  out = member->value.GetDouble();
  return true;
}

template<typename Encoding>
int getInt(const rapidjson::GenericValue<Encoding>& value, const char* memberName)
{
  auto member = value.FindMember(memberName);
  if (member == value.MemberEnd())
    throw std::runtime_error(std::string("Expected member name: ") + memberName);
  if (!member->value.IsInt())
    throw std::runtime_error(std::string("Member '") + memberName + "' must be an int");
  return member->value.GetInt();
}

template<typename Encoding>
bool tryGetInt(const rapidjson::GenericValue<Encoding>& value, const char* memberName, int& out)
{
  auto member = value.FindMember(memberName);
  if (member == value.MemberEnd())
    return false;
  if (!member->value.IsInt())
    return false;
  out = member->value.GetInt();
  return true;
}

template<typename Encoding>
long getLong(const rapidjson::GenericValue<Encoding>& value, const char* memberName)
{
  auto member = value.FindMember(memberName);
  if (member == value.MemberEnd())
    throw std::runtime_error(std::string("Expected member name: ") + memberName);
  if (!member->value.IsInt64())
    throw std::runtime_error(std::string("Member '") + memberName + "' must be a long");
  return member->value.GetInt64();
}

template<typename Encoding>
bool getBool(const rapidjson::GenericValue<Encoding>& value, const char* memberName)
{
  auto member = value.FindMember(memberName);
  if (member == value.MemberEnd())
    throw std::runtime_error(std::string("Expected member name: ") + memberName);
  if (!member->value.IsBool())
    throw std::runtime_error(std::string("Member '") + memberName + "' must be a bool");
  return member->value.GetBool();
}
