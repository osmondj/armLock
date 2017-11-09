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

const HWND WindowMsgHandler::getHwnd() const { return hwnd; }

} /* namespace winApi */
