/*
 * Cell.hpp
 *
 * Created by Viacheslav Borisenko
 *
 * Copyright (c) 2018 spectrobyte http://spectrobyte.com
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 *
 */

#ifndef QUASURA_AI_ASTAR_CELL_HPP
#define QUASURA_AI_ASTAR_CELL_HPP

#include <vector>
#include <string>
#include <cmath>
#include <memory>
#include "Quasura/AI/Global.hpp"
#include "Quasura/math/Vector2.hpp"

AI_NAMESPACE_BEGIN

namespace astar {

class Cell
{
public:
  using CellCollection = std::vector<std::shared_ptr<Cell>>;

  enum RelationType
  {
    ORTHO, DIAG
  };

  explicit Cell(const std::string& layoutId, const std::string& code, math::Vector2<int>& point);

  void SetType(int type);

  int GetType();

  void SetG(int g);

  int GetG();

  int GetF();

  int GetH();

  int CalculateG(const std::shared_ptr<Cell>& other);

  void CalculateH(const std::shared_ptr<Cell>& goal);

  void SetInfluenceG(int val);

  int GetInfluenceG();

  void RemoveInfluence();

  RelationType GetRelationType(const std::shared_ptr<Cell>& neighbour);

  void AddNeighbor(const std::shared_ptr<Cell>& neighbour);

  CellCollection& GetNeighbors();

  void SetParent(const std::shared_ptr<Cell>& parent);

  std::shared_ptr<Cell> GetParent();

  std::string GetCode();

  math::Vector2<int> GetPoint();

  void Reset();

private:
  int _influenceG;
  int _g;
  int _h;
  int _f;
  int _type;
  std::string _layoutId;
  std::string _code;
  math::Vector2<int> _point;
  std::shared_ptr<Cell> _parent;
  CellCollection _neighbors;
};

using CellPtr = std::shared_ptr<Cell>;

}

AI_NAMESPACE_END

#endif //QUASURA_AI_ASTAR_CELL_HPP
