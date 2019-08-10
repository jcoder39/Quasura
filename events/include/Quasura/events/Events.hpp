/*
 * Events.hpp
 *
 * Created by Viacheslav Borisenko
 *
 * Copyright (c) 2018 spectrobyte http://spectrobyte.com
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 *
 */

#ifndef QUASURA_EVENTS_HPP
#define QUASURA_EVENTS_HPP

#include <typeinfo>
#include <map>
#include <set>
#include "Global.hpp"
#include "Quasura/common/Singleton.hpp"
#include "Event.hpp"
#include "EventListener.hpp"
#include "Quasura/common/Logger.hpp"

EVENTS_NAMESPACE_BEGIN

class Events : public quasura::common::Singleton<Events>
{
  friend class quasura::common::Singleton<Events>;
public:

  template <typename T>
  void RegisterListener(const EventListener& listener)
  {
    auto type = typeid(T).name();
    _listeners.emplace(type, listener);
  }

  void UnregisterListener(const std::string& id)
  {
    for(auto it = _listeners.begin(); it != _listeners.end();) {
      if((it->second).GetID() == id) {
        it = _listeners.erase(it);
      } else {
        it++;
      }
    }
  }

  void Emit(const EventPtr& event)
  {
    auto listeners = _listeners.equal_range(typeid(*event).name());
    for(auto it = listeners.first; it != listeners.second; ++it) {
      it->second(event);
    }
  }

  void Emit(const EventPtr& event, const std::set<std::string>& listenerIDs)
  {
    auto listeners = _listeners.equal_range(typeid(*event).name());
    for(auto it = listeners.first; it != listeners.second; ++it) {
      if(hasListener(it->second, listenerIDs)){
        it->second(event);
      }
    }
  }

private:

  std::multimap<std::string, EventListener> _listeners;
  Events() = default;

  bool hasListener(const EventListener& listener, const std::set<std::string>& listenerIDs) const
  {
    auto search = listenerIDs.find(listener.GetID());
    if(search != listenerIDs.end()) {
      return true;
    } else {
      return false;
    }
  }
};

EVENTS_NAMESPACE_END

#endif //QUASURA_EVENTS_HPP
