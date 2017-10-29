/*
 * main.cpp
 *
 *  Created on: 28 paü 2017
 *      Author: User
 */

#include <windows.h>
#include <string>

MSG Message;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

WNDCLASSEX CreateWindowInformation(const HINSTANCE& hInstance,
                                   const std::string& name) {
  WNDCLASSEX wc;

  wc.cbSize = sizeof(WNDCLASSEX);
  wc.style = 0;
  wc.lpfnWndProc = WndProc;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = 0;
  wc.hInstance = hInstance;
  wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
  wc.hCursor = LoadCursor(NULL, IDC_ARROW);
  wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
  wc.lpszMenuName = NULL;
  wc.lpszClassName = name.c_str();
  wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

  return wc;
}

bool RegisterWindowClass(const WNDCLASSEX& classInfo) {
  if (RegisterClassEx(&classInfo)) {
    return true;
  } else {
    MessageBox(NULL, "Error", "Can't register class",
               MB_ICONEXCLAMATION | MB_OK);
    return false;
  }
}

HWND CreateWindowByWindowClassName(const HINSTANCE& hInstance,
                                   const std::string& windowClassName) {
  return CreateWindowEx(WS_EX_CLIENTEDGE, windowClassName.c_str(),
                        "Lock is armed", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,
                        CW_USEDEFAULT, 240, 120, NULL, NULL, hInstance, NULL);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine, int nCmdShow) {
  std::string windowClassName = "windowClassName";
  WNDCLASSEX wcInfo = CreateWindowInformation(hInstance, windowClassName);

  if (!RegisterWindowClass(wcInfo)) {
    return 1;
  }

  HWND hwnd = CreateWindowByWindowClassName(hInstance, windowClassName);

  if (hwnd == NULL) {
    MessageBox(NULL, "Error", "Can't create window.", MB_ICONEXCLAMATION);
    return 1;
  }

  ShowWindow(hwnd, nCmdShow);
  UpdateWindow(hwnd);

  while (GetMessage(&Message, NULL, 0, 0)) {
    TranslateMessage(&Message);
    DispatchMessage(&Message);
  }
  return Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
  switch (msg) {
    case WM_CLOSE:
      LockWorkStation();
      DestroyWindow(hwnd);
      break;

    case WM_DESTROY:
      PostQuitMessage(0);
      break;

    default:
      return DefWindowProc(hwnd, msg, wParam, lParam);
  }

  return 0;
}
