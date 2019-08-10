
/*
 * Matrix3x3.hpp
 *
 * Created by Viacheslav Borisenko
 *
 * Copyright (c) 2019 spectrobyte http://spectrobyte.com
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 *
 */

#ifndef QUASURA_MATH_MATRIX3X3_HPP
#define QUASURA_MATH_MATRIX3X3_HPP

#include <cmath>
#include "Vector3.hpp"

template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
class Matrix3x3
{
public:
  Matrix3x3()
  {
    for(size_t i = 0; i < 3; ++i) {
      for(size_t j = 0; j < 3; ++j) {
        this->_values[i][j] = 0;
      }
    }
  }

  explicit Matrix3x3(T array[3][3]) : Matrix3x3()
  {
    for(size_t i = 0; i < 3; ++i) {
      for(size_t j = 0; j < 3; ++j) {
        this->_values[i][j] = array[i][j];
      }
    }
  }

  Matrix3x3(
          T m00, T m01, T m02,
          T m10, T m11, T m12,
          T m20, T m21, T m22) : Matrix3x3()
  {
    this->_values[0][0] = m00;
    this->_values[0][1] = m01;
    this->_values[0][2] = m02;

    this->_values[1][0] = m10;
    this->_values[1][1] = m11;
    this->_values[1][2] = m12;

    this->_values[2][0] = m20;
    this->_values[2][1] = m21;
    this->_values[2][2] = m22;
  }

  Matrix3x3 operator*(const Matrix3x3& other) const
  {
    Matrix3x3 temp;

    for(size_t i = 0; i < 3; ++i) {
      for(size_t j = 0; j < 3; ++j) {
        temp._values[i][j] = 0;
        for(size_t k = 0; k < 3; ++k) {
          temp.values[i][j] += this->_values[i][k] * other._values[k][j];
        }
      }
    }

    return temp;
  }

  float Determinant() const
  {
    return
            this->_values[0][0] *
            (this->_values[1][1] * this->_values[2][2] - this->_values[1][2] * this->_values[2][1]) -
            this->_values[0][1] *
            (this->_values[1][0] * this->_values[2][2] - this->_values[1][2] * this->_values[2][0]) +
            this->_values[0][2] *
            (this->_values[1][0] * this->_values[2][1] - this->_values[1][1] * this->_values[2][0]);
  }

  Matrix3x3 Inversed() const
  {
    return Inversed(Determinant());
  }

  Matrix3x3 Inversed(float determinant) const
  {
    Matrix3x3 temp;

    temp._values[0][0] = this->_values[1][1] * this->_values[2][2] - this->_values[1][2] * this->_values[2][1];
    temp._values[1][0] = this->_values[1][2] * this->_values[2][0] - this->_values[1][0] * this->_values[2][2];
    temp._values[2][0] = this->_values[1][0] * this->_values[2][1] - this->_values[1][1] * this->_values[2][0];

    temp._values[0][1] = this->_values[0][2] * this->_values[2][1] - this->_values[0][1] * this->_values[2][2];
    temp._values[1][1] = this->_values[0][0] * this->_values[2][2] - this->_values[0][2] * this->_values[2][0];
    temp._values[2][1] = this->_values[0][1] * this->_values[2][0] - this->_values[0][0] * this->_values[2][1];

    temp._values[0][2] = this->_values[0][1] * this->_values[1][2] - this->_values[0][2] * this->_values[1][1];
    temp._values[1][2] = this->_values[0][2] * this->_values[1][0] - this->_values[0][0] * this->_values[1][2];
    temp._values[2][2] = this->_values[0][0] * this->_values[1][1] - this->_values[0][1] * this->_values[1][0];

    float det_inversed = 1.0f / determinant;
    for(size_t j = 0; j < 3; ++j) {
      for(size_t i = 0; i < 3; ++i) {
        temp._values[i][j] *= det_inversed;
      }
    }

    return temp;
  }

  static Matrix3x3 Scale(float x, float y, float z)
  {
    return Matrix3x3(
            x, 0.0f, 0.0f,
            0.0f, y, 0.0f,
            0.0f, 0.0f, z);
  }

  static Matrix3x3 Scale(float s)
  {
    return Matrix3x3(
            s, 0.0f, 0.0f,
            0.0f, s, 0.0f,
            0.0f, 0.0f, s);
  }

  static Matrix3x3 RotationX(float radians)
  {
    return Matrix3x3(
            1.0f, 0.0f, 0.0f,
            0.0f, std::cos(radians), std::sin(radians),
            0.0f, -std::sin(radians), std::cos(radians));
  }

  static Matrix3x3 RotationY(float radians)
  {
    return Matrix3x3(
            std::cos(radians), 0.0f, -std::sin(radians),
            0.0f, 1.0f, 0.0f,
            std::sin(radians), 0.0f, std::cos(radians));
  }

  static Matrix3x3 RotationZ(float radians)
  {
    return Matrix3x3(
            std::cos(radians), std::sin(radians), 0.0f,
            -std::sin(radians), std::cos(radians), 0.0f,
            0.0f, 0.0f, 1.0f);
  }

  static Matrix3x3 Rotation(const Vector3<float>& axis, float radians)
  {
    auto normalized(axis.Normalized());

    float cos_value = std::cos(radians);
    float sin_value = std::sin(radians);

    return Matrix3x3(
            normalized._x * normalized._x * (1.0f - cos_value) + cos_value,
            normalized._x * normalized._y * (1.0f - cos_value) + normalized._z * sin_value,
            normalized._x * normalized._z * (1.0f - cos_value) - normalized._y * sin_value,

            normalized._x * normalized._y * (1.0f - cos_value) - normalized._z * sin_value,
            normalized._y * normalized._y * (1.0f - cos_value) + cos_value,
            normalized._y * normalized._z * (1.0f - cos_value) + normalized._x * sin_value,

            normalized._x * normalized._z * (1.0f - cos_value) + normalized._y * sin_value,
            normalized._y * normalized._z * (1.0f - cos_value) - normalized._x * sin_value,
            normalized._z * normalized._z * (1.0f - cos_value) + cos_value);
  }

  /** Data array, [row][column] */
  T _values[3][3];
};

template<typename T>
Vector3<T> operator*(const Vector3<T>& v, const Matrix3x3<T>& m)
{
  return Vector3<T>(
          v._x * m._values[0][0] + v._y * m._values[1][0] + v._z * m._values[2][0],
          v._x * m._values[0][1] + v._y * m._values[1][1] + v._z * m._values[2][1],
          v._x * m._values[0][2] + v._y * m._values[1][2] + v._z * m._values[2][2]);
}

#endif //QUASURA_MATH_MATRIX3X3_HPP
