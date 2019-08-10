/*
 * RemoveComponentEvent.hpp
 *
 * Created by Viacheslav Borisenko
 *
 * Copyright (c) 2018 spectrobyte http://spectrobyte.com
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 *
 */

#ifndef QUASURA_REMOVE_COMPONENT_EVENT_HPP
#define QUASURA_REMOVE_COMPONENT_EVENT_HPP

#include "Quasura/ECS/Global.hpp"
#include "Quasura/events/Event.hpp"
#include "Quasura/ECS/Component.hpp"

ECS_NAMESPACE_BEGIN

struct RemoveComponentEvent : public quasura::events::Event
{
  ComponentPtr _component;
  RemoveComponentEvent(const ComponentPtr& component) : _component(component) {}
};

ECS_NAMESPACE_END

#endif //QUASURA_REMOVE_COMPONENT_EVENT_HPP
