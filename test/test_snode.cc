/**
 * @file test_snode.cc
 * @author Omar A Serrano
 * @date 2017-04-06
 */

#include <sstream>
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


TEST(TestSNode, IntNodeOutputOpSouldWork)
{
  Node<int> intNode;
  std::ostringstream oss;
  oss << intNode;
  EXPECT_EQ("Node(data=0, next=0)", oss.str());
}


TEST(TestSNode, StringNodeDefaultCtorShouldDefaultInitialize)
{
  Node<std::string> stringNode;
  EXPECT_EQ(std::string{}, stringNode.data);
  EXPECT_EQ(nullptr, stringNode.next);
}


TEST(TestSNode, StringNodeDefaultCtorShouldBeExcept)
{
  EXPECT_FALSE(std::is_nothrow_constructible<Node<std::string>>::value);
}


TEST(TestSNode, CreateNodeListShouldCreateAOneNodeListCorrectly)
{
  auto nodeList = createNodeList({1});
  EXPECT_EQ(1, nodeList->data);
  EXPECT_EQ(nullptr, nodeList->next);
  deleteNodeList(nodeList);
}


TEST(TestSNode, CreateNodeListShouldCreateATwoNodeListCorrectly)
{
  auto nodeList = createNodeList({1, 2});
  EXPECT_EQ(1, nodeList->data);
  EXPECT_NE(nullptr, nodeList->next);

  auto node = nodeList->next;
  EXPECT_EQ(2, node->data);
  EXPECT_EQ(nullptr, node->next);
  deleteNodeList(nodeList);
}


TEST(TestSNode, CreateNodeListShouldCreateAThreeNodeListCorrectly)
{
  auto nodeList = createNodeList({1, 2, 3});
  EXPECT_EQ(1, nodeList->data);
  EXPECT_NE(nullptr, nodeList->next);

  auto node = nodeList->next;
  EXPECT_EQ(2, node->data);
  EXPECT_NE(nullptr, node->next);

  node = node->next;
  EXPECT_EQ(3, node->data);
  EXPECT_EQ(nullptr, node->next);

  deleteNodeList(nodeList);
}


TEST(TestSNode, ListToStringShouldWorkCorrectlyForOneNode)
{
  auto nodeList = createNodeList({1});
  EXPECT_EQ("(1)", listToString(nodeList));
  deleteNodeList(nodeList);
}


TEST(TestSNode, ListToStringShouldWorkCorrectlyForMoreThanOneNode)
{
  auto nodeList = createNodeList({1, 2});
  EXPECT_EQ("(1, 2)", listToString(nodeList));
  deleteNodeList(nodeList);

  nodeList = createNodeList({1, 2, 3});
  EXPECT_EQ("(1, 2, 3)", listToString(nodeList));
  deleteNodeList(nodeList);
}


TEST(TestSNode, LengthShouldReturnCorrectValueForAnEmptyNodeList)
{
  auto nodeList = createNodeList<int>({});
  EXPECT_EQ(0, length(nodeList));
  deleteNodeList(nodeList);
}


TEST(TestSNode, LengthShouldReturnCorrectValueForAOneNodeList)
{
  auto nodeList = createNodeList({1});
  EXPECT_EQ(1, length(nodeList));
  deleteNodeList(nodeList);
}


TEST(TestSNode, LengthShouldReturnCorrectValueForATwoNodeList)
{
  auto nodeList = createNodeList({1, 2});
  EXPECT_EQ(2, length(nodeList));
  deleteNodeList(nodeList);
}


TEST(TestSNode, LengthShouldReturnCorrectValueForAThreeNodeList)
{
  auto nodeList = createNodeList({1, 2, 3});
  EXPECT_EQ(3, length(nodeList));
  deleteNodeList(nodeList);
}


TEST(TestSNode, AreListsEqualShouldReturnTrueForTwoEmptyLists)
{
  EXPECT_TRUE(areListsEqual<int>(nullptr, nullptr));
}


TEST(TestSNode, AreListsEqualShouldReturnCorrectValueWhenListsOnlyHaveOneItem)
{
  auto nodeList1 = createNodeList({1});
  auto nodeList2 = createNodeList({1});
  EXPECT_TRUE(areListsEqual(nodeList1, nodeList2));

  nodeList1->data = 2;
  EXPECT_FALSE(areListsEqual(nodeList1, nodeList2));

  deleteNodeList(nodeList1);
  deleteNodeList(nodeList2);
}


TEST(TestSNode, AreListsEqualShouldReturnFalseWhenListsHaveDifferentLenghts)
{
  auto nodeList1 = createNodeList({1, 2, 3});
  auto nodeList2 = createNodeList({1, 2, 3, 4});
  EXPECT_FALSE(areListsEqual(nodeList1, nodeList2));

  deleteNodeList(nodeList1);
  deleteNodeList(nodeList2);
}


TEST(TestSNode,
     AreListsEqualShouldReturnCorrectValueForListsWithMoreThanOneItem)
{
  auto nodeList1 = createNodeList({1, 2, 3, 4});
  EXPECT_TRUE(areListsEqual(nodeList1, nodeList1));

  auto nodeList2 = createNodeList({1, 2, 5, 4});
  EXPECT_FALSE(areListsEqual(nodeList1, nodeList2));

  deleteNodeList(nodeList1);
  deleteNodeList(nodeList2);
}


TEST(TestSNode, RemoveDuplicatesShouldNotDoAnythingIfItemsAreUnique)
{
  auto nodeList1 = createNodeList({1, 2, 3, 4});
  auto nodeList2 = createNodeList({1, 2, 3, 4});
  removeDuplicates(nodeList1);
  EXPECT_TRUE(areListsEqual(nodeList1, nodeList2));

  deleteNodeList(nodeList1);
  deleteNodeList(nodeList2);
}


TEST(TestSNode, RemoveDuplicatesShouldRemoveASingleDuplicateItem)
{
  auto nodeList1 = createNodeList({1, 2, 2, 4});
  auto nodeList2 = createNodeList({1, 2, 4});
  removeDuplicates(nodeList1);
  EXPECT_TRUE(areListsEqual(nodeList1, nodeList2));

  deleteNodeList(nodeList1);
  deleteNodeList(nodeList2);
}


TEST(TestSNode, RemoveDuplicatesShouldRemoveMultipleDuplicateItems)
{
  auto nodeList1 = createNodeList({9, 1, 2, 1, 8, 2, 2, 4, 5, 6, 9, 8, 1, 4});
  auto nodeList2 = createNodeList({9, 1, 2, 8, 4, 5, 6});
  removeDuplicates(nodeList1);
  EXPECT_TRUE(areListsEqual(nodeList1, nodeList2));

  deleteNodeList(nodeList1);
  deleteNodeList(nodeList2);
}


TEST(TestSNode, GetKthFromLastShouldThrowIfKIsOutOfRange)
{
  ASSERT_ANY_THROW(getKthFromLast<int>(nullptr, 1));
  auto nodeList = createNodeList({1, 2, 3});
  ASSERT_ANY_THROW(getKthFromLast(nodeList, 4));
  deleteNodeList(nodeList);
}


} // anonymous namespace
