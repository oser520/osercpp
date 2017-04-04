#pragma once

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
