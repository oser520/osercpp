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


TEST(TestString, HasUniqueCharactersShouldReturnTrueIfCharactersAreUnique)
{
  EXPECT_TRUE(hasUniqueCharacters<char>("01abcz"));
}


TEST(TestString, HasUniqueCharactersShouldReturnTrueIfOnlyOneChar)
{
  EXPECT_TRUE(hasUniqueCharacters<char>("1"));
}


TEST(TestString, HasUniqueCharactersShouldReturnFalseIfNotUnique)
{
  EXPECT_FALSE(hasUniqueCharacters<char>("00"));
  EXPECT_FALSE(hasUniqueCharacters<char>("1abcda"));
}

} // anonymous namespace
