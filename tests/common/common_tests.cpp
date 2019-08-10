/*
 * common_tests.cpp
 *
 * Created by Viacheslav Borisenko
 *
 * Copyright (c) 2018 spectrobyte http://spectrobyte.com
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 *
 */

#define TESTING

#include <gtest/gtest.h>
#include <string>
#include "Quasura/common/StringGenerator.hpp"

USING_COMMON_NAMESPACE

TEST(StringGenerator, Create)
{
  auto str = StringGenerator::Instance()->Create(10);

  ASSERT_EQ(10, str.size());
}