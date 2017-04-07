#pragma once

#include <initializer_list>
#include <ostream>
#include <set>
#include <string>
#include <sstream>
#include <stdexcept>
#include <type_traits>


namespace ospp {


template<typename T>
struct Node {
  T data;
  Node *next;

  Node() noexcept(std::is_nothrow_constructible<T>::value);
  Node(T &data, Node *next)
  noexcept(std::is_nothrow_copy_constructible<T>::value);
  Node(T &data) noexcept(std::is_nothrow_copy_constructible<T>::value);
};


template<typename T>
Node<T>::Node() noexcept(std::is_nothrow_constructible<T>::value)
  : data{}, next{nullptr}
{}


template<typename T>
Node<T>::Node(T &data, Node<T> *next)
  noexcept(std::is_nothrow_copy_constructible<T>::value)
  : data{data}, next{next}
{}


template<typename T>
Node<T>::Node(T &data) noexcept(std::is_nothrow_copy_constructible<T>::value)
  : data{data}
{}


template<typename TData>
std::ostream&
operator<<(std::ostream &os, const Node<TData> &node)
{
  return os << "Node(data=" << node.data << ", next=" << node.next << ")";
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


template<typename T>
void
removeDuplicates(Node<T> *node)
{
  std::set<T> found;
  auto prev = node;
  while (node) {
    auto it = found.insert(node->data);
    if (not it->second) {
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


template<typename T>
unsigned
length(Node<T> *node) noexcept
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

  if (k)
    throw std::out_of_range{};

  while (leading) {
    leading = leading->next;
    node = node->next;
  }
  return node->data;
}


template<typename TData>
void
removeNode(Node<TData> *node) noexcept
{
  if (not node)
    return;

  if (not node->next) {
    delete node;
    return;
  }

  auto tmp = node->next;
  node->data = tmp->data;
  node->next = tmp->next;
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


} // namespace ospp
