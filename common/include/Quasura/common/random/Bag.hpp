/*
 * Bag.hpp
 *
 * Created by Viacheslav Borisenko
 *
 * Copyright (c) 2018 spectrobyte http://spectrobyte.com
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 *
 */

#ifndef QUASURA_BAG_HPP
#define QUASURA_BAG_HPP

#include <vector>
#include "Chaos.hpp"
#include "Quasura/common/Global.hpp"

COMMON_NAMESPACE_BEGIN

template<typename T>
class Bag
{
public:
  Bag() = default;
  explicit Bag(const std::vector<T>& elements) : _elements(elements) {}

  void Add(const T& element)
  {
    _elements.push_back(element);
  }

  void Add(const std::vector<T>& elements)
  {
    _elements.insert(_elements.end(), elements.begin(), elements.end());
  }

  T Get()
  {
    auto chaos = Chaos::Instance();
    auto index = chaos->GetRandom(0, _elements.size() - 1);
    return _elements.at(index);
  }

private:
  std::vector<T> _elements;
};

COMMON_NAMESPACE_END

#endif //QUASURA_BAG_HPP