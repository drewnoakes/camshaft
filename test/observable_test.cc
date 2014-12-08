#include <gtest/gtest.h>

#include "camshaft/observable.hh"

TEST(ObservableTest, observableUtil)
{
  // Default construction
  Observable::reset();
  Observable o;
  EXPECT_EQ(1, Observable::ctorCount);
  EXPECT_EQ(0, Observable::dtorCount);
  EXPECT_EQ(0, Observable::copyCount);
  EXPECT_EQ(0, Observable::moveCount);
  EXPECT_EQ(0, Observable::assignCount);

  // Construction and assignment
  Observable::reset();
  o = Observable();
  EXPECT_EQ(1, Observable::ctorCount);
  EXPECT_EQ(1, Observable::dtorCount);
  EXPECT_EQ(0, Observable::copyCount);
  EXPECT_EQ(0, Observable::moveCount);
  EXPECT_EQ(1, Observable::assignCount);

  // Construction and assignment
  Observable o1;
  Observable o2;
  Observable::reset();
  o2 = o1;
  EXPECT_EQ(0, Observable::ctorCount);
  EXPECT_EQ(0, Observable::dtorCount);
  EXPECT_EQ(0, Observable::copyCount);
  EXPECT_EQ(0, Observable::moveCount);
  EXPECT_EQ(1, Observable::assignCount);

  // Move
  Observable::reset();
  Observable o3(std::move(o1));
  EXPECT_EQ(0, Observable::ctorCount);
  EXPECT_EQ(0, Observable::dtorCount);
  EXPECT_EQ(0, Observable::copyCount);
  EXPECT_EQ(1, Observable::moveCount);
  EXPECT_EQ(0, Observable::assignCount);

  // Copy
  Observable::reset();
  Observable o4(o1);
  EXPECT_EQ(0, Observable::ctorCount);
  EXPECT_EQ(0, Observable::dtorCount);
  EXPECT_EQ(1, Observable::copyCount);
  EXPECT_EQ(0, Observable::moveCount);
  EXPECT_EQ(0, Observable::assignCount);

  // Destructor
  Observable::reset();
  {
    Observable o5;
  }
  EXPECT_EQ(1, Observable::ctorCount);
  EXPECT_EQ(1, Observable::dtorCount);
  EXPECT_EQ(0, Observable::copyCount);
  EXPECT_EQ(0, Observable::moveCount);
  EXPECT_EQ(0, Observable::assignCount);
}
