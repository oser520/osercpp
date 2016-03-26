/**
 * @file test_queue.cc
 * @author Omar A Serrano
 * @date 2016-03-18
 */

#include <vector>

#include "gtest/gtest.h"
#include "queue.hh"

namespace {

using ospp::PriorityQueue;

// Test PriorityQueue default ctor
TEST(PriorityQueue1, DefaultCtors)
{
  PriorityQueue<int> pq;
  EXPECT_TRUE(pq.empty());
  EXPECT_EQ(0, pq.size());
}

// Test PriorityQueue constructor with size parameter
TEST(PriorityQueue1, sizeParamCtor)
{
  PriorityQueue<int> pq(20);
  EXPECT_TRUE(pq.empty());
  EXPECT_EQ(0, pq.size());
}

// Test PriorityQueue constructor different compare type
TEST(PriorityQueue2, compareTypeParam)
{
  PriorityQueue<int, std::greater<int>> pq;
  EXPECT_TRUE(pq.empty());
  EXPECT_EQ(0, pq.size());
}

// Test PriorityQueue iterator ctor
TEST(PriorityQueue3, iterCtor)
{
  std::vector<int> ivec({1, 3, 5, 7, 10});
  PriorityQueue<int> pq(ivec.begin(), ivec.end());
  EXPECT_TRUE(pq.empty());
  EXPECT_EQ(5, pq.size());
}

// Test push
TEST(PriorityQueue4, push)
{
  PriorityQueue<int> pq;
  pq.push(7);
  pq.push(7);
  pq.push(9);
  pq.push(8);
  pq.push(4);
  pq.push(5);
  pq.push(6);
  pq.push(2);
  pq.push(2);
  pq.push(1);

  EXPECT_FALSE(pq.empty());
  EXPECT_EQ(10, pq.size());
}

// Test top and pop
TEST(PriorityQueue5, top_and_pop)
{
  PriorityQueue<int> pq;
  pq.push(7);
  pq.push(7);
  pq.push(9);
  pq.push(8);
  pq.push(4);
  pq.push(5);
  pq.push(6);
  pq.push(2);
  pq.push(2);
  pq.push(1);

  EXPECT_EQ(10, pq.size());
  EXPECT_EQ(1, pq.top());

  pq.pop();
  EXPECT_EQ(9, pq.size());
  EXPECT_EQ(2, pq.top());

  pq.pop();
  EXPECT_EQ(8, pq.size());
  EXPECT_EQ(2, pq.top());

  pq.pop();
  EXPECT_EQ(7, pq.size());
  EXPECT_EQ(4, pq.top());
}

// Test toString
// TODO: implement test
DISABLED_TEST(PriorityQueue6, toString)
{
  PriorityQueue<int> pq;
  pq.push(7);
  pq.push(7);
  pq.push(9);
  pq.push(8);
  pq.push(4);
  pq.push(5);
  pq.push(6);
  pq.push(2);
  pq.push(2);
  pq.push(1);

  EXPECT_EQ(10, pq.size());
  EXPECT_EQ(1, pq.top());

  pq.pop();
  EXPECT_EQ(9, pq.size());
  EXPECT_EQ(2, pq.top());

  pq.pop();
  EXPECT_EQ(8, pq.size());
  EXPECT_EQ(2, pq.top());

  pq.pop();
  EXPECT_EQ(7, pq.size());
  EXPECT_EQ(4, pq.top());
}

} // anonymous namespace

int main(int argc, char *argv[])
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
