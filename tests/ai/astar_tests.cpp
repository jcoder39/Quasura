
/*
 * astar_tests.cpp
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
#include "Quasura/AI/astar/Layer.hpp"
#include "Quasura/common/Logger.hpp"
#include "Quasura/math/Vector2.hpp"
#include "Quasura/math/Rect.hpp"
#include "Quasura/math/Mathematician.hpp"

USING_MATH_NAMESPACE
using namespace quasura::ai::astar;

TEST(AStar, init)
{
  Rect<int> rect(0, 0, 16, 16);
  Layer layout("1", rect);
  layout.Init();

  clock_t begin = clock();

  Rect<int> areaRect(4, 3, 3, 3);
  layout.SetArea(Area(areaRect, 5));

  Vector2<int> from(0, 9);
  Vector2<int> to(8, 1);

  auto path = layout.BuildPath(from, to, {5});

  clock_t end = clock();
  double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
  LOG(elapsed_secs);

  ASSERT_TRUE(path._status == Path::OK);
}