#pragma once


#include <type_traits>


namespace ospp {


template<typename T, typename TContainer>
class Fringe
{
  TContainer<T> fringe;

public:
  bool empty() const noexcept;
  bool contains(const T &t) const noexcept;
  void push(const T &t);
  T next() const noexcept(std::is_nothrow_copy_constructible<T>::value);
  void pop() noexcept(std::is_nothrow_destructible<T>::value);
};


} // namespace ospp
