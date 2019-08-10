/*
 * Helper.hpp
 *
 * Created by Viacheslav Borisenko
 *
 * Copyright (c) 2018 spectrobyte http://spectrobyte.com
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 *
 */

#ifndef QUASURA_AI_ASTAR_HELPER_HPP
#define QUASURA_AI_ASTAR_HELPER_HPP

#include <sstream>
#include <iomanip>
#include "Quasura/AI/Global.hpp"
#include "Quasura/math/Vector2.hpp"

AI_NAMESPACE_BEGIN

namespace astar {

namespace ext {
template<typename T>
std::string to_string(const T& n, const int width)
{
  std::ostringstream ss;
  ss << std::setw(width) << std::setfill('0') << n;
  return ss.str();
}
}

class Helper
{
public:
  static int calculateWidth(int i)
  {
    int len = 1;
    if(i > 0) {
      for(len = 0; i > 0; len++) {
        i = i / 10;
      }
    }
    return len;
  }

  static std::string getCode(int x, int y, int widthX, int widthY)
  {
    std::string temp;
    temp += ext::to_string(x, widthX);
    temp += ext::to_string(y, widthY);
    return temp;
  };

  static std::string getCode(math::Vector2<int>& point, int widthX, int widthY)
  {
    std::string temp;
    temp += ext::to_string(point._x, widthX);
    temp += ext::to_string(point._y, widthY);
    return temp;
  };

  static std::string getCodeForW(math::Vector2<int>& point, int widthX, int widthY)
  {
    return getCode(point._x - 1, point._y, widthX, widthY);
  }

  static std::string getCodeForWN(math::Vector2<int>& point, int widthX, int widthY)
  {
    return getCode(point._x - 1, point._y - 1, widthX, widthY);
  }

  static std::string getCodeForN(math::Vector2<int>& point, int widthX, int widthY)
  {
    return getCode(point._x, point._y - 1, widthX, widthY);
  }

  static std::string getCodeForNE(math::Vector2<int>& point, int widthX, int widthY)
  {
    return getCode(point._x + 1, point._y - 1, widthX, widthY);
  }

  static std::string getCodeForE(math::Vector2<int>& point, int widthX, int widthY)
  {
    return getCode(point._x + 1, point._y, widthX, widthY);
  }

  static std::string getCodeForES(math::Vector2<int>& point, int widthX, int widthY)
  {
    return getCode(point._x + 1, point._y + 1, widthX, widthY);
  }

  static std::string getCodeForS(math::Vector2<int>& point, int widthX, int widthY)
  {
    return getCode(point._x, point._y + 1, widthX, widthY);
  }

  static std::string getCodeForSW(math::Vector2<int>& point, int widthX, int widthY)
  {
    return getCode(point._x - 1, point._y + 1, widthX, widthY);
  }
};

}

AI_NAMESPACE_END

#endif //Quasura_AI_ASTAR_HELPER_HPP
