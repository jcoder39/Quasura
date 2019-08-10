/*
 * Decorator.cpp
 *
 * Created by Viacheslav Borisenko
 *
 * Copyright (c) 2018 spectrobyte http://spectrobyte.com
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 *
 */

#include "Quasura/AI/BT/Decorator.hpp"

AI_NAMESPACE_BEGIN

namespace bt {

void Decorator::SetChild(const NodePtr& child)
{
  _child = child;
}

bool Decorator::hasNoChild()
{
  return _child == nullptr;
}

}

AI_NAMESPACE_END