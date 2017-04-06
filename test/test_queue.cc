/**
 * @file test_queue.cc
 * @author Omar A Serrano
 * @date 2016-03-18
 */

#include <vector>
#include <functional>
#include <random>

#include "gtest/gtest.h"
#include "queue/queue.hh"

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
TEST(PriorityQueue2, sizeParamCtor)
{
  PriorityQueue<int> pq(20);
  EXPECT_TRUE(pq.empty());
  EXPECT_EQ(20, pq.capacity());
}

// Test PriorityQueue constructor different compare type
TEST(PriorityQueue3, compTypeParamCtor)
{
  PriorityQueue<int, std::greater<int>> pq;
  EXPECT_TRUE(pq.empty());
  EXPECT_EQ(0, pq.size());

  auto f = [](const int &a, const int &b) -> bool { return a < b; };
  PriorityQueue<int, decltype(f)> pq1(f);
  EXPECT_TRUE(pq.empty());
  EXPECT_EQ(0, pq.size());
}

// Test PriorityQueue iterator ctor
TEST(PriorityQueue4, iterCtor)
{
  std::vector<int> ivec({10, 3, 7, 5, 1});
  PriorityQueue<int> pq(ivec.begin(), ivec.end());
  EXPECT_EQ(5, pq.size());
  EXPECT_EQ(1, pq.top());
  pq.pop();
  EXPECT_EQ(3, pq.top());
  EXPECT_EQ(4, pq.size());
}

// Test push
TEST(PriorityQueue5, push)
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
TEST(PriorityQueue9, topAndPop)
{
  PriorityQueue<int> lpq;
  lpq.push(7);
  lpq.push(7);
  lpq.push(9);
  lpq.push(8);
  lpq.push(4);
  lpq.push(5);
  lpq.push(6);
  lpq.push(2);
  lpq.push(2);
  lpq.push(1);

  EXPECT_EQ(10, lpq.size());
  EXPECT_EQ(1, lpq.top());

  lpq.pop();
  EXPECT_EQ(9, lpq.size());
  EXPECT_EQ(2, lpq.top());

  lpq.pop();
  EXPECT_EQ(8, lpq.size());
  EXPECT_EQ(2, lpq.top());

  lpq.pop();
  EXPECT_EQ(7, lpq.size());
  EXPECT_EQ(4, lpq.top());

  // Now test with different compare type
  PriorityQueue<int, std::greater<int>> gpq;
  gpq.push(2);
  gpq.push(2);
  gpq.push(8);
  gpq.push(1);
  gpq.push(7);
  gpq.push(7);
  gpq.push(9);
  gpq.push(4);
  gpq.push(5);
  gpq.push(6);

  EXPECT_EQ(9, gpq.top());
  gpq.pop();
  EXPECT_EQ(8, gpq.top());
  gpq.pop();
  EXPECT_EQ(7, gpq.top());
  gpq.pop();
  EXPECT_EQ(7, gpq.top());
  gpq.pop();
  EXPECT_EQ(6, gpq.top());
}

// Test top and pop with random numbers
TEST(PriorityQueue10, topAndPopRandom)
{
  auto randInt =
    std::bind(std::uniform_int_distribution<>(), std::default_random_engine(71));
  std::vector<int> ivec;
  for (int i = 0; i < 1000; ++i) ivec.push_back(randInt());

  PriorityQueue<int> lpq(ivec.cbegin(), ivec.cend());
  std::vector<int> orderedIvec;
  while (!lpq.empty()) {
    orderedIvec.push_back(lpq.top());
    lpq.pop();
  }
  std::sort(ivec.begin(), ivec.end());
  EXPECT_TRUE(std::equal(ivec.cbegin(), ivec.cend(), orderedIvec.cbegin()));
}

// Test capacity
TEST(PriorityQueue11, capacity)
{
  PriorityQueue<int> pq;

  EXPECT_EQ(8, pq.capacity());

  for (int i = 0; i < 8; ++i)
    pq.push(i);

  EXPECT_EQ(8, pq.capacity());

  pq.push(2);
  EXPECT_EQ(16, pq.capacity());
}

// Test toString
// TODO: implement test when priority queue iter is ready
TEST(PriorityQueue12, DISABLED_toString)
{
  PriorityQueue<int> pq;
  EXPECT_TRUE(pq.empty());
}

// Test hashCode
// TODO: implement test
TEST(PriorityQueue13, DISABLED_hashCode)
{
  PriorityQueue<int> pq;
  EXPECT_TRUE(pq.empty());
}

} // anonymous namespace
