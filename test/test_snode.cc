/**
 * @file test_snode.cc
 * @author Omar A Serrano
 * @date 2017-04-06
 */

#include <string>
#include <type_traits>

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


TEST(TestSNode, IntNodeDefaultCtorShouldBeNoExcept)
{
  EXPECT_TRUE(std::is_nothrow_constructible<Node<int>>::value);
}


TEST(TestSNode, StringNodeDefaultCtorShouldDefaultInitialize)
{
  Node<std::string> stringNode;
  EXPECT_EQ(std::string{}, stringNode.data);
  EXPECT_EQ(nullptr, stringNode.next);
}


TEST(TestSNode, StringNodeDefaultCtorShouldBeNoExcept)
{
  EXPECT_TRUE(std::is_nothrow_constructible<Node<std::string>>::value);
}


} // anonymous namespace
