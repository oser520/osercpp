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


TEST(TestString, ArePermuationsShouldReturnTrue)
{
  EXPECT_TRUE(arePermutations<char>("12345", "35214"));
  EXPECT_TRUE(arePermutations<char>("omarserrano", "resoranmaro"));
}


TEST(TestString, ArePermuationsShouldReturnFalse)
{
  EXPECT_FALSE(arePermutations<char>("123457", "35214"));
  EXPECT_FALSE(arePermutations<char>("omarsrrano", "resoranmaro"));
}


TEST(TestString, EncodeSpacesShouldEncodeSpaceCorrectly)
{
  std::string value{"hello there"};
  encodeSpaces(value);
  EXPECT_EQ("hello%20there", value);
}


TEST(TestString, EncodeSpacesShouldNotDoAnythingIfNoSpaces)
{
  std::string value{"omar"};
  encodeSpaces(value);
  EXPECT_EQ("omar", value);
}


TEST(TestString, EncodeSpacesShouldEncodeMultipleSpacesCorrectly)
{
  std::string value{"1 22 333 let's sing"};
  encodeSpaces(value);
  EXPECT_EQ("1%2022%20333%20let's%20sing", value);
}

} // anonymous namespace
