
/*
 * ecs_tests.cpp
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
#include <memory>
#include <string>
#include "Quasura/ECS/ECS.hpp"

USING_ECS_NAMESPACE
using namespace std;

TEST(ECS, create)
{
  ECSPtr ecs = make_shared<ECS>();
  ecs->Init();

  ASSERT_TRUE(true);
}