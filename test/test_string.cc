/**
 * @file test_string.cc
 * @author Omar A Serrano
 * @date 2017-04-05
 */

#include <string>

#include "gtest/gtest.h"
#include "string/string.hh"


namespace {


using namespace ospp;
using hasUniqueChar = hasUniqueCharacters<char>;


TEST(TestString, HasUniqueCharactersShouldReturnTrueIfCharactersAreUnique)
{
  EXPECT_TRUE(hasUniqueChar("01abcz"));
}


TEST(TestString, HasUniqueCharactersShouldReturnTrueIfOnlyOneChar)
{
  EXPECT_TRUE(hasUniqueChar("1"));
}


TEST(TestString, HasUniqueCharactersShouldReturnFalseIfNotUnique)
{
  EXPECT_FALSE(hasUniqueChar("00"));
  EXPECT_FALSE(hasUniqueChar("1abcda"));
}

} // anonymous namespace
