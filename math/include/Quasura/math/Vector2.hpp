
/*
 * Vector2.hpp
 *
 * Created by Viacheslav Borisenko
 *
 * Copyright (c) 2019 spectrobyte http://spectrobyte.com
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 *
 */

#ifndef QUASURA_MATH_VECTOR2_HPP
#define QUASURA_MATH_VECTOR2_HPP

#include <cmath>
#include "Global.hpp"

MATH_NAMESPACE_BEGIN

template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
class Vector2
{
public:
  Vector2() : _x(0), _y(0) {}
  explicit Vector2(T x, T y) : _x(x), _y(y) {}

  Vector2(const Vector2& other) : _x(other._x), _y(other._y) {}

  Vector2& operator=(const Vector2& other)
  {
    if(this == &other) {
      return *this;
    }

    this->_x = other._x;
    this->_y = other._y;

    return *this;
  }

  Vector2 operator-(const Vector2& another) const
  {
    return Vector2(_x - another._x, _y - another._y);
  }

  Vector2 operator-() const
  {
    return Vector2(-this->_x, -this->_y);
  }

  Vector2& operator+=(const Vector2& other)
  {
    _x += other._x;
    _y += other._y;

    return *this;
  }

  Vector2& operator-=(const Vector2& other)
  {
    _x -= other._x;
    _y -= other._y;

    return *this;
  }

  Vector2 operator+(const Vector2& other) const
  {
    Vector2 p(*this);
    p._x += other._x;
    p._y += other._y;
    return p;
  }

  Vector2 operator*(float s) const
  {
    return Vector2(this->_x * s, this->_y * s);
  }

  Vector2& operator*=(float s)
  {
    this->_x *= s;
    this->_y *= s;

    return *this;
  }

  Vector2 operator/(float s) const
  {
    return Vector2(this->_x / s, this->_y / s);
  }

  Vector2& operator/=(float s)
  {
    this->_x /= s;
    this->_y /= s;

    return *this;
  }

  bool operator==(const Vector2& rhs) const
  {
    return this->_x == rhs._x && this->_y == rhs._y;
  }
  bool operator!=(const Vector2& rhs) const
  {
    return this->_x != rhs._x || this->_y != rhs._y;
  }

  void Normalize()
  {
    auto length = Magnitude();
    length = 1.0f / length;
    double x = _x * length;
    double y = _y * length;

    _x = static_cast<T>(x);
    _y = static_cast<T>(y);
  }

  double Magnitude() const
  {
    return std::sqrt((_x * _x + _y * _y));
  }

  float Distance(const Vector2& other) const
  {
    float dx = other._x - _x;
    float dy = other._y - _y;

    return std::sqrt(dx * dx + dy * dy);
  }

  float Dot(const Vector2& other) const
  {
    return (_x * other._x + _y * other._y);
  }

public:
  T _x;
  T _y;
};

MATH_NAMESPACE_END

#endif //QUASURA_MATH_VECTOR2_HPP
