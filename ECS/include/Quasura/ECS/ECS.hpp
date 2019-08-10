/*
 * ECS.hpp
 *
 * Created by Viacheslav Borisenko
 *
 * Copyright (c) 2018 spectrobyte http://spectrobyte.com
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 *
 */

#ifndef QUASURA_ECS_HPP
#define QUASURA_ECS_HPP

#include <memory>
#include <vector>
#include <map>
#include <algorithm>
#include "Global.hpp"
#include "System.hpp"
#include "Entity.hpp"
#include "Object.hpp"
#include "ComponentContainer.hpp"
#include "Quasura/events/Events.hpp"
#include "Quasura/ECS/events/RemoveComponentEvent.hpp"
#include "Quasura/ECS/events/RemoveEntityEvent.hpp"
#include "Quasura/ECS/events/AddComponentToEntityEvent.hpp"

ECS_NAMESPACE_BEGIN

class ECS : public Object
{
public:
  ECS& operator=(const ECS&) = delete;
  ECS(const ECS&) = delete;

  ECS();
  ~ECS() override;

  void Init();

  EntityPtr CreateEntity();
  EntityPtr GetEntity(const std::string& id);

  void AddSystem(const SystemPtr& system);
  void RemoveSystem(const std::string& systemID);

  ComponentContainerPtr& GetComponentContainer();

  void Update(float dt);

  void Clear();

private:
  ComponentContainerPtr _componentContainer;
  std::vector<SystemPtr> _systems;
  std::map<std::string, EntityPtr> _entities;

  void onRemoveComponent(const quasura::events::EventPtr& e);
  void onRemoveEntity(const quasura::events::EventPtr& e);
  void onAddComponentToEntityEvent(const quasura::events::EventPtr& e);
};

using ECSPtr = std::shared_ptr<quasura::ecs::ECS>;

ECS_NAMESPACE_END

#endif //QUASURA_ECS_HPP
