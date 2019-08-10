/*
 * Object.hpp
 *
 * Created by Viacheslav Borisenko
 *
 * Copyright (c) 2018 spectrobyte http://spectrobyte.com
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 *
 */

#ifndef QUASURA_OBJECT_HPP
#define QUASURA_OBJECT_HPP

#include <string>
#include "Global.hpp"
#include "Quasura/common/StringGenerator.hpp"

ECS_NAMESPACE_BEGIN

class Object
{
public:
  Object();

  virtual ~Object() = 0;

  std::string GetID();

protected:
  std::string _id;
};

ECS_NAMESPACE_END

#endif //QUASURA_OBJECT_HPP
