/*
 * Window.h
 *
 *  Created on: 1 lis 2017
 *      Author: User
 */

#pragma once

#include <windows.h>
#include <string>
#include "Exception.hpp"

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace winApi {

class Window {
 public:
  Window(const HINSTANCE& hInstanceRef)
      : hInstance(hInstanceRef), hwnd(nullptr) {}

  void create(std::string className) throw(Exception);
  void show(int nCmdShow) const;
  void update() const;
  void destroy();
  static void destroy(HWND hwnd);
  const HWND getHwnd() const;

 private:
  void createWindowClassPoperties(const std::string& className,
                                  WNDPROC wndProc);
  void registerWindowClass() const throw(Exception);
  void createWindowByName() throw(Exception);

  const HINSTANCE& hInstance;
  std::string windowClassName;
  WNDCLASSEX windowClassProperties;
  HWND hwnd;
};

} /* namespace winApi */
