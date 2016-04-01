/**
 * @file test_queue.cc
 * @author Omar A Serrano
 * @date 2016-03-18
 */

#include <vector>
#include <functional>

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
TEST(PriorityQueue2, sizeParamCtor)
{
  PriorityQueue<int> pq(20);
  EXPECT_TRUE(pq.empty());
  EXPECT_EQ(20, pq.capacity());
}

// Test PriorityQueue constructor different compare type
TEST(PriorityQueue3, compareTypeParam)
{
  PriorityQueue<int, std::greater<int>> pq;
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

// Test parent
TEST(PriorityQueue6, parent)
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

  EXPECT_EQ(-1, pq.parent(0));
  EXPECT_EQ(0, pq.parent(1));
  EXPECT_EQ(0, pq.parent(2));
  EXPECT_EQ(1, pq.parent(3));
  EXPECT_EQ(1, pq.parent(4));
  EXPECT_EQ(2, pq.parent(5));
  EXPECT_EQ(2, pq.parent(6));
  EXPECT_EQ(3, pq.parent(7));
  EXPECT_EQ(3, pq.parent(8));
  EXPECT_EQ(4, pq.parent(9));
}

// Test leftChild
TEST(PriorityQueue7, leftChild)
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

  EXPECT_EQ(1, pq.leftChild(0));
  EXPECT_EQ(3, pq.leftChild(1));
  EXPECT_EQ(5, pq.leftChild(2));
  EXPECT_EQ(7, pq.leftChild(3));
  EXPECT_EQ(9, pq.leftChild(4));
}

// Test rightChild
TEST(PriorityQueue8, rightChild)
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

  EXPECT_EQ(2, pq.rightChild(0));
  EXPECT_EQ(4, pq.rightChild(1));
  EXPECT_EQ(6, pq.rightChild(2));
  EXPECT_EQ(8, pq.rightChild(3));
  EXPECT_EQ(10, pq.rightChild(4));
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

// Test capacity
TEST(PriorityQueue10, capacity)
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
TEST(PriorityQueue11, DISABLED_toString)
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

// Test hashCode
// TODO: implement test
TEST(PriorityQueue12, DISABLED_hashCode)
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

  pq.pop();
  EXPECT_EQ(6, pq.size());
  EXPECT_EQ(5, pq.top());

  pq.pop();
  EXPECT_EQ(5, pq.size());
  EXPECT_EQ(6, pq.top());

  pq.pop();
  EXPECT_EQ(4, pq.size());
  EXPECT_EQ(7, pq.top());

  pq.pop();
  EXPECT_EQ(3, pq.size());
  EXPECT_EQ(7, pq.top());

  pq.pop();
  EXPECT_EQ(2, pq.size());
  EXPECT_EQ(8, pq.top());

  pq.pop();
  EXPECT_EQ(1, pq.size());
  EXPECT_EQ(9, pq.top());

  pq.pop();
  EXPECT_EQ(0, pq.size());
  EXPECT_TRUE(pq.empty());
}

} // anonymous namespace

int main(int argc, char *argv[])
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
