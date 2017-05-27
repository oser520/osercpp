#pragma once


#include <algorithm>
#include <deque>
#include <type_traits>
#include <utility>
#include "graph/ifringe.hh"


namespace ospp {


template<class T>
class FifoFringe: public IFringe<T>
{
  std::deque<T> fringe;
public:
  bool
  empty() const noexcept override;

  bool
  contains(const T &t) const noexcept override;

  void
  push(const T &t) override;

  void
  push(T &&t) override;

  T
  next() const noexcept(std::is_nothrow_copy_constructible<T>::value) override;

  void
  pop() noexcept(std::is_nothrow_destructible<T>::value) override;
};


template<typename T>
bool
FifoFringe<T>::empty() const noexcept
{
  return fringe.empty();
}


template<typename T>
bool
FifoFringe<T>::contains(const T &t) const noexcept
{
  auto last = fringe.cend();
  return std::find(fringe.cbegin(), last, t) != last;
}


template<typename T>
void
FifoFringe<T>::push(const T &t)
{
  fringe.push_back(t);
}


template<typename T>
void
FifoFringe<T>::push(T &&t)
{
  fringe.push_back(std::move(t));
}


template<typename T>
T
FifoFringe<T>::next() const
noexcept(std::is_nothrow_copy_constructible<T>::value)
{
  return fringe.front();
}


template<typename T>
void
FifoFringe<T>::pop()
noexcept(std::is_nothrow_destructible<T>::value)
{
  fringe.pop_front();
}


} // namespace ospp
