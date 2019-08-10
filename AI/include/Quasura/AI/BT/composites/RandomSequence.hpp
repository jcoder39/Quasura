
/*
 * RandomSequence.hpp
 *
 * Created by Viacheslav Borisenko
 *
 * Copyright (c) 2018 spectrobyte http://spectrobyte.com
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 *
 */

#ifndef QUASURA_AI_BT_RANDOMSEQUENCE_HPP
#define QUASURA_AI_BT_RANDOMSEQUENCE_HPP

#include <random>
#include "Quasura/AI/Global.hpp"
#include "Quasura/AI/BT/Composite.hpp"

AI_NAMESPACE_BEGIN

namespace bt {

class RandomSequence final : public Composite
{
public:
  RandomSequence();

  void Before() override;

  Node::State Update(float dt) override;

private:
  std::random_device _rd;
  int _index;
  int _quantitySuccess;
};

}

AI_NAMESPACE_END

#endif //QUASURA_AI_BT_RANDOMSEQUENCE_HPP
