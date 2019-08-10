/*
 * ComponentCollection.hpp
 *
 * Created by Viacheslav Borisenko
 *
 * Copyright (c) 2018 spectrobyte http://spectrobyte.com
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 *
 */

#ifndef QUASURA_COMPONENT_COLLECTION_HPP
#define QUASURA_COMPONENT_COLLECTION_HPP

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include "Global.hpp"
#include "Component.hpp"
#include "Quasura/common/Logger.hpp"

ECS_NAMESPACE_BEGIN

class ComponentCollection
{
public:
  ComponentCollection() = default;
  ~ComponentCollection() = default;

  void AddComponent(const ComponentPtr& component)
  {
    if(hasComponent(component->GetID())){
      _components[component->GetID()] = component;
      return;
    }
    _components.insert({component->GetID(), component});
  }

  template<typename T>
  std::shared_ptr<T> GetComponent(const std::string& id)
  {
    if(!hasComponent(id)){
      return nullptr;
    }

    return std::static_pointer_cast<T>(_components.at(id));
  }

  template<typename T>
  std::vector<std::shared_ptr<T>> GetComponents()
  {
    std::vector<std::shared_ptr<T>> temp;
    temp.reserve(_components.size());

    std::transform(_components.begin(), _components.end(), std::back_inserter(temp),
                   [](const auto& entity) {
                     return std::static_pointer_cast<T>(entity.second);
                   });

    return temp;
  }

  void RemoveComponent(const std::string& id)
  {
    _components.erase(id);
  }

private:
  std::map<std::string, ComponentPtr> _components;

  bool hasComponent(const std::string& id)
  {
    auto iterator = this->_components.find(id);
    return iterator != this->_components.end();
  }
};

using ComponentCollectionPtr = std::shared_ptr<quasura::ecs::ComponentCollection>;

ECS_NAMESPACE_END

#endif //QUASURA_COMPONENT_COLLECTION_HPP
