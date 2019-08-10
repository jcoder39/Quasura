/*
 * RandomSequence.cpp
 *
 * Created by Viacheslav Borisenko
 *
 * Copyright (c) 2018 spectrobyte http://spectrobyte.com
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 *
 */

#include "Quasura/AI/BT/composites/RandomSequence.hpp"

AI_NAMESPACE_BEGIN

namespace bt {

void RandomSequence::Before()
{
  _index = 0;
  _quantitySuccess = 0;
}

Node::State RandomSequence::Update(float dt)
{
  if(hasNoChildren()) {
    return State::Success;
  }

  int max = static_cast<int>(_children.size() - 1);

  while(true) {

    std::uniform_int_distribution<int> distribution(0, max);
    int randomIndex = distribution(_rd);

    auto& toExecute = _children.at(randomIndex);
    toExecute->Tick(dt);
    for(auto& child : _children) {
      auto state = child->GetState();
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

RandomSequence::RandomSequence() : _quantitySuccess(0), _index(0)
{}

}

AI_NAMESPACE_END