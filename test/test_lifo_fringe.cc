/**
 * @file test_fifo_fringe.cc
 * @author Omar A Serrano
 * @date 2017-06-02
 */

#include "gtest/gtest.h"
#include "graph/lifo_fringe.hh"


using namespace ospp;


namespace {


struct TestLifoFringe : ::testing::Test
{
  LifoFringe<int> intFringe;
};


TEST_F(TestLifoFringe, EmptyShouldReturnTrueIfFringeIsEmpty)
{
  EXPECT_TRUE(intFringe.empty());
}


TEST_F(TestLifoFringe, PushingToFringeShouldResultInNonEmptyFringe)
{
  intFringe.push(1);
  EXPECT_FALSE(intFringe.empty());
}


TEST_F(TestLifoFringe, NextShouldReturnTheNextItem)
{
  intFringe.push(1);
  intFringe.push(2);
  EXPECT_EQ(2, intFringe.next());
}


TEST_F(TestLifoFringe, PopShouldRemoveTheNextItem)
{
  intFringe.push(1);
  intFringe.push(2);
  intFringe.pop();
  EXPECT_EQ(1, intFringe.next());
}


} // anonymous namespace
