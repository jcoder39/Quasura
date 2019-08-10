/*
 * System.hpp
 *
 * Created by Viacheslav Borisenko
 *
 * Copyright (c) 2018 spectrobyte http://spectrobyte.com
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 *
 */

#ifndef QUASURA_SYSTEM_HPP
#define QUASURA_SYSTEM_HPP

#include <memory>
#include "Global.hpp"
#include "Object.hpp"
#include "Quasura/events/Events.hpp"
#include "ComponentContainer.hpp"

ECS_NAMESPACE_BEGIN

class System : public Object
{
  friend class ECS;
public:
  System& operator=(const System&) = delete;
  System(const System&) = delete;

  explicit System(int priority);
  virtual ~System() = 0;

  virtual void Update(float) = 0;

  int GetPriority();

protected:
  ComponentContainerPtr _componentContainer;
  int _priority;

private:
  void setComponentContainer(const ComponentContainerPtr& container);
};

using SystemPtr = std::shared_ptr<quasura::ecs::System>;

ECS_NAMESPACE_END

#endif //QUASURA_SYSTEM_HPP
