#pragma once


#include <type_traits>


namespace ospp {


template<typename T>
class IFringe
{
public:
  virtual ~IFringe() = default;

  virtual bool
  empty() const noexcept;

  virtual bool
  contains(const T &t) const noexcept;

  virtual void
  push(const T &t);

  virtual void
  push(T &&t);

  virtual T
  next() const noexcept(std::is_nothrow_copy_constructible<T>::value);

  virtual void
  pop() noexcept(std::is_nothrow_destructible<T>::value);
};


} // namespace ospp
