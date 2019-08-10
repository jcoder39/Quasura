/*
 * Node.hpp
 *
 * Created by Viacheslav Borisenko
 *
 * Copyright (c) 2018 spectrobyte http://spectrobyte.com
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 *
 */

#ifndef QUASURA_AI_BT_NODE_HPP
#define QUASURA_AI_BT_NODE_HPP

#include <vector>
#include <memory>
#include "Quasura/AI/Global.hpp"

AI_NAMESPACE_BEGIN

namespace bt {

class Node
{
public:
  enum class State
  {
    Success,
    Failure,
    Error,
    InProgress
  };

  Node() : _state(State::Error)
  {};

  virtual ~Node() = default;

  virtual void Before()
  {}

  virtual void After()
  {}

  virtual State Update(float dt) = 0;

  State Tick(float dt)
  {
    Before();

    _state = Update(dt);

    After();

    return _state;
  }

  State GetState()
  {
    return _state;
  }

protected:
  State _state;
};

using NodePtr = std::shared_ptr<Node>;

}

AI_NAMESPACE_END

#endif //QUASURA_AI_BT_NODE_HPP
