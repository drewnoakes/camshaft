#include <gtest/gtest.h>

#include <memory>

#include "camshaft/observable.hh"

using namespace std;

TEST(SharedPtrTest, empty)
{
  Observable::reset();

  shared_ptr<Observable> sp;

  EXPECT_EQ(0, Observable::ctorCount);
  EXPECT_EQ(0, Observable::dtorCount);
  EXPECT_EQ(0, Observable::copyCount);
  EXPECT_EQ(0, Observable::moveCount);
  EXPECT_EQ(0, Observable::assignCount);

  EXPECT_EQ(nullptr, sp.get());
}

TEST(SharedPtrTest, owning)
{
  Observable::reset();

  Observable* o = new Observable();

  shared_ptr<Observable> sp(o);

  EXPECT_EQ(1, Observable::ctorCount);
  EXPECT_EQ(0, Observable::dtorCount);
  EXPECT_EQ(0, Observable::copyCount);
  EXPECT_EQ(0, Observable::moveCount);
  EXPECT_EQ(0, Observable::assignCount);

  EXPECT_EQ(o, sp.get());
}

TEST(SharedPtrTest, destruction)
{
  {
    shared_ptr<Observable> sp(new Observable());
    Observable::reset();
  }

  EXPECT_EQ(0, Observable::ctorCount);
  EXPECT_EQ(1, Observable::dtorCount);
  EXPECT_EQ(0, Observable::copyCount);
  EXPECT_EQ(0, Observable::moveCount);
  EXPECT_EQ(0, Observable::assignCount);
}

TEST(SharedPtrTest, copy)
{
  Observable::reset();

  shared_ptr<Observable> p1(new Observable());
  shared_ptr<Observable> p2 = p1;

  EXPECT_EQ(1, Observable::ctorCount);
  EXPECT_EQ(0, Observable::dtorCount);
  EXPECT_EQ(0, Observable::copyCount);
  EXPECT_EQ(0, Observable::moveCount);
  EXPECT_EQ(0, Observable::assignCount);
}

TEST(SharedPtrTest, destroyCopy)
{
  Observable* o = new Observable();

  Observable::reset();

  shared_ptr<Observable> p1;

  {
    shared_ptr<Observable> p2(o);
    p1 = p2;

    EXPECT_EQ(p1.get(), p2.get());
    EXPECT_EQ(p1, p2);
    EXPECT_EQ(o, p1.get());
    EXPECT_EQ(o, p2.get());
  }

  EXPECT_EQ(0, Observable::ctorCount);
  EXPECT_EQ(0, Observable::dtorCount);
  EXPECT_EQ(0, Observable::copyCount);
  EXPECT_EQ(0, Observable::moveCount);
  EXPECT_EQ(0, Observable::assignCount);
}

TEST(SharedPtrTest, reset)
{
  Observable* o = new Observable();

  Observable::reset();

  shared_ptr<Observable> p1(o);
  p1.reset();

  EXPECT_EQ(nullptr, p1.get());

  EXPECT_EQ(0, Observable::ctorCount);
  EXPECT_EQ(1, Observable::dtorCount);
  EXPECT_EQ(0, Observable::copyCount);
  EXPECT_EQ(0, Observable::moveCount);
  EXPECT_EQ(0, Observable::assignCount);
}

TEST(SharedPtrTest, resetCopy)
{
  Observable* o = new Observable();

  Observable::reset();

  shared_ptr<Observable> p1(o);
  shared_ptr<Observable> p2 = p1;
  p1.reset();

  EXPECT_EQ(nullptr, p1.get());
  EXPECT_EQ(o, p2.get());

  EXPECT_EQ(0, Observable::ctorCount);
  EXPECT_EQ(0, Observable::dtorCount);
  EXPECT_EQ(0, Observable::copyCount);
  EXPECT_EQ(0, Observable::moveCount);
  EXPECT_EQ(0, Observable::assignCount);
}

TEST(SharedPtrTest, destroyAllCopies)
{
  Observable* o = new Observable();

  {
    shared_ptr<Observable> p1(o);
    shared_ptr<Observable> p2 = p1;

    Observable::reset();
  }

  EXPECT_EQ(0, Observable::ctorCount);
  EXPECT_EQ(1, Observable::dtorCount);
  EXPECT_EQ(0, Observable::copyCount);
  EXPECT_EQ(0, Observable::moveCount);
  EXPECT_EQ(0, Observable::assignCount);
}
