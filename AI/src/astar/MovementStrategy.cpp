/*
 * MovementStrategy.cpp
 *
 * Created by Viacheslav Borisenko
 *
 * Copyright (c) 2018 spectrobyte http://spectrobyte.com
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 *
 */

#include "Quasura/AI/astar/MovementStrategy.hpp"

AI_NAMESPACE_BEGIN

USING_MATH_NAMESPACE

namespace astar {

Orthogonal::Orthogonal(int widthX, int widthY) : MovementStrategy(widthX, widthY)
{}

Orthogonal::~Orthogonal()
{};

void Orthogonal::CreateRelations(Rect<int>& border, std::map<std::string, CellPtr>& cells)
{
  auto mathematician = Mathematician::Instance();
  for(int r = border.GetX(); r < border.GetWidth(); r++) {
    for(int c = border.GetY(); c < border.GetHeight(); c++) {
      std::string code = Helper::getCode(r, c, _widthX, _widthY);
      auto& cell = cells.at(code);
      auto point = cell->GetPoint();
      if(mathematician->PossibleW(point, border)) {
        auto neighbor = cells.at(Helper::getCodeForW(point, _widthX, _widthY));
        cell->AddNeighbor(neighbor);
      }
      if(mathematician->PossibleN(point, border)) {
        auto neighbor = cells.at(Helper::getCodeForN(point, _widthX, _widthY));
        cell->AddNeighbor(neighbor);
      }
      if(mathematician->PossibleE(point, border)) {
        auto neighbor = cells.at(Helper::getCodeForE(point, _widthX, _widthY));
        cell->AddNeighbor(neighbor);
      }
      if(mathematician->PossibleS(point, border)) {
        auto neighbor = cells.at(Helper::getCodeForS(point, _widthX, _widthY));
        cell->AddNeighbor(neighbor);
      }
    }
  }
}

OrthogonalDiagonal::OrthogonalDiagonal(int widthX, int widthY) : MovementStrategy(widthX, widthY)
{}

OrthogonalDiagonal::~OrthogonalDiagonal()
{};

void OrthogonalDiagonal::CreateRelations(Rect<int>& border, std::map<std::string, CellPtr>& cells)
{
  auto mathematician = Mathematician::Instance();
  for(int r = border.GetX(); r < border.GetWidth(); r++) {
    for(int c = border.GetY(); c < border.GetHeight(); c++) {
      std::string code = Helper::getCode(r, c, _widthX, _widthY);

      auto& cell = cells.at(code);

      auto point = cell->GetPoint();
      if(mathematician->PossibleW(point, border)) {
        auto neighbor = cells.at(Helper::getCodeForW(point, _widthX, _widthY));
        cell->AddNeighbor(neighbor);
      }
      if(mathematician->PossibleWN(point, border)) {
        auto neighbor = cells.at(Helper::getCodeForWN(point, _widthX, _widthY));
        cell->AddNeighbor(neighbor);
      }
      if(mathematician->PossibleN(point, border)) {
        auto neighbor = cells.at(Helper::getCodeForN(point, _widthX, _widthY));
        cell->AddNeighbor(neighbor);
      }
      if(mathematician->PossibleNE(point, border)) {
        auto neighbor = cells.at(Helper::getCodeForNE(point, _widthX, _widthY));
        cell->AddNeighbor(neighbor);
      }
      if(mathematician->PossibleE(point, border)) {
        auto neighbor = cells.at(Helper::getCodeForE(point, _widthX, _widthY));
        cell->AddNeighbor(neighbor);
      }
      if(mathematician->PossibleES(point, border)) {
        auto neighbor = cells.at(Helper::getCodeForES(point, _widthX, _widthY));
        cell->AddNeighbor(neighbor);
      }
      if(mathematician->PossibleS(point, border)) {
        auto neighbor = cells.at(Helper::getCodeForS(point, _widthX, _widthY));
        cell->AddNeighbor(neighbor);
      }
      if(mathematician->PossibleSW(point, border)) {
        auto neighbor = cells.at(Helper::getCodeForSW(point, _widthX, _widthY));
        cell->AddNeighbor(neighbor);
      }
    }
  }
}

}

AI_NAMESPACE_END
