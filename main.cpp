/*
 * main.cpp
 *
 *  Created on: 28 paü 2017
 *      Author: User
 */

#include <windows.h>
#include <string>
#include "winApi/Window.hpp"
#include "armLock/WindowMsgHandler.hpp"

MSG Message;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine, int nCmdShow) {
#ifndef DEBUG
  FreeConsole();
#endif
  winApi::Window window(hInstance);
  try {
    window.create("windowClassName");
    window.show(nCmdShow);
    window.update();
    winApi::WindowMsgHandler::add(std::shared_ptr<winApi::WindowMsgHandler>(
        new armLock::WindowMsgHandler(window.getHwnd())));
  } catch (std::exception& exception) {
    return 1;
  }

  while (GetMessage(&Message, NULL, 0, 0)) {
    TranslateMessage(&Message);
    DispatchMessage(&Message);
  }
  return Message.wParam;
}
