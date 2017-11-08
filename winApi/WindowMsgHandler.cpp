/*
 * WindowMsgHandler.cpp
 *
 *  Created on: 5 lis 2017
 *      Author: User
 */

#include "WindowMsgHandler.hpp"
#include "Window.hpp"
#include <algorithm>

bool operator==(std::shared_ptr<winApi::WindowMsgHandler> ptr,
                const HWND hwnd) {
  return ptr->getHwnd() == hwnd;
}

void lockWorkStationAndDestroyWindow(HWND hwnd) {
  LockWorkStation();
  winApi::Window::destroy(hwnd);
}

namespace winApi {

std::vector<std::shared_ptr<WindowMsgHandler>> WindowMsgHandler::handlers;

WindowMsgHandler::~WindowMsgHandler() {}

void WindowMsgHandler::add(std::shared_ptr<WindowMsgHandler> msg) {
  handlers.push_back(msg);
}

void WindowMsgHandler::remove(HWND hwnd) {}

WindowMsgHandler& WindowMsgHandler::get(const HWND hwnd) throw(Exception) {
  auto iterator =
      std::find(handlers.begin(), handlers.end(), hwnd);
  if (iterator != handlers.end()) {
    return *(iterator->get());
  } else {
    throw Exception();
  }
}

LRESULT CALLBACK WindowMsgHandler::handle(UINT msg, WPARAM wParam,
                                          LPARAM lParam) throw(Exception) {
  switch (msg) {
    case WM_CLOSE:
      lockWorkStationAndDestroyWindow(hwnd);
      break;

    case WM_DESTROY:
      PostQuitMessage(0);
      break;

    case WM_MOUSEMOVE:
      //lockWorkStationAndDestroyWindow(hwnd);
      break;

    case WM_KILLFOCUS:
      lockWorkStationAndDestroyWindow(hwnd);
      break;

    default:
      return DefWindowProc(hwnd, msg, wParam, lParam);
 }
  return 0;
}

const HWND WindowMsgHandler::getHwnd() const { return hwnd; }

} /* namespace winApi */
