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
struct is_input_iter {
  using category = std::iterator_traits<Iter>::iterator_category;
  using true_or_false = std::is_same<category, std::input_iterator_tag>;
  using value = std::integral_constant<bool, true_or_false::value>;
};


} // namespace ospp

#endif /* _ITER_TRAITS_H */

