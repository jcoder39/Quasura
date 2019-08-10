
/*
 * Composite.hpp
 *
 * Created by Viacheslav Borisenko
 *
 * Copyright (c) 2018 spectrobyte http://spectrobyte.com
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 *
 */

#ifndef QUASURA_AI_BT_COMPOSITE_HPP
#define QUASURA_AI_BT_COMPOSITE_HPP

#include <vector>
#include "Quasura/AI/Global.hpp"
#include "Node.hpp"

AI_NAMESPACE_BEGIN

namespace bt {

class Composite : public Node
{
public:
  void AddChildren(const NodePtr& child);

  bool hasNoChildren();

protected:
  std::vector<NodePtr> _children;
};

}

AI_NAMESPACE_END

#endif //QUASURA_AI_BT_COMPOSITE_HPP
