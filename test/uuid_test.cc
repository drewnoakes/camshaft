#include <gtest/gtest.h>

#include <uuid/uuid.h>
#include <map>

#include "camshaft/uuid.hh"

TEST(UuidTest, libuuidParseCompareAndFormat)
{
  auto uuidString1 = "c5ccea57-4076-4703-b07e-e48d090becce";
  auto uuidString2 = "00000000-0000-0000-0000-000000000000";

  uuid_t parsed1;
  EXPECT_EQ(0, uuid_parse(uuidString1, parsed1));

  uuid_t parsed2;
  EXPECT_EQ(0, uuid_parse(uuidString2, parsed2));

  EXPECT_EQ(1, uuid_compare(parsed1, parsed2));

  char format[37];
  uuid_unparse_lower(parsed1, format);

  EXPECT_EQ(0, strcmp(uuidString1, format));
}

TEST(UuidTest, parseCompareAndFormat)
{
  auto uuidString1 = "c5ccea57-4076-4703-b07e-e48d090becce";
  auto uuidString2 = "00000000-0000-0000-0000-000000000000";

  Uuid parsed1a = Uuid::parse(uuidString1);
  Uuid parsed1b = Uuid::parse(uuidString1);
  Uuid parsed2 = Uuid::parse(uuidString2);

  EXPECT_EQ(parsed1a, parsed1b);
  EXPECT_EQ(parsed1b, parsed1a);
  EXPECT_NE(parsed1a, parsed2);
  EXPECT_NE(parsed2, parsed1a);
  EXPECT_EQ(uuidString1, parsed1a.toString(UuidStringFormat::Lower));
}

// TODO verify throws on invalid parse
// TODO test errors during parsing

TEST(UuidTest, worksAsMapKey)
{
  Uuid uuid1 = Uuid::random();
  Uuid uuid2 = Uuid::random();

  std::map<Uuid,int> map;
  map.insert(std::make_pair(uuid1, 1));
  map.insert(std::make_pair(uuid2, 2));

  EXPECT_EQ(2, map.size());

  auto it1 = map.find(uuid1);
  auto it2 = map.find(uuid2);
  auto it3 = map.find(Uuid::random());

  EXPECT_EQ(1, it1->second);
  EXPECT_EQ(2, it2->second);
  EXPECT_EQ(map.end(), it3);
}
