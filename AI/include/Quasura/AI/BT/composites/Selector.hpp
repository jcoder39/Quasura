
/*
 * Selector.hpp
 *
 * Created by Viacheslav Borisenko
 *
 * Copyright (c) 2018 spectrobyte http://spectrobyte.com
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 *
 */

#ifndef QUASURA_AI_BT_SELECTOR_HPP
#define QUASURA_AI_BT_SELECTOR_HPP

#include "Quasura/AI/Global.hpp"
#include "Quasura/AI/BT/Composite.hpp"

AI_NAMESPACE_BEGIN

namespace bt {

class Selector final : public Composite
{
public:
  Selector();

  void Before() override;

  Node::State Update(float dt) override;

private:
  int _quantityFailure;
};

}

AI_NAMESPACE_END

#endif //QUASURA_AI_BT_SELECTOR_HPP
