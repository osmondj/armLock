/*
 * WindowMsgHandler.cpp
 *
 *  Created on: 9 lis 2017
 *      Author: User
 */

#include "WindowMsgHandler.hpp"
#include "../winApi/Window.hpp"
#ifdef DEBUG
#include <iostream>
#endif

namespace armLock {

const std::string WindowMsgHandler::unlockPassword = "HASLO";

LRESULT WindowMsgHandler::handle(UINT msg, WPARAM wParam,
                                 LPARAM lParam) throw(winApi::Exception) {
  switch (msg) {
    case WM_CLOSE:
      lockWorkStationAndDestroyWindow();
      break;

    case WM_DESTROY:
      PostQuitMessage(0);
      break;

    case WM_KEYDOWN:
      handleKeyDown(wParam);
      break;

    case WM_MOUSEMOVE:
      typedString.clear();
      break;

    case WM_KILLFOCUS:
      if (isLockArmed) {
        lockWorkStationAndDestroyWindow();
      }
      break;

    default:
      return DefWindowProc(hwnd, msg, wParam, lParam);
  }
  return 0;
}

void WindowMsgHandler::lockWorkStationAndDestroyWindow() const {
  LockWorkStation();
  winApi::Window::destroy(hwnd);
}

void WindowMsgHandler::handleKeyDown(WPARAM wParam) {
#ifdef DEBUG
  std::cout << "Key=" << static_cast<char>(wParam) << std::endl;
#endif
  typedString += static_cast<char>(wParam);
#ifdef DEBUG
  std::cout << "TypedString=" << typedString << std::endl;
#endif
  if (typedString == unlockPassword) {
    isLockArmed = false;
    winApi::Window::destroy(hwnd);
  }
}

} /* namespace armLock */
