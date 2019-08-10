
/*
 * AddComponentToEntityEvent.hpp
 * 
 * Created by Viacheslav Borisenko
 * 
 * Copyright (c) 2018 spectrobyte http://spectrobyte.com
 * 
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 *
 */

#ifndef QUASURA_ADD_COMPONENT_TO_ENTITY_EVENT_HPP
#define QUASURA_ADD_COMPONENT_TO_ENTITY_EVENT_HPP

#include "Quasura/ECS/Global.hpp"
#include "Quasura/events/Event.hpp"
#include "Quasura/ECS/Component.hpp"

ECS_NAMESPACE_BEGIN

struct AddComponentToEntityEvent : public quasura::events::Event
{
  std::string _entityID;
  ComponentPtr _component;

  explicit AddComponentToEntityEvent(const std::string& entityID, const ComponentPtr& component) : _entityID(entityID), _component(component) {}
};

ECS_NAMESPACE_END

#endif //QUASURA_ADD_COMPONENT_TO_ENTITY_EVENT_HPP
