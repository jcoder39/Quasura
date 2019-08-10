/*
 * Sequence.cpp
 *
 * Created by Viacheslav Borisenko
 *
 * Copyright (c) 2018 spectrobyte http://spectrobyte.com
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 *
 */

#include "Quasura/AI/BT/composites/Sequence.hpp"

AI_NAMESPACE_BEGIN

namespace bt {

void Sequence::Before()
{
  _quantitySuccess = 0;
}

Node::State Sequence::Update(float dt)
{
  if(hasNoChildren()) {
    return State::Success;
  }

  while(true) {
    for(auto& child : _children) {
      auto state = child->Tick(dt);
      if(state != State::Success) {
        return state;
      }
      _quantitySuccess++;
    }
    if(_quantitySuccess == _children.size()) {
      return State::Success;
    }
  }
}

Sequence::Sequence() : _quantitySuccess(0)
{}

}

AI_NAMESPACE_END