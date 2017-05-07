#pragma once


#include <algorithm>
#include <queue>
#include <stack>
#include <stdexcept>
#include <type_traits>
#include <utility>


namespace ospp {


template<typename T, typename TContainer = std::queue<T>>
class Fringe
{
  using size_type = typename TContainer::size_type;
  TContainer fringe;

public:
  bool empty() const noexcept;
  bool contains(const T &t) const noexcept;
  void push(const T &t);
  void push(T &&t);
  T next() const noexcept(std::is_nothrow_copy_constructible<T>::value);
  void pop() noexcept(std::is_nothrow_destructible<T>::value);
  size_type size() const noexcept;
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
Fringe<T, TContainer>::pop()
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
Fringe<T, TContainer>::push(T &&t)
{
  fringe.push(std::move(t));
}


template<typename T, typename TContainer>
T
Fringe<T, TContainer>::next() const
noexcept(std::is_nothrow_copy_constructible<T>::value)
{
  return fringe.front();
}


template<typename T, typename TContainer>
typename Fringe<T, TContainer>::size_type
Fringe<T, TContainer>::size() const noexcept
{
  return fringe.size();
}


} // namespace ospp
