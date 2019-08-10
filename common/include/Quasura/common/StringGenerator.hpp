/*
 * StringGenerator.hpp
 *
 * Created by Viacheslav Borisenko
 *
 * Copyright (c) 2018 spectrobyte http://spectrobyte.com
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 *
 */

#ifndef QUASURA_STRINGGENERATOR_HPP
#define QUASURA_STRINGGENERATOR_HPP

#include <random>
#include <ctime>
#include "Global.hpp"
#include "Singleton.hpp"

COMMON_NAMESPACE_BEGIN

class StringGenerator : public Singleton<StringGenerator>
{
  friend class Singleton<StringGenerator>;
public:
  const std::string alpha = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQR1234567890";

  std::string Create(unsigned int length);

private:
  StringGenerator();

  std::random_device _rd;
  std::mt19937 _rng;
};

COMMON_NAMESPACE_END

#endif //QUASURA_STRINGGENERATOR_HPP
