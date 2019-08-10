/*
 * MovementStrategy.hpp
 *
 * Created by Viacheslav Borisenko
 *
 * Copyright (c) 2018 spectrobyte http://spectrobyte.com
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 *
 */

#ifndef QUASURA_AI_ASTAR_STRATEGY_HPP
#define QUASURA_AI_ASTAR_STRATEGY_HPP

#include <map>
#include <memory>
#include "Quasura/AI/Global.hpp"
#include "Cell.hpp"
#include "Helper.hpp"
#include "Quasura/math/Rect.hpp"
#include "Quasura/math/Mathematician.hpp"

AI_NAMESPACE_BEGIN

namespace astar {

struct MovementStrategy
{
  enum class Type { ORTHOGONAL, ORTHOGONAL_DIAGONAL };

  MovementStrategy(int widthX, int widthY) : _widthX(widthX), _widthY(widthY)
  {}

  virtual ~MovementStrategy()
  {};

  virtual void CreateRelations(math::Rect<int>& border, std::map<std::string, CellPtr>& cells) = 0;

protected:
  int _widthX, _widthY = 0;
};

struct Orthogonal : public MovementStrategy
{
  Orthogonal(int widthX, int widthY);

  ~Orthogonal() override;

  void CreateRelations(math::Rect<int>& border, std::map<std::string, CellPtr>& cells) override;
};

struct OrthogonalDiagonal : public MovementStrategy
{
  OrthogonalDiagonal(int widthX, int widthY);

  ~OrthogonalDiagonal() override;

  void CreateRelations(math::Rect<int>& border, std::map<std::string, CellPtr>& cells) override;
};

}

AI_NAMESPACE_END

#endif //QUASURA_AI_ASTAR_STRATEGY_HPP
