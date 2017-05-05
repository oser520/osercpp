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
  Fringe<int, std::queue> qFringe;
  Fringe<int, std::stack> sFringe;
  std::vector<int> data{0, 1, 2, 3, 4, 5};
};


TEST_F(TestFringe, EmptyShouldReturnTrueIfFringeIsEmpty)
{
  EXPECT_TRUE(qFringe.empty());
  EXPECT_TRUE(sFringe.empty());
}


} // anonymous namespace
