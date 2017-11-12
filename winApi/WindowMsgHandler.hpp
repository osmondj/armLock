/*
 * WindowMsgHandler.h
 *
 *  Created on: 5 lis 2017
 *      Author: User
 */

#pragma once

#include <windows.h>
#include <memory>
#include <vector>
#include "Exception.hpp"

namespace winApi {

class WindowMsgHandler {
 public:
  explicit WindowMsgHandler(HWND hwndptr) : hwnd(hwndptr) {}
  virtual ~WindowMsgHandler();
  static void add(std::shared_ptr<WindowMsgHandler> msg);
  static void remove(HWND hwnd);
  static WindowMsgHandler& get(const HWND hwnd) throw(Exception);
  virtual LRESULT CALLBACK handle(UINT msg, WPARAM wParam,
                                  LPARAM lParam) throw(Exception) = 0;
  const HWND getHwnd() const;

 protected:
  HWND hwnd;
  static std::vector<std::shared_ptr<WindowMsgHandler>> handlers;
};

} /* namespace winApi */
