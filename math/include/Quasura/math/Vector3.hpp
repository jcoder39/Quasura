
/*
 * Vector3.hpp
 *
 * Created by Viacheslav Borisenko
 *
 * Copyright (c) 2019 spectrobyte http://spectrobyte.com
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 *
 */

#ifndef QUASURA_MATH_VECTOR3_HPP
#define QUASURA_MATH_VECTOR3_HPP

#include <cmath>

template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
class Vector3
{
public:
  Vector3() : _x(0), _y(0), _z(0) {}

  explicit Vector3(T x, T y, T z) : _x(x), _y(y), _z(z) {}

  Vector3(const Vector3& other) : _x(other._x), _y(other._y), _z(other._z) {}
  Vector3& operator=(const Vector3& other)
  {
    if(this == &other) {
      return *this;
    }

    this->_x = other._x;
    this->_y = other._y;
    this->_z = other._z;

    return *this;
  }

  bool operator==(const Vector3& other) const
  {
    return this->_x == other._x && this->_y == other._y && this->_z == other._z;
  }

  Vector3 operator+(const Vector3& other) const
  {
    return Vector3(this->_x + other._x, this->_y + other._y, this->_z + other._z);
  }

  Vector3& operator+=(const Vector3& other)
  {
    this->_x += other._x;
    this->_y += other._y;
    this->_z += other._z;

    return *this;
  }

  Vector3 operator-(const Vector3& other) const
  {
    return Vector3(this->_x - other._x, this->_y - other._y, this->_z - other._z);
  }

  Vector3& operator-=(const Vector3& other)
  {
    this->_x -= other._x;
    this->_y -= other._y;
    this->_z -= other._z;

    return *this;
  }

  Vector3 operator-() const
  {
    return Vector3(-this->_x, -this->_y, -this->_z);
  }

  Vector3 operator*(float s) const
  {
    return Vector3(this->_x * s, this->_y * s, this->_z * s);
  }

  Vector3& operator*=(float s)
  {
    this->_x *= s;
    this->_y *= s;
    this->_z *= s;

    return *this;
  }

  Vector3 operator/(float s) const
  {
    return Vector3(this->_x / s, this->_y / s, this->_z / s);
  }

  Vector3& operator/=(float s)
  {
    this->_x /= s;
    this->_y /= s;
    this->_z /= s;

    return *this;
  }

  double Magnitude() const
  {
    return std::sqrt((_x * _x + _y * _y + _z * _z));
  }

  double Magnitude_sqr() const
  {
    return _x * _x + _y * _y + _z * _z;
  }

  void Normalize()
  {
    auto length = Magnitude();
    length = 1.0f / length;
    double x = _x * length;
    double y = _y * length;
    double z = _z * length;

    _x = static_cast<T>(x);
    _y = static_cast<T>(y);
    _z = static_cast<T>(z);
  }

  Vector3 Normalized() const
  {
    Vector3 temp(*this);
    temp.Normalize();
    return temp;
  }

  float Dot(const Vector3& other) const
  {
    return (_x * other._x + _y * other._y + _z * other._z);
  }

  Vector3 Cross(const Vector3& other) const
  {
    return Vector3(this->_y * other._z - this->_z * other._y, this->_z * other._x - this->_x * other._z, this->_x * other._y - this->_y * other._x);
  }

  double Distance(const Vector3& other) const
  {
    auto delta = other - *this;

    return delta.Magnitude();
  }

  double AngleWith(const Vector3& other) const
  {
    return std::acos(this->Dot(other) / (this->Magnitude() * other.Magnitude()));
  }

  Vector3 ProjectionOn(const Vector3& other) const
  {
    return other.Normalized() * (this->Dot(other) / other.Magnitude());
  }

  Vector3 PerpendicularOn(const Vector3& other) const
  {
    return (*this) - this->ProjectionOn(other);
  }

public:
  T _x;
  T _y;
  T _z;
};

#endif //QUASURA_MATH_VECTOR3_HPP
