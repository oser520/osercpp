/**
 * @file test_fifo_fringe.cc
 * @author Omar A Serrano
 * @date 2017-05-26
 */

#include "gtest/gtest.h"
#include "graph/fifo_fringe.hh"


using namespace ospp;


namespace {


struct TestFifoFringe : ::testing::Test
{
  FifoFringe<int> intFringe;
};


TEST_F(TestFifoFringe, EmptyShouldReturnTrueIfFringeIsEmpty)
{
  EXPECT_TRUE(intFringe.empty());
}


TEST_F(TestFifoFringe, PushingToFringeShouldResultInNonEmptyFringe)
{
  intFringe.push(1);
  EXPECT_FALSE(intFringe.empty());
}


TEST_F(TestFifoFringe, NextShouldReturnTheNextItem)
{
  intFringe.push(1);
  intFringe.push(2);
  EXPECT_EQ(1, intFringe.next());
}


} // anonymous namespace
