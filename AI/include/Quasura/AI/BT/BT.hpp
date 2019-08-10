
/*
 * BT.hpp
 *
 * Created by Viacheslav Borisenko
 *
 * Copyright (c) 2018 spectrobyte http://spectrobyte.com
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 *
 */

#ifndef QUASURA_AI_BT_BT_HPP
#define QUASURA_AI_BT_BT_HPP

#include <memory>
#include "Quasura/AI/Global.hpp"
#include "Node.hpp"

AI_NAMESPACE_BEGIN

namespace bt {

class BT
{
public:
  BT();

  Node::State Tick(float dt);

  void SetRoot(const NodePtr& root);

private:
  NodePtr _root;
};

using BTPtr = std::shared_ptr<BT>;

}

AI_NAMESPACE_END

#endif //QUASURA_AI_BT_BT_HPP
