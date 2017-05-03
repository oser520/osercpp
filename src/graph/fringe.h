#pragma once


#include <algorithm>
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


template<typename T>
class Fringe<T, std::queue>
{
  std::queue<T> fringe;

public:
  bool empty() const noexcept;
  bool contains(const T &t) const noexcept;
  void push(const T &t);
  void push(T &&t);
  T next() const noexcept(std::is_nothrow_copy_constructible<T>::value);
  void pop() noexcept(std::is_nothrow_destructible<T>::value);
};


template<typename T>
bool
Fringe<T, std::queue>::empty() const noexcept
{
  return fringe.empty();
}


template<typename T>
bool
Fringe<T, std::queue>::contains(const T &t) const noexcept
{
  auto last = fringe.cend();
  return std::find(fringe.cbegin(), last, t) != last;
}


template<typename T>
void
Fringe<T, std::queue>::push(const T &t)
{
  fringe.push(t);
}


template<typename T>
void
Fringe<T, std::queue>::push(T &&t)
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
void
Fringe<T, std::queue>::pop() const
noexcept(std::is_nothrow_destructible<T>::value)
{
  fringe.pop();
}


} // namespace ospp
