/*
 * Chaos.hpp
 *
 * Created by Viacheslav Borisenko
 *
 * Copyright (c) 2018 spectrobyte http://spectrobyte.com
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 *
 */

#ifndef QUASURA_CHAOS_HPP
#define QUASURA_CHAOS_HPP

#include <random>
#include <ctime>
#include "Quasura/common/Singleton.hpp"
#include "Quasura/common/Global.hpp"

COMMON_NAMESPACE_BEGIN

class Chaos : public Singleton<Chaos>
{
  friend class Singleton<Chaos>;
public:

  float GetRandom(float start, float end)
  {
    std::uniform_real_distribution<float> d(start, end);
    return d(_rd);
  }

  int GetRandom(int start, int end)
  {
    std::uniform_int_distribution<int> d(start, end);
    return d(_rd);
  }

  int Roll(int s)
  {
    return GetRandom(1, s);
  }

  bool YesNo(int seed = 2)
  {
    auto rand = Roll(seed);
    return rand % 2 == 0;
  }

private:
  Chaos() : _rng(time(nullptr)) {}

  std::random_device _rd;
  std::mt19937 _rng;
};

COMMON_NAMESPACE_END

#endif //QUASURA_CHAOS_HPP