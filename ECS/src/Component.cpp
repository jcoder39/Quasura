/*
 * Component.cpp
 *
 * Created by Viacheslav Borisenko
 *
 * Copyright (c) 2018 spectrobyte http://spectrobyte.com
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 *
 */

#include "Quasura/ECS/Component.hpp"

ECS_NAMESPACE_BEGIN

void Component::SetID(const std::string& entityID)
{
  _id = entityID;
}

std::string Component::GetType()
{
  return typeid(*this).name();
}

Component::Component() = default;

Component::~Component() = default;

ECS_NAMESPACE_END