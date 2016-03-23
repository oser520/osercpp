/**
 * @file test_queue.cc
 * @author Omar A Serrano
 * @date 2016-03-18
 */

#include "gtest/gtest.h"
#include "queue.hh"

namespace {

using ospp::PriorityQueue;

// Test PriorityQueue default ctor
TEST(PriorityQueue, DefaultCtors)
{
  PriorityQueue<int> pq;
  EXPECT_TRUE(pq.empty());
  EXPECT_EQ(0, pq.size());
}

} // anonymous namespace

int main(int argc, char *argv[])
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
