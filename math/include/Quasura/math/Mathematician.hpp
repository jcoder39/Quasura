
/*
 * Mathematician.hpp
 * 
 * Created by Viacheslav Borisenko
 * 
 * Copyright (c) 2018 spectrobyte http://spectrobyte.com
 * 
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 *
 */

#ifndef QUASURA_MATH_MATHEMATICIAN_HPP
#define QUASURA_MATH_MATHEMATICIAN_HPP

#include "Global.hpp"
#include "Quasura/common/Singleton.hpp"
#include "Rect.hpp"
#include "Vector2.hpp"

MATH_NAMESPACE_BEGIN

class Mathematician : public quasura::common::Singleton<Mathematician>
{
  friend class quasura::common::Singleton<Mathematician>;

public:
  template<typename T>
  bool PossibleW(Vector2<T>& point, Rect<T>& border)
  {
    return point._x - 1 >= border.GetX();
  }

  template<typename T>
  bool PossibleWN(Vector2<T>& point, Rect<T>& border)
  {
    return point._x - 1 >= border.GetX() && point._y - 1 >= border.GetY();
  }

  template<typename T>
  bool PossibleN(Vector2<T>& point, Rect<T>& border)
  {
    return point._y - 1 >= border.GetY();
  }

  template<typename T>
  bool PossibleNE(Vector2<T>& point, Rect<T>& border)
  {
    return point._x + 1 < border.GetWidth() && point._y - 1 >= border.GetY();
  }

  template<typename T>
  bool PossibleE(Vector2<T>& point, Rect<T>& border)
  {
    return point._x + 1 < border.GetWidth();
  }

  template<typename T>
  bool PossibleES(Vector2<T>& point, Rect<T>& border)
  {
    return point._x + 1 < border.GetWidth() && point._y + 1 < border.GetHeight();
  }

  template<typename T>
  bool PossibleS(Vector2<T>& point, Rect<T>& border)
  {
    return point._y + 1 < border.GetHeight();
  }

  template<typename T>
  bool PossibleSW(Vector2<T>& point, Rect<T>& border)
  {
    return point._x - 1 >= border.GetX() && point._y + 1 < border.GetHeight();
  }

  template<typename T>
  double Distance(Vector2<T>& point, Rect<T>& rect)
  {
    if(point._x < rect.GetX()) {
      if(point._y < rect.GetY()) {
        Vector2<T> p(rect.GetX(), rect.GetY());
        Vector2<T> diff = point - p;
        return diff.Magnitude();
      } else if(point._y > rect.GetHeight()) {
        Vector2<T> p(rect.GetX(), rect.GetHeight());
        Vector2<T> diff = point - p;
        return diff.Magnitude();
      } else {
        return rect.GetX() - point._x;
      }
    } else if(point._x > rect.GetWidth()) {
      if(point._y < rect.GetY()) {
        Vector2<T> p(rect.GetWidth(), rect.GetY());
        Vector2<T> diff = point - p;
        return diff.Magnitude();
      } else if(point._y > rect.GetHeight()) {
        Vector2<T> p(rect.GetWidth(), rect.GetHeight());
        Vector2<T> diff = point - p;
        return diff.Magnitude();
      } else {
        return point._x - rect.GetWidth();
      }
    } else {
      if(point._y < rect.GetY()) {
        return rect.GetY() - point._y;
      } else if(point._y > rect.GetHeight()) {
        return point._y - rect.GetHeight();
      } else {
        return 0.0f;
      }
    }
  }

  template<typename T>
  bool Contains(Vector2<T>& point, Rect<T>& rect)
  {
    return point._x >= rect.GetX() && point._x < rect.GetX() + rect.GetWidth() &&
           point._y >= rect.GetY() && point._y < rect.GetY() + rect.GetHeight();
  }

  template<typename T>
  bool ContainsIncludeBorders(Vector2<T>& point, Rect<T>& rect)
  {
    return point._x >= rect.GetX() && point._x <= rect.GetX() + rect.GetWidth() &&
           point._y >= rect.GetY() && point._y <= rect.GetY() + rect.GetHeight();
  }

  template<typename T>
  bool ContainsPointIncludeBorders(Rect<T>& area, Rect<T>& rect)
  {
    for(auto x = area.GetX(); x < area.GetWidth(); x++) {
      for(auto y = area.GetY(); y < area.GetHeight(); y++) {
        Vector2<T> point(x, y);
        if(containsIncludeBorders(point, rect)) {
          return true;
        }
      }
    }
    return false;
  }
};

MATH_NAMESPACE_END

#endif //QUASURA_MATH_MATHEMATICIAN_HPP
