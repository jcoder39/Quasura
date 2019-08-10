
/*
 * Rect.hpp
 * 
 * Created by Viacheslav Borisenko
 * 
 * Copyright (c) 2018 spectrobyte http://spectrobyte.com
 * 
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 *
 */

#ifndef QUASURA_MATH_RECT_HPP
#define QUASURA_MATH_RECT_HPP

#include <cmath>
#include "Global.hpp"

MATH_NAMESPACE_BEGIN

template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
class Rect
{
public:
  Rect() : _x(0), _y(0), _width(0), _height(0) {}
  explicit Rect(T x, T y, T width, T height) : _x(x), _y(y), _width(width), _height(height) {}
  Rect(const Rect& other) : _x(other._x), _y(other._y), _width(other._width), _height(other._height) {}
  Rect& operator=(const Rect& other)
  {
    if(this == &other) {
      return *this;
    }

    this->_x = other._x;
    this->_y = other._y;
    this->_width = other._width;
    this->_height = other._height;

    return *this;
  }

  bool operator==(const Rect& rhs) const
  {
    return this->_x == rhs._x && this->_y == rhs._y && this->_width == rhs._width && this->_height == rhs._height;
  }

  bool operator!=(const Rect& rhs) const
  {
    return this->_x == rhs._x || this->_y == rhs._y || this->_width == rhs._width || this->_height == rhs._height;
  }

  T GetX() const { return _x; }
  T GetY() const { return _y; }
  T GetWidth() const { return _width; }
  T GetHeight() const { return _height; }

  void SetX(T val) { _x = val; }
  void SetY(T val) { _y = val; }
  void SetWidth(T val) { _width = val; }
  void SetHeight(T val) { _height = val; }

private:
  T _x;
  T _y;
  T _width;
  T _height;
};

MATH_NAMESPACE_END

#endif //QUASURA_MATH_RECT_HPP
