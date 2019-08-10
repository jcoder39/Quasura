/*
 * Parallel.cpp
 *
 * Created by Viacheslav Borisenko
 *
 * Copyright (c) 2018 spectrobyte http://spectrobyte.com
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 *
 */

#include "Quasura/AI/BT/composites/Parallel.hpp"

AI_NAMESPACE_BEGIN

namespace bt {

void Parallel::Before()
{
  _quantitySuccess = 0;
  _quantityFailure = 0;
}

Node::State Parallel::Update(float dt)
{
  if(hasNoChildren()) {
    return State::Success;
  }

  while(true) {
    for(auto& child : _children) {
      auto state = child->Tick(dt);

      if(state == State::Success) {
        _quantitySuccess++;
      } else if(state == State::Failure) {
        _quantityFailure++;
      }
    }

    if(_quantitySuccess >= _minSuccess) {
      return State::Success;
    }
    if(_quantityFailure >= _minFailure) {
      return State::Failure;
    }
  }
}

Parallel::Parallel(int minSuccess, int minFailure) : _minSuccess(minSuccess), _minFailure(minFailure),
                                                     _quantityFailure(0),
                                                     _quantitySuccess(0)
{}

}

AI_NAMESPACE_END
