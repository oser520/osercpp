#pragma once


#include <algorithm>
#include <type_traits>
#include <utility>
#include <vector>
#include "graph/ifringe.hh"


namespace ospp {


template<class T>
class LifoFringe: public IFringe<T>
{
  std::vector<T> fringe;
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
LifoFringe<T>::empty() const noexcept
{
  return fringe.empty();
}


template<typename T>
bool
LifoFringe<T>::contains(const T &t) const noexcept
{
  auto last = fringe.cend();
  return std::find(fringe.cbegin(), last, t) != last;
}


template<typename T>
void
LifoFringe<T>::push(const T &t)
{
  fringe.push_back(t);
}


template<typename T>
void
LifoFringe<T>::push(T &&t)
{
  fringe.push_back(std::move(t));
}


template<typename T>
T
LifoFringe<T>::next() const
noexcept(std::is_nothrow_copy_constructible<T>::value)
{
  return fringe.back();
}


template<typename T>
void
LifoFringe<T>::pop()
noexcept(std::is_nothrow_destructible<T>::value)
{
  fringe.pop_back();
}


} // namespace ospp
