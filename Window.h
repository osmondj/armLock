/*
 * Window.h
 *
 *  Created on: 1 lis 2017
 *      Author: User
 */

#pragma once

#include <windows.h>
#include <exception>
#include <string>

namespace winApi {
class Exception : public std::exception {
  virtual const char* what() const throw() { return "WinApi exception."; }
};

class Window {
 public:
  Window(const HINSTANCE& hInstanceRef)
      : hInstance(hInstanceRef), hwnd(nullptr) {}

  void create(std::string className, WNDPROC wndProc) throw(Exception);
  void show(int nCmdShow) const;
  void update() const;
  void destroy();
  static void destroy(HWND hwnd);

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
