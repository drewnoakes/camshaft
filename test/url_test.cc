#include <gtest/gtest.h>

#include "camshaft/url.hh"

using namespace std;

TEST(UrlTest, parseQueryString_simple)
{
  auto res = parseQueryString("?foo=100,200&bar=\"two\"");

  ASSERT_EQ(2, res.size());

  ASSERT_TRUE(res.find("foo") != res.end());
  ASSERT_TRUE(res.find("bar") != res.end());

  ASSERT_EQ("100,200", res.find("foo")->second);
  ASSERT_EQ("\"two\"", res.find("bar")->second);
}

TEST(UrlTest, parseQueryString_empty)
{
  auto res = parseQueryString("");

  ASSERT_TRUE(res.empty());
}

TEST(UrlTest, parseQueryString_name_only)
{
  auto res = parseQueryString("?universe");

  ASSERT_EQ(1, res.size());
  ASSERT_TRUE(res.find("universe") != res.end());

  ASSERT_EQ("", res.find("universe")->second);
}

TEST(UrlTest, parseQueryString_more_args)
{
  auto res = parseQueryString("?foo=100,200&bar=\"two\"&univsers&my=mine123");

  ASSERT_EQ(4, res.size());
  ASSERT_TRUE(res.find("my") != res.end());

  ASSERT_EQ("mine123", res.find("my")->second);
}

TEST(UrlTest, parseQueryString_multipleValues)
{
  auto res = parseQueryString("a=1&a=2&b=3&b=3&b=3");

  ASSERT_EQ(5, res.size());
  ASSERT_TRUE(res.find("a") != res.end());
  ASSERT_TRUE(res.find("b") != res.end());

  auto a_range = res.equal_range("a");
  auto b_range = res.equal_range("b");

  ASSERT_EQ(2, distance(a_range.first, a_range.second));
  ASSERT_EQ(3, distance(b_range.first, b_range.second));

  vector<string> a_values;
  vector<string> b_values;

  for (auto it = a_range.first; it != a_range.second; it++)
    a_values.push_back(it->second);
  for (auto it = b_range.first; it != b_range.second; it++)
    b_values.push_back(it->second);

  ASSERT_EQ("1", a_values[0]);
  ASSERT_EQ("2", a_values[1]);

  ASSERT_EQ("3", b_values[0]);
  ASSERT_EQ("3", b_values[1]);
  ASSERT_EQ("3", b_values[2]);
}
