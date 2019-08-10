
/*
 * Parallel.hpp
 *
 * Created by Viacheslav Borisenko
 *
 * Copyright (c) 2018 spectrobyte http://spectrobyte.com
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 *
 */

#ifndef QUASURA_AI_BT_PARALLEL_HPP
#define QUASURA_BT_PARALLEL_HPP

#include "Quasura/AI/Global.hpp"
#include "Quasura/AI/BT/Composite.hpp"

AI_NAMESPACE_BEGIN

namespace bt {

class Parallel final : public Composite
{
public:
  Parallel(int minSuccess, int minFailure);

  void Before() override;

  Node::State Update(float dt) override;

private:
  int _minSuccess;
  int _minFailure;
  int _quantitySuccess;
  int _quantityFailure;
};

}

AI_NAMESPACE_END

#endif //QUASURA_BT_PARALLEL_HPP
