#pragma once


#include <type_traits>


namespace ospp {


template<class T>
class IFringe
{
public:
  virtual ~IFringe() = default;

  virtual bool
  empty() const noexcept = 0;

  virtual bool
  contains(const T &t) const noexcept = 0;

  virtual void
  push(const T &t) = 0;

  virtual void
  push(T &&t) = 0;

  virtual T
  next() const noexcept(std::is_nothrow_copy_constructible<T>::value) = 0;

  virtual void
  pop() noexcept(std::is_nothrow_destructible<T>::value) = 0;
};


} // namespace ospp
