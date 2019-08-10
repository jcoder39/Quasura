/*
 * BT.cpp
 *
 * Created by Viacheslav Borisenko
 *
 * Copyright (c) 2018 spectrobyte http://spectrobyte.com
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 *
 */

#include "Quasura/AI/BT/BT.hpp"

AI_NAMESPACE_BEGIN

namespace bt {

Node::State BT::Tick(float dt)
{
  if(_root == nullptr) {
    return Node::State::Success;
  }
  return _root->Tick(dt);
}

void BT::SetRoot(const NodePtr& root)
{
  _root = root;
}

BT::BT() : _root(nullptr)
{}

}

AI_NAMESPACE_END