/*
 * WindowMsgHandler.cpp
 *
 *  Created on: 9 lis 2017
 *      Author: User
 */

#include "WindowMsgHandler.hpp"
#include "../winApi/Window.hpp"

namespace armLock {
LRESULT WindowMsgHandler::handle(UINT msg, WPARAM wParam, LPARAM lParam) const
    throw(winApi::Exception) {
  switch (msg) {
    case WM_CLOSE:
      lockWorkStationAndDestroyWindow();
      break;

    case WM_DESTROY:
      PostQuitMessage(0);
      break;

    case WM_MOUSEMOVE:
      // lockWorkStationAndDestroyWindow();
      break;

    case WM_KILLFOCUS:
      lockWorkStationAndDestroyWindow();
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

} /* namespace armLock */
