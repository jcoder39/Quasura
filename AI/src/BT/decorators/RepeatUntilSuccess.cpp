/*
 * RepeatUntilSuccess.cpp
 *
 * Created by Viacheslav Borisenko
 *
 * Copyright (c) 2018 spectrobyte http://spectrobyte.com
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 *
 */

#include "Quasura/AI/BT/decorators/RepeatUntilSuccess.hpp"

AI_NAMESPACE_BEGIN

namespace bt {

Node::State RepeatUntilSuccess::Update(float dt)
{
  while(true) {
    auto state = _child->Tick(dt);

    if(state == State::Success) {
      return state;
    }
  }
}

}

AI_NAMESPACE_END