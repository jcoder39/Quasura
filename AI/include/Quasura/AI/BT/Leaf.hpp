/*
 * Leaf.hpp
 *
 * Created by Viacheslav Borisenko
 *
 * Copyright (c) 2018 spectrobyte http://spectrobyte.com
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 *
 */

#ifndef QUASURA_AI_BT_LEAF_HPP
#define QUASURA_AI_BT_LEAF_HPP

#include "Quasura/AI/Global.hpp"
#include "Node.hpp"

AI_NAMESPACE_BEGIN

namespace bt {

class Leaf : public Node
{
public:
  Node::State Update(float dt) override = 0;
};

}

AI_NAMESPACE_END

#endif //QUASURA_AI_BT_LEAF_HPP
