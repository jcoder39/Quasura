/*
 * ComponentContainer.hpp
 *
 * Created by Viacheslav Borisenko
 *
 * Copyright (c) 2018 spectrobyte http://spectrobyte.com
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 *
 */

#ifndef QUASURA_COMPONENT_CONTAINER_HPP
#define QUASURA_COMPONENT_CONTAINER_HPP

#include <iostream>
#include <map>
#include <memory>
#include "Global.hpp"
#include "Component.hpp"
#include "ComponentCollection.hpp"
#include "Quasura/common/Logger.hpp"
#include "Object.hpp"
#include "Quasura/events/Events.hpp"
#include "events/AddComponentEvent.hpp"
#include "events/RemoveComponentEvent.hpp"

ECS_NAMESPACE_BEGIN

class ComponentContainer : public Object
{
  friend class ECS;
public:
  using ComponentType = std::string;

  ComponentContainer& operator=(const ComponentContainer&) = delete;

  ComponentContainer(const ComponentContainer&) = delete;

  ComponentContainer() = default;

  ~ComponentContainer() override
  {
    auto events = quasura::events::Events::Instance();
    events->UnregisterListener(GetID());
  }

  void Init()
  {
    auto events = quasura::events::Events::Instance();
    events->RegisterListener<AddComponentEvent>(quasura::events::EventListener(GetID(), std::addressof(*this), &ComponentContainer::onAddComponent));
    events->RegisterListener<RemoveComponentEvent>(quasura::events::EventListener(GetID(), std::addressof(*this), &ComponentContainer::onRemoveComponent));
    SYSLOG("init");
  }

  template<typename T>
  std::shared_ptr<T> GetComponent(const std::string& id)
  {
    auto type = typeid(T).name();
    auto collection = this->getCollection(type);

    return collection->GetComponent<T>(id);
  }

  template<typename T>
  std::vector<std::shared_ptr<T>> GetComponents()
  {
    auto type = typeid(T).name();
    auto collection = this->getCollection(type);

    auto components = collection->GetComponents<T>();
    return components;
  }

private:
  std::map<ComponentType, ComponentCollectionPtr> _componentCollection;

  ComponentCollectionPtr getCollection(const ComponentType& type)
  {
    auto iterator = this->_componentCollection.find(type);
    if(iterator != this->_componentCollection.end()) {
      return iterator->second;
    }

    ComponentCollectionPtr collection = std::make_shared<ComponentCollection>();
    this->_componentCollection.insert(std::make_pair(type, collection));
    return collection;
  }

  void clear()
  {
    _componentCollection.clear();
  }

  void onAddComponent(const quasura::events::EventPtr& e)
  {
    auto addEvent = std::static_pointer_cast<AddComponentEvent>(e);
    auto component = addEvent->_component;
    auto type = component->GetType();
    auto collection = getCollection(type);
    collection->AddComponent(component);
  }

  void onRemoveComponent(const quasura::events::EventPtr& e)
  {
    auto removeEvent = std::static_pointer_cast<RemoveComponentEvent>(e);
    auto component = removeEvent->_component;
    auto type = component->GetType();
    auto collection = this->getCollection(type);
    collection->RemoveComponent(component->GetID());
  }
};

using ComponentContainerPtr = std::shared_ptr<quasura::ecs::ComponentContainer>;

ECS_NAMESPACE_END

#endif //QUASURA_COMPONENT_CONTAINER_HPP
