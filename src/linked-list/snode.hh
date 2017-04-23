#pragma once

#include <cmath>
#include <initializer_list>
#include <ostream>
#include <set>
#include <string>
#include <sstream>
#include <stdexcept>
#include <type_traits>


namespace ospp {


template<typename TData>
struct Node {
  TData data;
  Node *next;

  Node() noexcept(std::is_nothrow_constructible<TData>::value);
  Node(TData &data, Node *next)
  noexcept(std::is_nothrow_copy_constructible<TData>::value);
  Node(TData &data) noexcept(std::is_nothrow_copy_constructible<TData>::value);
};


template<typename TData>
Node<TData>::Node() noexcept(std::is_nothrow_constructible<TData>::value)
  : data{}, next{nullptr}
{}


template<typename TData>
Node<TData>::Node(TData &data, Node<TData> *next)
  noexcept(std::is_nothrow_copy_constructible<TData>::value)
  : data{data}, next{next}
{}


template<typename TData>
Node<TData>::Node(TData &data)
  noexcept(std::is_nothrow_copy_constructible<TData>::value)
  : data{data}, next{nullptr}
{}


template<typename TData>
std::ostream&
operator<<(std::ostream &os, const Node<TData> &node)
{
  return os << "Node(data=" << node.data << ", next=" << node.next << ")";
}


template<typename TData>
void
removeDuplicates(Node<TData> *node)
{
  std::set<TData> found;
  auto prev = node;
  while (node) {
    auto iterBool = found.insert(node->data);
    if (not iterBool.second) {
      auto tmp = node;
      node = node->next;
      prev->next = node;
      delete tmp;
      continue;
    }
    prev = node;
    node = node->next;
  }
}


template<typename TData>
unsigned
length(Node<TData> *node) noexcept
{
  auto len = 0u;
  while (node) {
    ++len;
    node = node->next;
  }
  return len;
}


template<typename TData>
TData
getKthFromLast(Node<TData> *node, unsigned k)
{
  auto leading = node;
  while (leading and k) {
    --k;
    leading = leading->next;
  }

  if (k or not node)
    throw std::out_of_range("node list contains less than k+1 items");

  while (leading->next) {
    leading = leading->next;
    node = node->next;
  }
  return node->data;
}


template<typename TData>
void
removeNode(Node<TData> **node) noexcept
{
  if (not *node)
    return;

  if (not (*node)->next) {
    delete *node;
    *node = nullptr;
    return;
  }

  auto tmp = (*node)->next;
  (*node)->data = tmp->data;
  (*node)->next = tmp->next;
  delete tmp;
}


template<typename TData>
Node<TData>*
createNodeList(std::initializer_list<TData> dataList)
{
  Node<TData> *head{nullptr}, *next{nullptr};
  for (auto data : dataList)
  {
    if (not head) {
      try {
        head = new Node<TData>(data);
        next = head;
      } catch (...) {
        deleteNodeList(head);
        throw;
      }
    }
    else {
      try {
        next->next = new Node<TData>(data);
        next = next->next;
      } catch (...) {
        deleteNodeList(head);
        throw;
      }
    }
  }
  return head;
}


template<typename TData>
void
deleteNodeList(Node<TData> *node) noexcept
{
  Node<TData> *prev;
  while (node) {
    prev = node;
    node = node->next;
    delete prev;
  }
}


template<typename TData>
bool
areListsEqual(Node<TData> *node1, Node<TData> *node2) noexcept
{
  while (node1 and node2) {
    if (node1->data != node2->data)
      return false;
    node1 = node1->next;
    node2 = node2->next;
  }

  if (node1 or node2)
    return false;

  return true;
}


template<typename TData>
std::ostream&
listToStream(std::ostream &os, Node<TData> *node)
{
    os << "(";
    if (node) {
      os << node->data;
      node = node->next;
    }

    while (node) {
      os << ", " << node->data;
      node = node->next;
    }
    os << ")";

    return os;
}


template<typename TData>
std::string
listToString(Node<TData> *node)
{
  std::ostringstream os;
  listToStream(os, node);
  return os.str();
}


template<typename TData>
TData
sumList(Node<TData> *node)
{
  TData total{};
  while (node) {
    total += node->data;
    node = node->next;
  }
  return total;
}


template<typename TData>
typename std::enable_if<std::is_arithmetic<TData>::value, TData>::type
toNumberFromDigits(Node<TData> *node)
{
  TData number{};
  for (auto place = 0; node; ++place, node = node->next)
    number += node->data * static_cast<TData>(std::pow(10, place));
  return number;
}


template<typename TData>
TData
inline sumLists(Node<TData> *lhs, Node<TData> *rhs)
{
  return toNumberFromDigits(lhs) + toNumberFromDigits(rhs);
}


template<typename TData>
typename std::enable_if<std::is_arithmetic<TData>::value, TData>::type
toNumberFromDigitsReverse(Node<TData> *node)
{
  TData number{};
  auto len = static_cast<int>(length(node)) - 1;
  for (; len >= 0; --len, node = node->next)
    number += node->data * static_cast<TData>(std::pow(10, len));
  return number;
}


template<typename TData>
TData
inline sumListsReverse(Node<TData> *lhs, Node<TData> *rhs)
{
  return toNumberFromDigitsReverse(lhs) + toNumberFromDigitsReverse(rhs);
}


template<typename TData>
Node<TData>*
findNode(Node<TData> *nodeList, Node<TData> *node)
{
  if (not nodeList or not node)
    return nullptr;

  while (nodeList) {
    if (nodeList == node)
      return node;
    nodeList = nodeList->next;
  }

  return nullptr;
}


} // namespace ospp
