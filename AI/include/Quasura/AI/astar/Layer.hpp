/*
 * Layer.hpp
 *
 * Created by Viacheslav Borisenko
 *
 * Copyright (c) 2018 spectrobyte http://spectrobyte.com
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 *
 */

#ifndef QUASURA_AI_ASTAR_LAYER_HPP
#define QUASURA_AI_ASTAR_LAYER_HPP

#include <map>
#include <memory>
#include <string>
#include <random>
#include <ctime>
#include <vector>
#include <set>
#include <iostream>
#include <algorithm>
#include <iterator>
#include "Quasura/AI/Global.hpp"
#include "Cell.hpp"
#include "MovementStrategy.hpp"
#include "Helper.hpp"
#include "Quasura/math/Vector2.hpp"
#include "Quasura/math/Rect.hpp"

AI_NAMESPACE_BEGIN

namespace astar {

struct Area
{
  int _type;
  math::Rect<int> _rect;

  Area(math::Rect<int>& rect, int type) : _type(type), _rect(rect) {}
};

struct Path
{
  enum Status
  {
    OK,
    WRONG_PATH
  };

  Path() : _status(WRONG_PATH), _path({})
  {}

  Path(Status status, const std::vector<std::string>& path) : _status(status), _path(path)
  {};

  Status _status;
  std::vector<std::string> _path;
};

struct Influence
{
  math::Vector2<int> _position;
  int _from;
  int _to;

  Influence(math::Vector2<int>& position, int val) : _position(position), _from(0), _to(val)
  {}

  static std::vector<Influence>& Empty()
  {
    static std::vector<Influence> empty;
    return empty;
  }
};

class Layer
{
public:
  explicit Layer(const std::string& id, math::Rect<int>& rect, const MovementStrategy::Type& type = MovementStrategy::Type::ORTHOGONAL_DIAGONAL);

  void Init();

  Path BuildPath(math::Vector2<int>& from, math::Vector2<int>& to, const std::set<int>& possibleObstaclesTypes, unsigned int maxHops = 0,
                 std::vector<Influence>& changeType = Influence::Empty(),
                 std::vector<Influence>& setInfluence = Influence::Empty());

  bool HasObstacles(math::Vector2<int>& position, const std::set<int>& possibleTypes);

  void SetArea(const Area& area);

  math::Rect<int> GetSize();

  CellPtr GetCell(const std::string& code);

  CellPtr GetCell(math::Vector2<int>& position);

  const std::map<std::string, CellPtr>& GetCells();

  std::string GetId();

  int** GetMap();

  void DisplayLayout();

  void DisplayNeighbors();

  void DisplayTypesOfCells();

private:
  std::string _id;
  int _capacityX;
  int _capacityY;
  CellPtr _goal;
  math::Rect<int> _rect;
  std::shared_ptr<MovementStrategy> _strategy;
  std::map<std::string, CellPtr> _cells;
  std::map<std::string, CellPtr> _openedList;
  std::map<std::string, CellPtr> _closedList;

  CellPtr findCellWithMinimalF();

  bool hasElementInOpenList(const std::string& code);

  void removeElementInOpenList(const std::string& code);

  void clear();
};

}

AI_NAMESPACE_END

#endif //QUASURA_AI_ASTAR_LAYER_HPP
