
/*
 * vector2_tests.cpp
 * 
 * Created by Viacheslav Borisenko
 * 
 * Copyright (c) 2019 spectrobyte http://spectrobyte.com
 * 
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 *
 */

#define TESTING

#include <gtest/gtest.h>
#include <string>
#include "Quasura/math/Vector2.hpp"

USING_MATH_NAMESPACE
using namespace std;

TEST(Vector2, constructor)
{
  Vector2<float> vec;

  ASSERT_EQ(0.0f, vec._x);
  ASSERT_EQ(0.0f, vec._y);

  Vector2<float> vec1(1.0f, 2.0f);

  ASSERT_EQ(1.0f, vec1._x);
  ASSERT_EQ(2.0f, vec1._y);
}

TEST(Vector2, copy_constructor)
{
  Vector2<float> vec(1.0f, 2.0f);
  Vector2<float> vec1(vec);

  ASSERT_EQ(1.0f, vec1._x);
  ASSERT_EQ(2.0f, vec1._y);
}