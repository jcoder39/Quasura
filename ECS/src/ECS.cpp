/*
 * ECS.cpp
 *
 * Created by Viacheslav Borisenko
 *
 * Copyright (c) 2018 spectrobyte http://spectrobyte.com
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 *
 */

#include "Quasura/ECS/ECS.hpp"

ECS_NAMESPACE_BEGIN

USING_EVENTS_NAMESPACE
using namespace std;

EntityPtr ECS::CreateEntity()
{
  std::shared_ptr<Entity> entity = std::make_shared<Entity>();
  _entities.insert({entity->GetID(), entity});
  SYSLOG("create entity: " + entity->GetID());
  return entity;
}

EntityPtr ECS::GetEntity(const std::string& id)
{
  SYSLOG("get entity: " + id);
  return _entities.at(id);
}

void ECS::AddSystem(const SystemPtr& system)
{
  system->setComponentContainer(_componentContainer);
  _systems.push_back(system);

  std::sort(_systems.begin(), _systems.end(), [](const SystemPtr& l, const SystemPtr& r) {
    return l->GetPriority() < r->GetPriority();
  });
  SYSLOG("add system: " + system->GetID());
}

void ECS::RemoveSystem(const std::string& systemID)
{
  auto it = std::find_if(_systems.begin(), _systems.end(), [&systemID](const SystemPtr& system) {return system->GetID() == systemID;});

  if(it != _systems.end()) {
    _systems.erase(it);
  }
  SYSLOG("remove system: " + systemID);
}

ComponentContainerPtr& ECS::GetComponentContainer()
{
  return _componentContainer;
}

void ECS::Update(float dt)
{
  for(const auto& system : _systems){
    system->Update(dt);
  }
}

void ECS::Clear()
{
  _componentContainer->clear();
  _entities.clear();
  SYSLOG("clear");
}

void ECS::onRemoveComponent(const EventPtr& e)
{
  auto removeEvent = std::static_pointer_cast<RemoveComponentEvent>(e);
  auto component = removeEvent->_component;
  auto entity = _entities.at(component->GetID());
  SYSLOG(entity->GetID() + " : " + component->GetType());
  entity->removeComponent(component);
}

void ECS::onRemoveEntity(const EventPtr& e)
{
  auto removeEntityEvent = std::static_pointer_cast<RemoveEntityEvent>(e);
  auto entity = _entities.at(removeEntityEvent->_entityId);
  auto events = Events::Instance();
  for(const auto& [key, component] : entity->GetComponents()){
    auto remove = std::make_shared<RemoveComponentEvent>(component);
    events->Emit(remove, {_componentContainer->GetID()});
  }
  SYSLOG(entity->GetID());
  _entities.erase(removeEntityEvent->_entityId);
}

void ECS::onAddComponentToEntityEvent(const EventPtr& e)
{
  auto addComponentToEntityEvent = static_pointer_cast<AddComponentToEntityEvent>(e);
  auto entity = _entities.at(addComponentToEntityEvent->_entityID);
  entity->AddComponent(addComponentToEntityEvent->_component);
  SYSLOG(entity->GetID() + " : " + addComponentToEntityEvent->_component->GetType());
}

void ECS::Init()
{
  _componentContainer = std::make_shared<ComponentContainer>();
  _componentContainer->Init();
  auto events = Events::Instance();
  events->RegisterListener<RemoveComponentEvent>(EventListener(GetID(), std::addressof(*this), &ECS::onRemoveComponent));
  events->RegisterListener<RemoveEntityEvent>(EventListener(GetID(), std::addressof(*this), &ECS::onRemoveEntity));
  events->RegisterListener<AddComponentToEntityEvent>(EventListener(GetID(), std::addressof(*this), &ECS::onAddComponentToEntityEvent));
  SYSLOG("init");
}

ECS::ECS() = default;

ECS::~ECS()
{
  auto events = Events::Instance();
  events->UnregisterListener(GetID());
}

ECS_NAMESPACE_END