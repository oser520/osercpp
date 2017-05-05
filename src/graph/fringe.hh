#pragma once


#include <algorithm>
#include <queue>
#include <stack>
#include <type_traits>
#include <utility>


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


template<typename T, typename TContainer>
bool
Fringe<T, TContainer>::empty() const noexcept
{
  return fringe.empty();
}


template<typename T, typename TContainer>
bool
Fringe<T, TContainer>::contains(const T &t) const noexcept
{
  auto last = fringe.cend();
  return std::find(fringe.cbegin(), last, t) != last;
}


template<typename T, typename TContainer>
void
Fringe<T, TContainer>::pop() const
noexcept(std::is_nothrow_destructible<T>::value)
{
  fringe.pop();
}


template<typename T, typename TContainer>
void
Fringe<T, TContainer>::push(const T &t)
{
  fringe.push(t);
}


template<typename T, typename TContainer>
void
Fringe<T, TContainerstd>::push(T &&t)
{
  fringe.push(std::move(t));
}


template<typename T>
T
Fringe<T, std::queue>::next() const
noexcept(std::is_nothrow_copy_constructible<T>::value)
{
  return fringe.front();
}


template<typename T>
T
Fringe<T, std::stack>::next() const
noexcept(std::is_nothrow_copy_constructible<T>::value)
{
  return fringe.top();
}


} // namespace ospp
