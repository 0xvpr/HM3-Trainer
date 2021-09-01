#pragma once

#include <windows.h>

#include <d3d9.h>
#include <d3dx9.h>

#include "events.hpp"
#include "render.hpp"
#include "kiero/kiero.h"
#include "kiero/minhook/include/MinHook.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx9.h"

#define WINDOW_NAME "Hitman Trainer (STATUS)"


typedef long(__stdcall* EndScene)(LPDIRECT3DDEVICE9);
typedef LRESULT(CALLBACK* WNDPROC)(HWND, UINT, WPARAM, LPARAM);
