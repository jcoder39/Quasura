/*
 * EventListener.hpp
 *
 * Created by Viacheslav Borisenko
 *
 * Copyright (c) 2018 spectrobyte http://spectrobyte.com
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 *
 */

#ifndef QUASURA_EVENT_LISTENER_HPP
#define QUASURA_EVENT_LISTENER_HPP

#include <functional>
#include "Global.hpp"
#include "Event.hpp"

EVENTS_NAMESPACE_BEGIN

class EventListener
{
public:
  explicit EventListener(const std::string& id, std::function<void(const EventPtr&)>& callback) : _id(id), _callback(callback){}

  template <typename Class, typename Callback>
  explicit EventListener(const std::string& id, Class* object, Callback callback)
  {
    _id = id;
    _callback = std::bind(callback, object, std::placeholders::_1);
  };

  std::string GetID() const
  {
    return _id;
  }

  void operator()(const EventPtr& event)
  {
    _callback(event);
  }

private:
  std::string _id;
  std::function<void(const EventPtr&)> _callback;
};

EVENTS_NAMESPACE_END

#endif //QUASURA_EVENT_LISTENER_HPP
