/*
 * RepeatUntilFail.cpp
 *
 * Created by Viacheslav Borisenko
 *
 * Copyright (c) 2018 spectrobyte http://spectrobyte.com
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 *
 */

#include "Quasura/AI/BT/decorators/RepeatUntilFail.hpp"

AI_NAMESPACE_BEGIN

namespace bt {

Node::State RepeatUntilFail::Update(float dt)
{
  while(true) {
    auto state = _child->Tick(dt);

    if(state == State::Failure) {
      return State::Success;
    }
  }
}

}

AI_NAMESPACE_END