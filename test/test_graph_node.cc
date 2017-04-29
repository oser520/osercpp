/**
 * @file test_graph_node.cc
 * @author Omar A Serrano
 * @date 2017-04-28
 */

#include "gtest/gtest.h"
#include "graph/graph_node.hh"


using namespace ospp;


namespace {


TEST(TestGraphNode, DefaultCtorShouldInitializeIntDataMemberToZero)
{
  GraphNode<int> intNode;
  EXPECT_EQ(0, intNode.data);
  EXPECT_EQ(0, intNode.neighbors.size());
}


} // anonymous namespace
