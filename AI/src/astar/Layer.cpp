/*
 * Layer.cpp
 *
 * Created by Viacheslav Borisenko
 *
 * Copyright (c) 2018 spectrobyte http://spectrobyte.com
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 *
 */

#include "Quasura/AI/astar/Layer.hpp"

AI_NAMESPACE_BEGIN

namespace astar {

using namespace std;
USING_MATH_NAMESPACE

Layer::Layer(const std::string& id, Rect<int>& rect, const MovementStrategy::Type& type) : _id(id), _rect(rect), _goal(nullptr)
{
  _capacityX = Helper::calculateWidth(_rect.GetWidth());
  _capacityY = Helper::calculateWidth(_rect.GetHeight());
  if(type == MovementStrategy::Type::ORTHOGONAL){
    _strategy = make_shared<Orthogonal>(_capacityX, _capacityY);
  } else {
    _strategy = make_shared<OrthogonalDiagonal>(_capacityX, _capacityY);
  }
}

void Layer::Init()
{
  for(int r = _rect.GetX(); r < _rect.GetWidth(); r++) {
    for(int c = _rect.GetY(); c < _rect.GetHeight(); c++) {
      auto code = ext::to_string(r, _capacityX) + ext::to_string(c, _capacityY);
      auto position = Vector2<int>(r, c);
      auto cell = make_shared<Cell>(_id, code, position);
      _cells.insert({cell->GetCode(), cell});
    }
  }

  _strategy->CreateRelations(_rect, _cells);
}

Path Layer::BuildPath(Vector2<int>& from, Vector2<int>& to, const set<int>& possibleObstaclesTypes, unsigned int maxHopes,
                      std::vector<Influence>& changeType, std::vector<Influence>& setInfluence)
{
  clear();

  for(auto& change : changeType) {
    auto cell = GetCell(change._position);
    change._from = cell->GetType();
    cell->SetType(change._to);
  }

  for(auto& influence : setInfluence) {
    auto cell = GetCell(influence._position);
    influence._from = cell->GetInfluenceG();
    cell->SetInfluenceG(influence._to);
  }

  if(maxHopes == 0) {
    auto a = _rect.GetWidth() * _rect.GetHeight() / 2;
    maxHopes = static_cast<unsigned int>(std::floor(a + 0.5f));
  }

  auto srcCode = Helper::getCode(from._x, from._y, _capacityX, _capacityY);
  CellPtr current = _cells.at(srcCode);
  auto goalCode = Helper::getCode(to._x, to._y, _capacityX, _capacityY);
  _goal = _cells.at(goalCode);

  Vector2<int> point = _goal->GetPoint();
    if(HasObstacles(point, possibleObstaclesTypes)) {
    auto a = std::sqrt(_rect.GetWidth() * _rect.GetWidth() + _rect.GetHeight() * _rect.GetHeight());
    maxHopes = static_cast<unsigned int>(std::floor(a + 0.5f));
  }

  _openedList.insert({current->GetCode(), current});
  CellPtr minCellByH;
  bool wrong = true;
  unsigned int cycle = 0;
  while(true) {
    cycle++;
    if(current == _goal) {
      wrong = false;
      break;
    }

    auto& neighbors = current->GetNeighbors();
    for(auto neighbor : neighbors) {
      if(_closedList.count(neighbor->GetCode())) {
        continue;
      }

      auto found = possibleObstaclesTypes.find(neighbor->GetType());
      if(found != possibleObstaclesTypes.end()) {
        continue;
      }

      if(hasElementInOpenList(neighbor->GetCode())) {
        if(neighbor->CalculateG(current) < neighbor->GetG()) {
          neighbor->SetParent(current);
          auto g = neighbor->CalculateG(current);
          neighbor->SetG(g);
        }
      } else {
        neighbor->SetParent(current);
        auto g = neighbor->CalculateG(current);
        neighbor->SetG(g);
        neighbor->CalculateH(_goal);
        _openedList.insert({neighbor->GetCode(), neighbor});
      }
    }

    removeElementInOpenList(current->GetCode());
    _closedList.insert({current->GetCode(), current});

    if(_openedList.empty()) {
      break;
    }

    current = findCellWithMinimalF();

    if(minCellByH == nullptr) {
      minCellByH = current;
    }
    if(current->GetH() < minCellByH->GetH()) {
      minCellByH = current;
    }

    if(cycle > maxHopes) {
      break;
    }
  }

  std::vector<std::string> path;
  Path::Status status = Path::OK;

  if(wrong) {
    status = Path::WRONG_PATH;
    CellPtr cur = minCellByH;
    if(cur == nullptr) {
      return Path(status, {});
    }
    path.push_back(cur->GetCode());

    while(true) {
      auto parent = cur->GetParent();
      if(parent == nullptr) {
        break;
      }

      cur = parent;
      path.push_back(cur->GetCode());
    }
  } else {
    CellPtr cur = _goal;
    path.push_back(cur->GetCode());

    while(true) {
      auto parent = cur->GetParent();
      if(parent == nullptr) {
        break;
      }

      cur = parent;
      path.push_back(cur->GetCode());
    }
  }
  path.pop_back();
  std::reverse(path.begin(), path.end());

  for(auto& change : changeType) {
    auto cell = GetCell(change._position);
    cell->SetType(change._from);
  }

  for(auto& influence : setInfluence) {
    auto cell = GetCell(influence._position);
    cell->SetInfluenceG(influence._from);
  }

  return Path(status, path);
}

bool Layer::HasObstacles(Vector2<int>& position, const std::set<int>& possibleTypes)
{
  std::string code = Helper::getCode(position, _capacityX, _capacityY);
  auto cell = _cells.at(code);
  auto search = possibleTypes.find(cell->GetType());
  return search != possibleTypes.end();
}

void Layer::SetArea(const Area& area)
{
  auto rect = area._rect;

  int width = rect.GetX() + rect.GetWidth();
  if(width > _rect.GetWidth()) {
    width = _rect.GetWidth();
  }
  int height = rect.GetY() + rect.GetHeight();
  if(height > _rect.GetHeight()) {
    height = _rect.GetHeight();
  }

  for(int x = rect.GetX(); x < width; x++) {
    for(int y = rect.GetY(); y < height; y++) {
      std::string code = Helper::getCode(x, y, _capacityX, _capacityY);
      auto cell = _cells.at(code);
      cell->SetType(area._type);
    }
  }
}

math::Rect<int> Layer::GetSize()
{
  return _rect;
}

CellPtr Layer::GetCell(const std::string& code)
{
  return _cells.at(code);
}

CellPtr Layer::GetCell(Vector2<int>& position)
{
  auto code = Helper::getCode(position._x, position._y, _capacityX, _capacityY);
  return GetCell(code);
}

const std::map<std::string, std::shared_ptr<Cell>>& Layer::GetCells()
{
  return _cells;
}

std::string Layer::GetId()
{
  return _id;
}

int** Layer::GetMap()
{
  int width = _rect.GetWidth() - _rect.GetX();
  int height = _rect.GetHeight() - _rect.GetY();

  int** map = new int* [width + 1];
  for(int i = 0; i <= width; i++) {
    map[i] = new int[height];
  }
  for(const auto& [id, cell] : _cells) {
    Vector2<int> point = cell->GetPoint();
    map[point._x][point._y] = cell->GetType();
  }
  return map;
}

void Layer::DisplayLayout()
{
  std::cout << "  ";
  for(int c = _rect.GetY(); c < _rect.GetHeight(); c++) {
    std::cout << c << "  ";
  }
  std::cout << std::endl;
  std::cout << " _";
  for(int c = _rect.GetY(); c < _rect.GetHeight() * 3; c++) {
    std::cout << "_";
  }
  std::cout << std::endl;
  for(int r = _rect.GetX(); r < _rect.GetWidth(); r++) {
    std::cout << r << "|";
    for(int c = _rect.GetY(); c < _rect.GetHeight(); c++) {
      std::string code = Helper::getCode(r, c, _capacityX, _capacityY);
      auto& cell = _cells.at(code);
      std::cout << " " << cell->GetCode();
    }
    std::cout << std::endl;
  }
}

void Layer::DisplayNeighbors()
{
  for(int r = _rect.GetX(); r < _rect.GetWidth(); r++) {
    for(int c = _rect.GetY(); c < _rect.GetHeight(); c++) {
      std::string code = Helper::getCode(r, c, _capacityX, _capacityY);
      auto& cell = _cells.at(code);
      std::cout << "cell: " << cell->GetCode() << " neighbours: ";
      for(auto n : cell->GetNeighbors()) {
        std::cout << " " << n->GetCode() << ",";
      }
      std::cout << std::endl;
      std::cout << std::endl;
    }
  }
}

void Layer::DisplayTypesOfCells()
{
  std::cout << "   ";
  for(int r = _rect.GetY(); r < _rect.GetWidth(); r++) {
    std::cout << r << " ";
  }
  std::cout << std::endl;
  std::cout << " _";
  for(int r = _rect.GetY(); r < _rect.GetWidth() * 2; r++) {
    std::cout << "_";
  }
  std::cout << std::endl;

  for(int c = _rect.GetY(); c < _rect.GetHeight(); c++) {
    std::cout << c << "|";
    for(int r = _rect.GetX(); r < _rect.GetWidth(); r++) {
      std::string code = Helper::getCode(r, c, _capacityX, _capacityY);
      auto& cell = _cells.at(code);
      std::cout << " " << cell->GetType();
    }
    std::cout << std::endl;
  }
}

CellPtr Layer::findCellWithMinimalF()
{
  CellPtr min;
  for(auto& [id, cell] : _openedList) {
    if(min == nullptr) {
      min = cell;
      continue;
    }
    if(cell->GetF() < min->GetF()) {
      min = cell;
    }
  }
  return min;
}

bool Layer::hasElementInOpenList(const std::string& code)
{
  return _openedList.find(code) != _openedList.end();
}

void Layer::removeElementInOpenList(const std::string& code)
{
  _openedList.erase(code);
}

void Layer::clear()
{
  _openedList.clear();
  _closedList.clear();
  for(auto& [id, cell] : _cells) {
    cell->Reset();
  }
}

}

AI_NAMESPACE_END