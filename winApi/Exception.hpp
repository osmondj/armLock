/*
 * Exception.hpp
 *
 *  Created on: 8 lis 2017
 *      Author: User
 */

#pragma once

#include <exception>

namespace winApi {

class Exception : public std::exception {
  virtual const char* what() const throw() { return "WinApi exception."; }
};

}  // namespace winApi
