#pragma once

#include <string>
#include <array>
#include <iostream>

enum class UuidStringFormat
{
  Unspecified,
  Upper,
  Lower
};

class Uuid
{
public:
  static Uuid random();

  /// Parse the string as a UUID, throwing if unable
  static Uuid parse(const std::string& uuidString);

  Uuid(const Uuid&) = default;
  Uuid& operator=(const Uuid&) = default;
  ~Uuid() = default;

  /// Returns this UUID as a 32 character string
  std::string toString(UuidStringFormat format = UuidStringFormat::Unspecified) const;

  bool operator<(const Uuid& other) const;
  bool operator==(const Uuid& other) const;
  bool operator!=(const Uuid& other) const;

private:
  Uuid() = default;

  std::array<unsigned char, 16> _bytes;
};

inline std::ostream& operator<<(std::ostream& stream, const Uuid& uuid)
{
  return stream << uuid.toString();
}
