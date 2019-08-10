
/*
 * Matrix4x4.hpp
 *
 * Created by Viacheslav Borisenko
 *
 * Copyright (c) 2019 spectrobyte http://spectrobyte.com
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 *
 */

#ifndef QUASURA_MATH_MATRIX4X4_HPP
#define QUASURA_MATH_MATRIX4X4_HPP

#include <cmath>
#include "Vector3.hpp"

template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
class Matrix4x4
{
public:
  Matrix4x4()
  {
    for(int i = 0; i < 4; ++i) {
      for(int j = 0; j < 4; ++j) {
        this->_values[i][j] = 0;
      }
    }
  }

  explicit Matrix4x4(T array[4][4])
  {
    for(int i = 0; i < 4; ++i) {
      for(int j = 0; j < 4; ++j) {
        this->_values[i][j] = array[i][j];
      }
    }
  }

  Matrix4x4(
          T m00, T m01, T m02, T m03,
          T m10, T m11, T m12, T m13,
          T m20, T m21, T m22, T m23,
          T m30, T m31, T m32, T m33)
  {
    this->_values[0][0] = m00;
    this->_values[0][1] = m01;
    this->_values[0][2] = m02;
    this->_values[0][3] = m03;

    this->_values[1][0] = m10;
    this->_values[1][1] = m11;
    this->_values[1][2] = m12;
    this->_values[1][3] = m13;

    this->_values[2][0] = m20;
    this->_values[2][1] = m21;
    this->_values[2][2] = m22;
    this->_values[2][3] = m23;

    this->_values[3][0] = m30;
    this->_values[3][1] = m31;
    this->_values[3][2] = m32;
    this->_values[3][3] = m33;
  }

  Matrix4x4 operator*(const Matrix4x4& other) const
  {
    Matrix4x4 temp;

    for(size_t i {0}; i < 4; ++i) {
      for(size_t j {0}; j < 4; ++j) {
        temp._values[i][j] = 0;
        for(size_t k {0}; k < 4; ++k) {
          temp._values[i][j] += this->_values[i][k] * other._values[k][j];
        }
      }
    }

    return temp;
  }

  static Matrix4x4 Translation(float x, float y, float z)
  {
    return Matrix4x4(
            1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            x, y, z, 1.0f);
  }

  static Matrix4x4 Scale(float x, float y, float z)
  {
    return Matrix4x4(
            x, 0.0f, 0.0f, 0.0f,
            0.0f, y, 0.0f, 0.0f,
            0.0f, 0.0f, z, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f);
  }

  static Matrix4x4 Scale(float s)
  {
    return Matrix4x4(
            s, 0.0f, 0.0f, 0.0f,
            0.0f, s, 0.0f, 0.0f,
            0.0f, 0.0f, s, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f);
  }

  static Matrix4x4 RotationX(float radians)
  {
    return Matrix4x4(
            1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, std::cos(radians), std::sin(radians), 0.0f,
            0.0f, -std::sin(radians), std::cos(radians), 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f);
  }

  static Matrix4x4 RotationY(float radians)
  {
    return Matrix4x4(
            std::cos(radians), 0.0f, -std::sin(radians), 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            std::sin(radians), 0.0f, std::cos(radians), 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f);
  }

  static Matrix4x4 RotationZ(float radians)
  {
    return Matrix4x4(
            std::cos(radians), std::sin(radians), 0.0f, 0.0f,
            -std::sin(radians), std::cos(radians), 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f);
  }

  static Matrix4x4 Rotation(const Vector3<float>& axis, float radians)
  {
    auto normalized(axis.Normalized());

    float cos_value = std::cos(radians);
    float sin_value = std::sin(radians);

    return Matrix4x4(
            normalized._x * normalized._x * (1.0f - cos_value) + cos_value,
            normalized._x * normalized._y * (1.0f - cos_value) + normalized._z * sin_value,
            normalized._x * normalized._z * (1.0f - cos_value) - normalized._y * sin_value,
            0.0f,

            normalized._x * normalized._y * (1.0f - cos_value) - normalized._z * sin_value,
            normalized._y * normalized._y * (1.0f - cos_value) + cos_value,
            normalized._y * normalized._z * (1.0f - cos_value) + normalized._x * sin_value,
            0.0f,

            normalized._x * normalized._z * (1.0f - cos_value) + normalized._y * sin_value,
            normalized._y * normalized._z * (1.0f - cos_value) - normalized._x * sin_value,
            normalized._z * normalized._z * (1.0f - cos_value) + cos_value,
            0.0f,

            0.0f,
            0.0f,
            0.0f,
            1.0f);
  }

  static Matrix4x4 ClipSpace(float hfov, float vfov, float near, float far)
  {
    float projection_plane_z = 1.0f;

    float right = std::tan(hfov / 2.0f) * projection_plane_z;
    float left = -right;
    float top = std::tan(vfov / 2.0f) * projection_plane_z;
    float bottom = -top;

    return Matrix4x4(
            2.0f * projection_plane_z / (right - left), 0.0f, 0.0f, 0.0f,
            0.0f, 2.0f * projection_plane_z / (top - bottom), 0.0f, 0.0f,
            (left + right) / (left - right), (bottom + top) / (bottom - top), (far + near) / (far - near), 1.0f,
            0.0f, 0.0f, -2.0f * near * far / (far - near), 0.0f);
  }

  static const inline Matrix4x4 IDENTITY = Matrix4x4(
          1.0f, 0.0f, 0.0f, 0.0f,
          0.0f, 1.0f, 1.0f, 0.0f,
          0.0f, 0.0f, 1.0f, 0.0f,
          0.0f, 0.0f, 0.0f, 1.0f);

  /** Data array, [row][column] */
  float _values[4][4];
};

#endif //QUASURA_MATH_MATRIX4X4_HPP
