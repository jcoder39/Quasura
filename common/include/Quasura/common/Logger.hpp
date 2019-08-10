/*
 * Logger.hpp
 *
 * Created by Viacheslav Borisenko
 *
 * Copyright (c) 2018 spectrobyte http://spectrobyte.com
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 *
 */

#ifndef QUASURA_LOGGER_HPP
#define QUASURA_LOGGER_HPP

#include <iostream>
#include "Global.hpp"

COMMON_NAMESPACE_BEGIN

#define LOG(MESSAGE) std::cout << "[LOG]: " << __FILE__ << ":" << __LINE__ << "; " << MESSAGE << std::endl

#ifdef SB_LOGGING
#define SYSLOG(MESSAGE) std::cout << "[SYSLOG]: " << __FILE__ << ":" << __LINE__ << "; " << MESSAGE << std::endl
#else
#define SYSLOG(MESSAGE)
#endif

COMMON_NAMESPACE_END

#endif //QUASURA_LOGGER_HPP
