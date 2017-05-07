/**
 * @file test_fringe.cc
 * @author Omar A Serrano
 * @date 2017-05-04
 */

#include <queue>
#include <stack>
#include <vector>

#include "gtest/gtest.h"
#include "graph/fringe.hh"


using namespace ospp;


namespace {


struct TestFringe : ::testing::Test
{
  Fringe<int> qFringe;

  void SetUp() override
  {
    qFringe.push(1);
    qFringe.push(2);
    qFringe.push(3);
    qFringe.push(4);
  }
};


TEST_F(TestFringe, EmptyShouldReturnTrueIfFringeIsEmpty)
{
  EXPECT_TRUE(Fringe<int>{}.empty());
}


TEST_F(TestFringe, EmptyShouldReturnFalseIfFringeIsNotEmpty)
{
  EXPECT_FALSE(qFringe.empty());
}


TEST_F(TestFringe, NextShouldReturnTheNextItem)
{
  EXPECT_EQ(1, qFringe.next());
}


TEST_F(TestFringe, PopShouldRemoveTheCurrentNextItem)
{
  qFringe.pop();
  EXPECT_EQ(2, qFringe.next());
}


TEST_F(TestFringe, SizeShouldReturnTheCorrectValue)
{
  EXPECT_EQ(4, qFringe.size());
}


} // anonymous namespace
