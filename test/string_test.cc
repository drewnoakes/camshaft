#include <gtest/gtest.h>

#include "camshaft/string.hh"

using namespace camshaft;
using namespace std;

TEST(StringTest, trim)
{
  string str;

  str = "  HELLO  ";
  EXPECT_EQ("HELLO", trim(str));

  str = "\r\nHELLO\r\n";
  EXPECT_EQ("HELLO", trim(str));

  str = "  HELLO\t";
  EXPECT_EQ("HELLO", trim(str));

  str = "\tHELLO\t";
  EXPECT_EQ("HELLO", trim(str));

  str = "\tHELLO WORLD\t";
  EXPECT_EQ("HELLO WORLD", trim(str));
}

TEST(StringTest, trimEnd)
{
  string str;

  str = "  HELLO  ";
  EXPECT_EQ("  HELLO", trim_end(str));

  str = "\r\nHELLO\r\n";
  EXPECT_EQ("\r\nHELLO", trim_end(str));

  str = "  HELLO";
  EXPECT_EQ("  HELLO", trim_end(str));

  str = "\tHELLO\t";
  EXPECT_EQ("\tHELLO", trim_end(str));

  str = "\tHELLO WORLD\t";
  EXPECT_EQ("\tHELLO WORLD", trim_end(str));
}

TEST(StringTest, trimFront)
{
  string str;

  str = "  HELLO  ";
  EXPECT_EQ("HELLO  ", trim_front(str));

  str = "\r\nHELLO\r\n";
  EXPECT_EQ("HELLO\r\n", trim_front(str));

  str = "  HELLO\t";
  EXPECT_EQ("HELLO\t", trim_front(str));

  str = "\tHELLO\t";
  EXPECT_EQ("HELLO\t", trim_front(str));

  str = "\tHELLO WORLD\t";
  EXPECT_EQ("HELLO WORLD\t", trim_front(str));
}


TEST(StringTest, removeNonAscii)
{
  string str;

  str = "HELLO WORLD";
  EXPECT_EQ("HELLO WORLD", remove_non_ascii(str));

  str = u8"HELLO\u00DAWORLD";
  EXPECT_EQ("HELLOWORLD", remove_non_ascii(str));
}
