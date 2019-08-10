/*
 * AI.hpp
 *
 * Created by Viacheslav Borisenko
 *
 * Copyright (c) 2018 spectrobyte http://spectrobyte.com
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 *
 */

#ifndef QUASURA_AI_HPP
#define QUASURA_AI_HPP

// Behaviour Tree
#include "Quasura/AI/BT/BT.hpp"
#include "Quasura/AI/BT/Composite.hpp"
#include "Quasura/AI/BT/Decorator.hpp"
#include "Quasura/AI/BT/Leaf.hpp"
#include "Quasura/AI/BT/Node.hpp"
#include "Quasura/AI/BT/composites/Parallel.hpp"
#include "Quasura/AI/BT/composites/RandomSequence.hpp"
#include "Quasura/AI/BT/composites/Selector.hpp"
#include "Quasura/AI/BT/composites/Sequence.hpp"
#include "Quasura/AI/BT/decorators/Inverter.hpp"
#include "Quasura/AI/BT/decorators/Repeater.hpp"
#include "Quasura/AI/BT/decorators/RepeatUntilFail.hpp"
#include "Quasura/AI/BT/decorators/RepeatUntilSuccess.hpp"
#include "Quasura/AI/BT/decorators/Succeeder.hpp"

// AStar
#include "Quasura/AI/astar/Layer.hpp"
#include "Quasura/AI/astar/MovementStrategy.hpp"
#include "Quasura/AI/astar/Cell.hpp"
#include "Quasura/AI/astar/Helper.hpp"

#endif //QUASURA_AI_HPP
