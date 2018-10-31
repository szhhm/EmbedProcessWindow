#ifndef PROCESSWINDOW_H
#define PROCESSWINDOW_H
#include "Windows.h"
#include "TlHelp32.h"
#include "winuser.h"
#include <string>

BOOL CALLBACK FindProcessWnd(HWND hWnd, LPARAM lparam);
HWND FindMyWindows(const std::string processName, int& pid);

#endif // PROCESSWINDOW_H
