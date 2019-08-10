/*
 * Object.cpp
 *
 * Created by Viacheslav Borisenko
 *
 * Copyright (c) 2018 spectrobyte http://spectrobyte.com
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 *
 */

#include "Quasura/ECS/Object.hpp"

ECS_NAMESPACE_BEGIN

std::string Object::GetID()
{
  return _id;
}

Object::Object()
{
  _id = quasura::common::StringGenerator::Instance()->Create(20);
}

Object::~Object() = default;

ECS_NAMESPACE_END