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
  ASSERT_ANY_THROW(getKthFromLast<int>(nullptr, 0));
  ASSERT_ANY_THROW(getKthFromLast<int>(nullptr, 1));
  auto nodeList = createNodeList({1, 2, 3});
  ASSERT_ANY_THROW(getKthFromLast(nodeList, 4));
  deleteNodeList(nodeList);
}


TEST(TestSNode, GetKthFromLastShouldReturnCorrectValueForKEqualToZero)
{
  auto nodeList = createNodeList({9});
  EXPECT_EQ(9, getKthFromLast(nodeList, 0));
  deleteNodeList(nodeList);

  nodeList = createNodeList({9, 100});
  EXPECT_EQ(100, getKthFromLast(nodeList, 0));
  deleteNodeList(nodeList);

  nodeList = createNodeList({9, 1, 2, 1, 8, 2, 2, 4, 5, 6, 9, 8, 1, 4});
  EXPECT_EQ(4, getKthFromLast(nodeList, 0));
  deleteNodeList(nodeList);
}


TEST(TestSNode, GetKthFromLastShouldReturnFirstValueForKEqualToLengthMinusOne)
{
  auto nodeList = createNodeList({9});
  auto len = length(nodeList) - 1;
  EXPECT_EQ(9, getKthFromLast(nodeList, len));
  deleteNodeList(nodeList);

  nodeList = createNodeList({9, 100});
  len = length(nodeList) - 1;
  EXPECT_EQ(9, getKthFromLast(nodeList, len));
  deleteNodeList(nodeList);

  nodeList = createNodeList({9, 1, 2, 1, 8, 2, 2, 4, 5, 6, 9, 8, 1, 4});
  len = length(nodeList) - 1;
  EXPECT_EQ(9, getKthFromLast(nodeList, len));
  deleteNodeList(nodeList);
}


TEST(TestSNode, GetKthFromLastShouldReturnCorrectValue)
{
  auto nodeList = createNodeList({9, 1, 2, 1, 8, 2, 2, 4, 5, 6, 9, 8, 1, 4});
  EXPECT_EQ(1, getKthFromLast(nodeList, 1));
  EXPECT_EQ(8, getKthFromLast(nodeList, 2));
  EXPECT_EQ(5, getKthFromLast(nodeList, 5));
  EXPECT_EQ(2, getKthFromLast(nodeList, 8));
  deleteNodeList(nodeList);
}


TEST(TestSNode, RemoveNodeShouldRemoveTheFirstNodeCorrectlyIfListOnlyHasOneNode)
{
  auto nodeList = createNodeList({1});
  removeNode(&nodeList);
  EXPECT_EQ("()", listToString(nodeList));
  deleteNodeList(nodeList);
}


TEST(TestSNode, RemoveNodeShouldRemoveTheFirstNodeCorrectlyIfListHasMoreNodes)
{
  auto nodeList = createNodeList({1, 2});
  removeNode(&nodeList);
  EXPECT_EQ("(2)", listToString(nodeList));
  deleteNodeList(nodeList);
}


TEST(TestSNode, RemoveNodeShouldRemoveANodeCorrectly)
{
  auto nodeList = createNodeList({1, 2, 3});
  removeNode(&nodeList->next);
  EXPECT_EQ("(1, 3)", listToString(nodeList));
  deleteNodeList(nodeList);
}


TEST(TestSNode, SumListShouldReturnDefaultCtorValueForEmptyList)
{
  Node<int> *intNode = nullptr;
  EXPECT_EQ(0, sumList(intNode));

  Node<std::string> *strNode = nullptr;
  EXPECT_EQ(std::string{}, sumList(strNode));
}


TEST(TestSNode, SumListShouldReturnCorrectValueForMultiNodeLists)
{
  auto intNodeList = createNodeList({1u, 20u, 33u});
  EXPECT_EQ(54u, sumList(intNodeList));
  deleteNodeList(intNodeList);

  auto strNodeList = createNodeList<std::string>({"how", "are", "you"});
  EXPECT_EQ("howareyou", sumList(strNodeList));
  deleteNodeList(strNodeList);
}


TEST(TestSNode, ToNumberFromDigitsShouldReturnCorrectValueForNullList)
{
  Node<int> *nodeList{nullptr};
  EXPECT_EQ(0, toNumberFromDigits(nodeList));
}


TEST(TestSNode, ToNumberFromDigitsShouldReturnCorrectValueForSingleNode)
{
  auto nodeList = createNodeList({5});
  EXPECT_EQ(5, toNumberFromDigits(nodeList));
  deleteNodeList(nodeList);
}


TEST(TestSNode, ToNumberFromDigitsShouldReturnCorrectValueForMultiNodeList)
{
  auto nodeList = createNodeList({5, 7, 9});
  EXPECT_EQ(975, toNumberFromDigits(nodeList));
  deleteNodeList(nodeList);
}


TEST(TestSNode, SumListsShouldReturnCorrectValueForEmptyLists)
{
  Node<int> *nodeList{nullptr};
  EXPECT_EQ(0, sumLists(nodeList, nodeList));
}


TEST(TestSNode, SumListsShouldReturnCorrectValueNonEmptyLists)
{
  auto nodeList1 = createNodeList({1, 1, 1});
  auto nodeList2 = createNodeList({2, 3, 4});

  EXPECT_EQ(543, sumLists(nodeList1, nodeList2));

  deleteNodeList(nodeList1);
  deleteNodeList(nodeList2);
}


TEST(TestSNode, ToNumberFromDigitsReverseShouldReturnCorrectValueForNullList)
{
  EXPECT_EQ(0, toNumberFromDigitsReverse<int>(nullptr));
}


TEST(TestSNode, ToNumberFromDigitsReverseShouldReturnCorrectValueForSingleNode)
{
  auto nodeList = createNodeList({5});
  EXPECT_EQ(5, toNumberFromDigitsReverse(nodeList));
  deleteNodeList(nodeList);
}


TEST(TestSNode,
     ToNumberFromDigitsReverseShouldReturnCorrectValueForMultiNodeList)
{
  auto nodeList = createNodeList({5, 7, 9});
  EXPECT_EQ(579, toNumberFromDigitsReverse(nodeList));
  deleteNodeList(nodeList);
}


TEST(TestSNode, SumListsReverseShouldReturnCorrectValueForEmptyLists)
{
  EXPECT_EQ(0, sumListsReverse<int>(nullptr, nullptr));
}


TEST(TestSNode, SumListsReverseShouldReturnCorrectValueNonEmptyLists)
{
  auto nodeList1 = createNodeList({1, 1, 1});
  auto nodeList2 = createNodeList({2, 3, 4});

  EXPECT_EQ(345, sumListsReverse(nodeList1, nodeList2));

  deleteNodeList(nodeList1);
  deleteNodeList(nodeList2);
}


TEST(TestSNode, FindNodeReturnsNullPointerIfNodeListIsNull)
{
  Node<int> *nodeList = nullptr;
  auto node = createNodeList({1});

  EXPECT_EQ(nullptr, findNode(nodeList, node));

  deleteNodeList(node);
}


TEST(TestSNode, FindNodeReturnsNullPointerIfNodeIsNull)
{
  Node<int> *node = nullptr;
  auto nodeList = createNodeList({1});

  EXPECT_EQ(nullptr, findNode(nodeList, node));

  deleteNodeList(nodeList);
}


TEST(TestSNode, FindNodeReturnsNullPointerIfNodeIsNotFound)
{
  auto node = createNodeList({0});
  auto nodeList = createNodeList({0, 1, 2});

  EXPECT_EQ(nullptr, findNode(nodeList, node));

  deleteNodeList(nodeList);
  deleteNodeList(node);
}


TEST(TestSNode, FindNodeReturnsTheCorrectPointerIfItFindsTheNode)
{
  auto nodeList = createNodeList({0, 1, 2});
  EXPECT_EQ(nodeList->next->next, findNode(nodeList, nodeList->next->next));
  deleteNodeList(nodeList);
}


TEST(TestSNode, FindCommonNodeReturnsNullIfLeftHandSideIsNull)
{
  Node<int> *leftNodeList{nullptr};
  auto rightNodeList = createNodeList({0, 1, 2});
  EXPECT_EQ(nullptr, findCommonNode(leftNodeList, rightNodeList));
  deleteNodeList(rightNodeList);
}


TEST(TestSNode, FindCommonNodeReturnsNullIfRightHandSideIsNull)
{
  Node<int> *rightNodeList{nullptr};
  auto leftNodeList = createNodeList({0, 1, 2});
  EXPECT_EQ(nullptr, findCommonNode(leftNodeList, rightNodeList));
  deleteNodeList(leftNodeList);
}


TEST(TestSNode, FindCommonNodeReturnsCorrectNode)
{
  auto leftNodeList = createNodeList({0, 1});
  auto rightNodeList = createNodeList({3, 5});
  leftNodeList->next->next = rightNodeList;
  auto node = findCommonNode(leftNodeList, rightNodeList);
  EXPECT_EQ(rightNodeList, node);
  EXPECT_EQ(node->data, 3);
  leftNodeList->next->next = nullptr;
  deleteNodeList(leftNodeList);
  deleteNodeList(rightNodeList);
}


TEST(TestSNode, DetectLoopShouldReturnNullPtrIfNodeIsNull)
{
  EXPECT_EQ(nullptr, detectLoop<int>(nullptr));
}


} // anonymous namespace
