/*
 * Succeeder.cpp
 *
 * Created by Viacheslav Borisenko
 *
 * Copyright (c) 2018 spectrobyte http://spectrobyte.com
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 *
 */

#include "Quasura/AI/BT/decorators/Succeeder.hpp"

AI_NAMESPACE_BEGIN

namespace bt {

Node::State Succeeder::Update(float dt)
{
  _child->Tick(dt);
  return State::Success;
}

}

AI_NAMESPACE_END