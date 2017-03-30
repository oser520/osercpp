/**
 * @file string.hh
 * @author Omar A Serrano
 * @date 2017-03-28
 */

#pragma once

#include <bitset>
#include <limits>
#include <string>
#include <unordered_map>

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

template<typename TChar>
bool
arePermutations(
  const std::basic_string<TChar> &lhs,
  const std::basic_string<TChar> &rhs)
{
  if (lhs.size() != rhs.size())
    return false;

  std::unordered_map<TChar, int> charMap;
  for (auto c : lhs)
    ++charMap[c];

  for (auto c : rhs) {
    auto val = --charMap[c];
    if (val < 0)
      return false;
  }

  for (auto values : charMap) {
    if (not values.second)
      return false;
  }

  return true;
}

} // namespace ospp
