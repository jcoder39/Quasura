/*
 * RemoveEntityEvent.hpp
 *
 * Created by Viacheslav Borisenko
 *
 * Copyright (c) 2018 spectrobyte http://spectrobyte.com
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 *
 */

#ifndef QUASURA_REMOVE_ENTITY_EVENT_HPP
#define QUASURA_REMOVE_ENTITY_EVENT_HPP

#include <string>
#include "Quasura/ECS/Global.hpp"
#include "Quasura/events/Event.hpp"

ECS_NAMESPACE_BEGIN

struct RemoveEntityEvent : public quasura::events::Event
{
  std::string _entityId;
  RemoveEntityEvent(const std::string& entityId) : _entityId(entityId) {}
};

ECS_NAMESPACE_END

#endif //QUASURA_REMOVE_ENTITY_EVENT_HPP
