/**
 * @file string.hh
 * @author Omar A Serrano
 * @date 2017-03-28
 */

#pragma once

#include <bitset>
#include <limits>
#include <string>

namespace ospp {

template<typename TChar>
bool
hasUniqueCharacters(const std::basic_string<TChar> &value)
{
  std::bitset<std::numeric_limits<TChar>::max()> charSet;
  for (const auto c : value) {
    if (charSet.test(value))
      return false;
    charSet.set(value);
  }
  return true;
}

} // namespace ospp
