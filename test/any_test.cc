#include <gtest/gtest.h>

#include "camshaft/any.hh"
#include "camshaft/observable.hh"

using namespace std;

TEST(AnyTest, basics)
{
  any a;
  EXPECT_TRUE(a.empty());

  a = 1;
  EXPECT_FALSE(a.empty());
  EXPECT_EQ(1, any_cast<int>(a));

  EXPECT_EQ(typeid(int), a.type());

  a = "string";
  EXPECT_EQ(typeid(const char*), a.type());
  EXPECT_STREQ("string", any_cast<const char*>(a));
  EXPECT_THROW(any_cast<int>(a), bad_any_cast);

  a.clear();

  EXPECT_TRUE(a.empty());
  EXPECT_THROW(any_cast<int>(a), bad_any_cast);
}

TEST(AnyTest, accessValueByReference)
{
  any a;
  static_assert(is_lvalue_reference<decltype(any_cast<int&>(a))>::value, "Should return reference");

  // Verify that the referenced value is identical over multiple casts
  int i = 1;
  a = i; // copies value into 'any' container

  // multiple calls should return same reference
  int* p1 = &any_cast<int&>(a);
  int* p2 = &any_cast<int&>(a);

  EXPECT_EQ(p1, p2);
  EXPECT_NE(&i, p1);
}

TEST(AnyTest, copyAssignValue)
{
  {
    Observable o;
    any a;
    Observable::reset();
    a = o;

    EXPECT_EQ(0, Observable::ctorCount);
    EXPECT_EQ(0, Observable::dtorCount);
    EXPECT_EQ(1, Observable::copyCount);
    EXPECT_EQ(0, Observable::moveCount);
    EXPECT_EQ(0, Observable::assignCount);
  }
  EXPECT_EQ(2, Observable::dtorCount);
}

TEST(AnyTest, copyConstructValue)
{
  {
    Observable o;
    Observable::reset();
    any a(o);

    EXPECT_EQ(0, Observable::ctorCount);
    EXPECT_EQ(0, Observable::dtorCount);
    EXPECT_EQ(1, Observable::copyCount);
    EXPECT_EQ(0, Observable::moveCount);
    EXPECT_EQ(0, Observable::assignCount);
  }
  EXPECT_EQ(2, Observable::dtorCount);
}

TEST(AnyTest, moveValue)
{
  Observable::reset();
  {
    Observable o;
    any a(move(o));

    EXPECT_EQ(1, Observable::ctorCount);
    EXPECT_EQ(0, Observable::dtorCount);
    EXPECT_EQ(1, Observable::copyCount); // TODO shouldn't copy, should it?
    EXPECT_EQ(0, Observable::moveCount); // TODO why doesn't it move the value into the any here?
    EXPECT_EQ(0, Observable::assignCount);
  }
  EXPECT_EQ(2, Observable::dtorCount);
}

TEST(AnyTest, moveAny)
{
  {
    Observable o;
    any a(o);
    Observable::reset();
    any b(move(o));

    EXPECT_EQ(0, Observable::ctorCount);
    EXPECT_EQ(0, Observable::dtorCount);
    EXPECT_EQ(1, Observable::copyCount); // TODO shouldn't copy, should it?
    EXPECT_EQ(0, Observable::moveCount); // TODO why doesn't it move the value into the any here?
    EXPECT_EQ(0, Observable::assignCount);
  }
  EXPECT_EQ(3, Observable::dtorCount);
}

TEST(AnyTest, assignValue)
{
  {
    Observable o;
    any a1(o);
    any a2;
    Observable::reset();
    a2 = a1;

    EXPECT_EQ(0, Observable::ctorCount);
    EXPECT_EQ(0, Observable::dtorCount);
    EXPECT_EQ(1, Observable::copyCount); // TODO shouldn't copy, should it?
    EXPECT_EQ(0, Observable::moveCount); // TODO why doesn't it move the value into the any here?
    EXPECT_EQ(0, Observable::assignCount);
  }
  EXPECT_EQ(3, Observable::dtorCount); // o, a1, a2
}

TEST(AnyTest, is)
{
  any a;
  EXPECT_FALSE(a.is<int>());

  a = 1;

  EXPECT_TRUE(a.is<int>());
  EXPECT_TRUE(a.is<const int>());
  EXPECT_TRUE(a.is<volatile int>());
  EXPECT_TRUE(a.is<int&>());
  EXPECT_TRUE(a.is<int&&>());
  EXPECT_FALSE(a.is<unsigned int>());
  EXPECT_FALSE(a.is<double>());
}
