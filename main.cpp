/*
 * main.cpp
 *
 *  Created on: 28 paü 2017
 *      Author: User
 */

#include <windows.h>
#include <string>
#include "Window.h"

MSG Message;
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine, int nCmdShow) {
  winApi::Window window(hInstance);
  try {
    window.create("windowClassName", WndProc);
    window.show(nCmdShow);
    window.update();
  } catch (std::exception& exception) {
    return 1;
  }

  while (GetMessage(&Message, NULL, 0, 0)) {
    TranslateMessage(&Message);
    DispatchMessage(&Message);
  }
  return Message.wParam;
}

void lockWorkStationAndDestroyWindow(HWND hwnd) {
  LockWorkStation();
  winApi::Window::destroy(hwnd);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
  switch (msg) {
    case WM_CLOSE:
      lockWorkStationAndDestroyWindow(hwnd);
      break;

    case WM_DESTROY:
      PostQuitMessage(0);
      break;

    case WM_MOUSEMOVE:
      lockWorkStationAndDestroyWindow(hwnd);
      break;

    case WM_KILLFOCUS:
      lockWorkStationAndDestroyWindow(hwnd);
      break;

    default:
      return DefWindowProc(hwnd, msg, wParam, lParam);
  }

  return 0;
}
