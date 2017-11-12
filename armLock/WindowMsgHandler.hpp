/*
 * WindowMsgHandler.h
 *
 *  Created on: 9 lis 2017
 *      Author: User
 */

#pragma once

#include "../winApi/WindowMsgHandler.hpp"
#include <string>

namespace armLock {

class WindowMsgHandler : public winApi::WindowMsgHandler {
 public:
  explicit WindowMsgHandler(HWND hwndptr)
      : winApi::WindowMsgHandler(hwndptr), isLockArmed(true) {}
  virtual LRESULT CALLBACK handle(UINT msg, WPARAM wParam,
                                  LPARAM lParam) throw(winApi::Exception);

 private:
  void lockWorkStationAndDestroyWindow() const;
  void handleKeyDown(WPARAM wParam);

  static const std::string unlockPassword;

  bool isLockArmed;
  std::string typedString;
};

} /* namespace armLock */
