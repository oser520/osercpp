/**
 * @file test_snode.cc
 * @author Omar A Serrano
 * @date 2017-04-06
 */

#include <string>

#include "gtest/gtest.h"
#include "linked-list/snode.hh"


namespace {


using namespace ospp;


TEST(TestSNode, IntNodeDefaultCtorShouldDefaultInitialize)
{
  Node<int> intNode;
  EXPECT_EQ(0, intNode.data);
  EXPECT_EQ(nullptr, intNode.next);
}


} // anonymous namespace
