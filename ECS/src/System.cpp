/*
 * System.cpp
 *
 * Created by Viacheslav Borisenko
 *
 * Copyright (c) 2018 spectrobyte http://spectrobyte.com
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 *
 */

#include "Quasura/ECS/System.hpp"

ECS_NAMESPACE_BEGIN

int System::GetPriority()
{
  return _priority;
}

void System::setComponentContainer(const ComponentContainerPtr& container)
{
  _componentContainer = container;
}

System::System(int priority) : _priority(priority) {}

System::~System() = default;

ECS_NAMESPACE_END