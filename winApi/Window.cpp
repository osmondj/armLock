/*
 * Window.cpp
 *
 *  Created on: 1 lis 2017
 *      Author: User
 */

#include "Window.hpp"
#include "WindowMsgHandler.hpp"

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
  try {
    return winApi::WindowMsgHandler::get(hwnd).handle(msg, wParam, lParam);
  } catch (...) {
    return DefWindowProc(hwnd, msg, wParam, lParam);
  }
}

namespace winApi {

void Window::create(std::string className) throw(Exception) {
  createWindowClassPoperties(className, WndProc);
  registerWindowClass();
  createWindowByName();
}

void Window::show(int nCmdShow) const { ShowWindow(hwnd, nCmdShow); }

void Window::update() const { UpdateWindow(hwnd); }

void Window::createWindowClassPoperties(const std::string& className,
                                        WNDPROC wndProc) {
  windowClassName = className;

  windowClassProperties.cbSize = sizeof(WNDCLASSEX);
  windowClassProperties.style = 0;
  windowClassProperties.lpfnWndProc = wndProc;
  windowClassProperties.cbClsExtra = 0;
  windowClassProperties.cbWndExtra = 0;
  windowClassProperties.hInstance = hInstance;
  windowClassProperties.hIcon = LoadIcon(NULL, IDI_APPLICATION);
  windowClassProperties.hCursor = LoadCursor(NULL, IDC_ARROW);
  windowClassProperties.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
  windowClassProperties.lpszMenuName = NULL;
  windowClassProperties.lpszClassName = windowClassName.c_str();
  windowClassProperties.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
}

void Window::registerWindowClass() const throw(Exception) {
  if (!RegisterClassEx(&windowClassProperties)) {
    MessageBox(NULL, "Error", "Can't register class",
               MB_ICONEXCLAMATION | MB_OK);
    throw Exception();
  }
}

void Window::destroy() { Window::destroy(hwnd); }

void Window::destroy(HWND hwnd) {
  if (hwnd) {
    DestroyWindow(hwnd);
    hwnd = nullptr;
  }
}

const HWND Window::getHwnd() const { return hwnd; }

void Window::createWindowByName() throw(Exception) {
  if (!hwnd) {
    hwnd = CreateWindowEx(WS_EX_CLIENTEDGE, windowClassName.c_str(),
                          "Lock is armed", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,
                          CW_USEDEFAULT, 240, 120, NULL, NULL, hInstance, NULL);
  }

  if (!hwnd) {
    MessageBox(NULL, "Error", "Can't create window",
               MB_ICONEXCLAMATION | MB_OK);
    throw Exception();
  }
}

} /* namespace winApi */
