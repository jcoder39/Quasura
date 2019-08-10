/*
 * Entity.hpp
 *
 * Created by Viacheslav Borisenko
 *
 * Copyright (c) 2018 spectrobyte http://spectrobyte.com
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 *
 */

#ifndef QUASURA_ENTITY_HPP
#define QUASURA_ENTITY_HPP

#include <string>
#include <map>
#include "Global.hpp"
#include "ECS.hpp"
#include "Component.hpp"
#include "Object.hpp"
#include "Quasura/events/Events.hpp"
#include "Quasura/ECS/events/AddComponentEvent.hpp"

ECS_NAMESPACE_BEGIN

class Entity : public Object
{
  friend class ECS;

public:

  Entity() {}

  virtual ~Entity() override {};

  void AddComponent(const ComponentPtr& component)
  {
    std::string id = component->GetID();
    id += ":";
    id += component->GetType();
    if(hasComponent(id)){
      SYSLOG("warning. component with key: " + id + " was updated");
      _components[id] = component;
    } else {
      _components.insert({id, component});
    }
    auto events = quasura::events::Events::Instance();
    auto addComponentEvent = std::make_shared<AddComponentEvent>(component);
    events->Emit(addComponentEvent);
    SYSLOG(id);
  }

  template<typename T>
  std::shared_ptr<T> GetComponent(const std::string& entityID)
  {
    auto type = typeid(T).name();
    std::string id = entityID;
    id += ":";
    id += type;
    if(!hasComponent(id)) {
      return nullptr;
    }

    auto component = std::static_pointer_cast<T>(_components.at(id));
    SYSLOG(id);
    return component;
  }

  std::map<std::string, ComponentPtr>& GetComponents()
  {
    return _components;
  }

protected:
  std::map<std::string, ComponentPtr> _components;

private:

  bool hasComponent(const std::string& id)
  {
    auto iterator = this->_components.find(id);
    return iterator != this->_components.end();
  }

  void removeComponent(const ComponentPtr& component)
  {
    std::string id = component->GetID();
    id += ":";
    id += component->GetType();
    _components.erase(id);
    SYSLOG(id);
  }
};

using EntityPtr = std::shared_ptr<quasura::ecs::Entity>;

ECS_NAMESPACE_END

#endif //QUASURA_ENTITY_HPP
