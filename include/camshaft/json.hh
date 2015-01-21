#pragma once

#include <string>
#include <rapidjson/document.h>

inline const char* getJsonString(const rapidjson::Value& value, const char* memberName)
{
  auto member = value.FindMember(memberName);
  if (member == value.MemberEnd())
    throw std::runtime_error(std::string("Expected member name: ") + memberName);
  if (!member->value.IsString())
    throw std::runtime_error(std::string("Member '") + memberName + "' must be a string");
  return member->value.GetString();
}

inline const rapidjson::Value& getObject(const rapidjson::Value& value, const char* memberName)
{
  auto member = value.FindMember(memberName);
  if (member == value.MemberEnd())
    throw std::runtime_error(std::string("Expected member name: ") + memberName);
  if (!member->value.IsObject())
    throw std::runtime_error(std::string("Member '") + memberName + "' must be an object");
  return member->value;
}

inline bool tryGetObject(const rapidjson::Value& value, const char* memberName, const rapidjson::Value** out)
{
  auto member = value.FindMember(memberName);
  if (member == value.MemberEnd())
    return false;
  if (!member->value.IsObject())
    return false;
  *out = &member->value;
  return true;
}

inline bool tryGetArray(const rapidjson::Value& value, const char* memberName, const rapidjson::Value** out)
{
  auto member = value.FindMember(memberName);
  if (member == value.MemberEnd())
    return false;
  if (!member->value.IsArray())
    return false;
  *out = &member->value;
  return true;
}

inline double getDouble(const rapidjson::Value& value, const char* memberName)
{
  auto member = value.FindMember(memberName);
  if (member == value.MemberEnd())
    throw std::runtime_error(std::string("Expected member name: ") + memberName);
  if (!member->value.IsNumber())
    throw std::runtime_error(std::string("Member '") + memberName + "' must be a number");
  return member->value.GetDouble();
}

inline bool tryGetDouble(const rapidjson::Value& value, const char* memberName, double& out)
{
  auto member = value.FindMember(memberName);
  if (member == value.MemberEnd())
    return false;
  if (!member->value.IsNumber())
    return false;
  out = member->value.GetDouble();
  return true;
}

inline int getInt(const rapidjson::Value& value, const char* memberName)
{
  auto member = value.FindMember(memberName);
  if (member == value.MemberEnd())
    throw std::runtime_error(std::string("Expected member name: ") + memberName);
  if (!member->value.IsInt())
    throw std::runtime_error(std::string("Member '") + memberName + "' must be an int");
  return member->value.GetInt();
}

inline long getLong(const rapidjson::Value& value, const char* memberName)
{
  auto member = value.FindMember(memberName);
  if (member == value.MemberEnd())
    throw std::runtime_error(std::string("Expected member name: ") + memberName);
  if (!member->value.IsInt64())
    throw std::runtime_error(std::string("Member '") + memberName + "' must be a long");
  return member->value.GetInt64();
}

inline const char* getString(const rapidjson::Value& value, const char* memberName)
{
  auto member = value.FindMember(memberName);
  if (member == value.MemberEnd())
    throw std::runtime_error(std::string("Expected member name: ") + memberName);
  if (!member->value.IsString())
    throw std::runtime_error(std::string("Member '") + memberName + "' must be a string");
  return member->value.GetString();
}

inline bool tryGetString(const rapidjson::Value& value, const char* memberName, std::string& out)
{
  auto member = value.FindMember(memberName);
  if (member == value.MemberEnd())
    return false;
  if (!member->value.IsString())
    return false;
  out = member->value.GetString();
  return true;
}
