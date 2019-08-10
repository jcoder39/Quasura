/*
 * Composite.cpp
 *
 * Created by Viacheslav Borisenko
 *
 * Copyright (c) 2018 spectrobyte http://spectrobyte.com
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 *
 */

#include "Quasura/AI/BT/Composite.hpp"

AI_NAMESPACE_BEGIN

namespace bt {

void Composite::AddChildren(const NodePtr& child)
{
  _children.push_back(child);
}

bool Composite::hasNoChildren()
{
  return _children.empty();
}

}

AI_NAMESPACE_END
