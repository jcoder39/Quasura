/*
 * Event.hpp
 *
 * Created by Viacheslav Borisenko
 *
 * Copyright (c) 2018 spectrobyte http://spectrobyte.com
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 *
 */

#ifndef QUASURA_EVENT_HPP
#define QUASURA_EVENT_HPP

#include <memory>
#include "Global.hpp"

EVENTS_NAMESPACE_BEGIN

class Event
{
public:
  Event() = default;
  virtual ~Event() = 0;
};

inline Event::~Event() = default;

using EventPtr = std::shared_ptr<quasura::events::Event>;

EVENTS_NAMESPACE_END

#endif //QUASURA_EVENT_HPP
