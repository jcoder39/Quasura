/*
 * Component.hpp
 *
 * Created by Viacheslav Borisenko
 *
 * Copyright (c) 2018 spectrobyte http://spectrobyte.com
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 *
 */

#ifndef QUASURA_COMPONENT_HPP
#define QUASURA_COMPONENT_HPP

#include <memory>
#include <string>
#include <typeinfo>
#include "Global.hpp"
#include "Object.hpp"

ECS_NAMESPACE_BEGIN

class Component : public Object
{
public:
  Component();
  ~Component() override = 0;

  std::string GetType();

  void SetID(const std::string& id);
};

using ComponentPtr = std::shared_ptr<quasura::ecs::Component>;

ECS_NAMESPACE_END

#endif //QUASURA_COMPONENT_HPP
