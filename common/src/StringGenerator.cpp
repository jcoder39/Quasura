/*
 * StringGenerator.cpp
 *
 * Created by Viacheslav Borisenko
 *
 * Copyright (c) 2018 spectrobyte http://spectrobyte.com
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 *
 */

#include "Quasura/common/StringGenerator.hpp"

COMMON_NAMESPACE_BEGIN

std::string StringGenerator::Create(unsigned int length)
{
  std::string result;
  for(unsigned int i = 0; i < length; i++){
    std::uniform_int_distribution<int> uni(0, 53);
    auto rand = uni(_rng);
    result += alpha.at(rand);
  }
  return result;
}

StringGenerator::StringGenerator() : _rng(time(nullptr)) {}

COMMON_NAMESPACE_END