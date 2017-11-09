/*
 * WindowMsgHandler.h
 *
 *  Created on: 9 lis 2017
 *      Author: User
 */

#pragma once

#include "../winApi/WindowMsgHandler.hpp"

namespace armLock {

class WindowMsgHandler : public winApi::WindowMsgHandler {
 public:
  explicit WindowMsgHandler(HWND hwndptr) : winApi::WindowMsgHandler(hwndptr) {}
  virtual LRESULT CALLBACK handle(UINT msg, WPARAM wParam, LPARAM lParam) const
      throw(winApi::Exception);

 private:
  void lockWorkStationAndDestroyWindow() const;
};

} /* namespace armLock */
