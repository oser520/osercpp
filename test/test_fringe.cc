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
  std::vector<int> data{0, 1, 2, 3, 4, 5};
};


TEST_F(TestFringe, EmptyShouldReturnTrueIfFringeIsEmpty)
{
  EXPECT_TRUE(qFringe.empty());
}


TEST_F(TestFringe, EmptyShouldReturnFalseIfFringeIsNotEmpty)
{
  qFringe.push(1);
  EXPECT_FALSE(qFringe.empty());
}


TEST_F(TestFringe, NextShouldReturnTheNextItem)
{
  qFringe.push(1);
  qFringe.push(2);
  EXPECT_EQ(1, qFringe.next());
}


} // anonymous namespace
