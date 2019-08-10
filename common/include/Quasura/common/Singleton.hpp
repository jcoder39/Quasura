/*
 * Singleton.hpp
 *
 * Created by Viacheslav Borisenko
 *
 * Copyright (c) 2018 spectrobyte http://spectrobyte.com
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 *
 */

#ifndef QUASURA_SINGLETON_HPP
#define QUASURA_SINGLETON_HPP

#include "Global.hpp"

COMMON_NAMESPACE_BEGIN

template<typename T>
class Singleton
{
  friend T;
public:
  virtual ~Singleton() = default;

  static T* Instance()
  {
    static T t;
    return &t;
  }

private:
  Singleton() = default;
};

COMMON_NAMESPACE_END

#endif //QUASURA_SINGLETON_HPP
