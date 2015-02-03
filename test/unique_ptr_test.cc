#include <gtest/gtest.h>

#include <memory>
#include <camshaft/memory.hh>

#include "camshaft/observable.hh"

using namespace std;

TEST(UniquePtrTest, empty)
{
  Observable::reset();

  unique_ptr<Observable> u;

  EXPECT_EQ(0, Observable::ctorCount);
  EXPECT_EQ(0, Observable::dtorCount);
  EXPECT_EQ(0, Observable::copyCount);
  EXPECT_EQ(0, Observable::moveCount);
  EXPECT_EQ(0, Observable::assignCount);

  ASSERT_EQ(nullptr, u.get());
}

TEST(UniquePtrTest, constructedWithPtr)
{
  Observable::reset();

  auto o = new Observable();

  EXPECT_EQ(1, Observable::ctorCount);
  EXPECT_EQ(0, Observable::dtorCount);
  EXPECT_EQ(0, Observable::copyCount);
  EXPECT_EQ(0, Observable::moveCount);
  EXPECT_EQ(0, Observable::assignCount);

  Observable::reset();

  unique_ptr<Observable> u(o);

  EXPECT_EQ(0, Observable::ctorCount);
  EXPECT_EQ(0, Observable::dtorCount);
  EXPECT_EQ(0, Observable::copyCount);
  EXPECT_EQ(0, Observable::moveCount);
  EXPECT_EQ(0, Observable::assignCount);

  ASSERT_EQ(o, u.get());
}

TEST(UniquePtrTest, reset)
{
  Observable::reset();

  auto o = new Observable();

  EXPECT_EQ(1, Observable::ctorCount);
  EXPECT_EQ(0, Observable::dtorCount);
  EXPECT_EQ(0, Observable::copyCount);
  EXPECT_EQ(0, Observable::moveCount);
  EXPECT_EQ(0, Observable::assignCount);

  Observable::reset();

  unique_ptr<Observable> u;

  ASSERT_EQ(nullptr, u.get());

  u.reset(o);

  ASSERT_EQ(o, u.get());

  EXPECT_EQ(0, Observable::ctorCount);
  EXPECT_EQ(0, Observable::dtorCount);
  EXPECT_EQ(0, Observable::copyCount);
  EXPECT_EQ(0, Observable::moveCount);
  EXPECT_EQ(0, Observable::assignCount);
}

TEST(UniquePtrTest, destruction)
{
  Observable::reset();

  {
    unique_ptr<Observable> u(new Observable());

    EXPECT_EQ(1, Observable::ctorCount);
    EXPECT_EQ(0, Observable::dtorCount);
    EXPECT_EQ(0, Observable::copyCount);
    EXPECT_EQ(0, Observable::moveCount);
    EXPECT_EQ(0, Observable::assignCount);

    Observable::reset();

    // Now, unqique_ptr falls out of scope and is destructed (RAII)
  }

  EXPECT_EQ(0, Observable::ctorCount);
  EXPECT_EQ(1, Observable::dtorCount);
  EXPECT_EQ(0, Observable::copyCount);
  EXPECT_EQ(0, Observable::moveCount);
  EXPECT_EQ(0, Observable::assignCount);
}

void unique_ptr_acceptor(unique_ptr<Observable> u)
{
  u.get();
}

TEST(UniquePtrTest, move)
{
  unique_ptr<Observable> u(new Observable());

  ASSERT_NE(nullptr, u.get()); // null

  Observable::reset();

  unique_ptr_acceptor(move(u));

  EXPECT_EQ(0, Observable::ctorCount);
  EXPECT_EQ(1, Observable::dtorCount);
  EXPECT_EQ(0, Observable::copyCount);
  EXPECT_EQ(0, Observable::moveCount);
  EXPECT_EQ(0, Observable::assignCount);

  ASSERT_EQ(nullptr, u.get()); // null after move
}

TEST(UniquePtrTest, make_unique)
{
  auto u1 = unique_ptr<string>(new string("hello"));

  auto u2 = make_unique<string>("hello");

  (void)u1; // suppress warnings
  (void)u2;
}
