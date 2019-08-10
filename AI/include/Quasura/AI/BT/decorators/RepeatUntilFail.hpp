
/*
 * RepeaterUntilFail.hpp
 *
 * Created by Viacheslav Borisenko
 *
 * Copyright (c) 2018 spectrobyte http://spectrobyte.com
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 *
 */

#ifndef QUASURA_AI_BT_REPEATUNTILFAIL_HPP
#define QUASURA_AI_BT_REPEATUNTILFAIL_HPP

#include "Quasura/AI/Global.hpp"
#include "Quasura/AI/BT/Decorator.hpp"

AI_NAMESPACE_BEGIN

namespace bt {

class RepeatUntilFail final : public Decorator
{
public:

  Node::State Update(float dt) override;
};

}

AI_NAMESPACE_END

#endif //QUASURA_AI_BT_REPEATUNTILFAIL_HPP
