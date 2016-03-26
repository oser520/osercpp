/**
 * @file iter_traits.hh
 * @author Omar A Serrano
 * @date 2016-03-06
 *
 * @description Implement logic to be able to determine characteristics
 *  of iterators.
 */
#ifndef _ITER_TRAITS_H
#define _ITER_TRAITS_H

#include <iterator>
#include <type_traits>

namespace ospp {

/**
 * Determines at compile time if an iterator carries the input_iterator_tag.
 */
template<typename Iter>
struct is_input_iter
{
  using category = typename std::iterator_traits<Iter>::iterator_category;
  static const bool
  value = std::is_base_of<std::input_iterator_tag, category>::value;
};

/**
 * Determines at compile time if an iterator carries the forward_iterator_tag.
 */
template<typename Iter>
struct is_forward_iter
{
  using category = typename std::iterator_traits<Iter>::iterator_category;
  static const bool
  value = std::is_base_of<std::forward_iterator_tag, category>::value;
};

/**
 * Determines at compile time if an iterator carries the bidirectional_iterator_tag.
 */
template<typename Iter>
struct is_bidirectional_iter
{
  using category = typename std::iterator_traits<Iter>::iterator_category;
  static const bool
  value = std::is_base_of<std::bidirectional_iterator_tag, category>::value;
};

/**
 * Determines at compile time if an iterator carries the random_iterator_tag.
 */
template<typename Iter>
struct is_random_iter
{
  using category = typename std::iterator_traits<Iter>::iterator_category;
  static const bool
  value = std::is_base_of<std::random_access_iterator_tag, category>::value;
};

/**
 * Determines at compile time if an iterator carries the output_iterator_tag.
 */
template<typename Iter>
struct is_output_iter
{
  using category = typename std::iterator_traits<Iter>::iterator_category;
  static const bool
  value = std::is_base_of<std::output_iterator_tag, category>::value;
};

} // namespace ospp

#endif /* _ITER_TRAITS_H */
