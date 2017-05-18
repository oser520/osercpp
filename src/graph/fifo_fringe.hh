#pragma once


#include <algorithm>
#include <type_traits>
#include <vector>
#include "graph/ifringe.hh"


namespace ospp {


template<typename T>
class FifoFringe: class IFring<T>
{
  std::vector<T> fringe;
public:
  bool empty() const noexcept override;
  bool contains(const T &t) const noexcept override;
  void push(const T &t) override;
  void push(T &&t) override;
  T next() const noexcept(std::is_nothrow_copy_constructible<T>::value) override;
  void pop() noexcept(std::is_nothrow_destructible<T>::value) override;
};


template<typename T>
bool
FifoFringe<T>::empty() const noexcept override
{
  return fringe.empty();
}


template<typename T>
bool
FifoFringe<T>::contains(const T &t) const noexcept override
{
  auto last = fringe.cend();
  return std::find(fringe.cbegin(), last, t) != last;
}


} // namespace ospp
