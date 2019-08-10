/*
 * Cell.cpp
 *
 * Created by Viacheslav Borisenko
 *
 * Copyright (c) 2018 spectrobyte http://spectrobyte.com
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 *
 */

#include "Quasura/AI/astar/Cell.hpp"

AI_NAMESPACE_BEGIN

USING_MATH_NAMESPACE

namespace astar {

Cell::Cell(const std::string& layoutId, const std::string& code, Vector2<int>& point) :
        _layoutId(layoutId), _code(code), _point(point), _g(0), _h(0), _f(0), _parent(nullptr), _type(0), _influenceG(0)
{}

Cell::RelationType Cell::GetRelationType(const std::shared_ptr<Cell>& neighbour)
{
  if((_point._x - 1 == neighbour->_point._x && _point._y == neighbour->_point._y) ||
     (_point._x == neighbour->_point._x && _point._y + 1 == neighbour->_point._y) ||
     (_point._x + 1 == neighbour->_point._x && _point._y == neighbour->_point._y) ||
     (_point._x == neighbour->_point._x && _point._y - 1 == neighbour->_point._y)) {
    return ORTHO;
  }
  return DIAG;
}

int Cell::CalculateG(const std::shared_ptr<Cell>& other)
{
  int g = other->_g;
  if(GetRelationType(other) == ORTHO) {
    g += 10 + _influenceG;
  } else {
    g += 14 + _influenceG;
  }
  return g;
}

void Cell::SetG(int g)
{
  _g = g;
}

int Cell::GetG()
{
  return _g;
}

int Cell::GetF()
{
  return _g + _h;
}

int Cell::GetH()
{
  return _h;
}

void Cell::SetInfluenceG(int val)
{
  _influenceG = val;
}

int Cell::GetInfluenceG()
{
  return _influenceG;
}

void Cell::RemoveInfluence()
{
  _influenceG = 0;
}

void Cell::CalculateH(const std::shared_ptr<Cell>& goal)
{
  _h = (std::abs(_point._x - goal->_point._x) + std::abs(_point._y - goal->_point._y)) * 10; // manhattan,  10 - min points
}

std::string Cell::GetCode()
{
  return _code;
}

math::Vector2<int> Cell::GetPoint()
{
  return _point;
}

void Cell::AddNeighbor(const std::shared_ptr<Cell>& neighbour)
{
  _neighbors.push_back(neighbour);
}

Cell::CellCollection& Cell::GetNeighbors()
{
  return _neighbors;
}

void Cell::SetParent(const std::shared_ptr<Cell>& parent)
{
  _parent = parent;
}

CellPtr Cell::GetParent()
{
  return _parent;
}

void Cell::SetType(int type)
{
  _type = type;
}

int Cell::GetType()
{
  return _type;
}

void Cell::Reset()
{
  _g = 0;
  _h = 0;
  _f = 0;
  _parent = nullptr;
}

}

AI_NAMESPACE_END