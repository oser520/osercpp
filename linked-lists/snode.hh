#pragma once

#include <set>
#include <type_traits>


template<typename T>
struct Node {
  T data{};
  Node *next{nullptr};

  Node(T &data, Node *next)
  noexcept(std::is_nothrow_copy_constructible<T>::value);
  Node(T &data) noexcept(std::is_nothrow_copy_constructible<T>::value);
  Node() noexcept(std::is_nothrow_constructible<T>::value) = default;
};


template<T>
Node<T>::Node(T &data, Node<T> *next)
  noexcept(std::is_nothrow_copy_constructible<T>::value)
  : data{data}, next{next}
{}


template<T>
Node<T>::Node(T &data) noexcept(std::is_nothrow_copy_constructible<T>::value)
  : data{data}
{}


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
