/*
 * Repeater.cpp
 *
 * Created by Viacheslav Borisenko
 *
 * Copyright (c) 2018 spectrobyte http://spectrobyte.com
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 *
 */

#include "Quasura/AI/BT/decorators/Repeater.hpp"

AI_NAMESPACE_BEGIN

namespace bt {

void Repeater::Before()
{
  _counter = 0;
}

Node::State Repeater::Update(float dt)
{
  while(true) {
    _counter++;

    auto state = _child->Tick(dt);

    if(_counter == _limit) {
      return State::Success;
    }

    return state;
  }
}

Repeater::Repeater(int limit) : _limit(limit), _counter(0)
{}

}

AI_NAMESPACE_END