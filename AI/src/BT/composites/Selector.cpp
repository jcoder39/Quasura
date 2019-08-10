/*
 * Selector.cpp
 *
 * Created by Viacheslav Borisenko
 *
 * Copyright (c) 2018 spectrobyte http://spectrobyte.com
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 *
 */

#include "Quasura/AI/BT/composites/Selector.hpp"

AI_NAMESPACE_BEGIN

namespace bt {

void Selector::Before()
{
  _quantityFailure = 0;
}

Node::State Selector::Update(float dt)
{
  if(hasNoChildren()) {
    return State::Success;
  }

  while(true) {
    for(auto& child : _children) {
      auto state = child->Tick(dt);
      if(state != State::Failure) {
        return state;
      }
      _quantityFailure++;
    }
    if(_quantityFailure == _children.size()) {
      return State::Failure;
    }
  }
}

Selector::Selector() : _quantityFailure(0)
{}

}

AI_NAMESPACE_END