#ifndef D3D9HOOK_HEADER
#define D3D9HOOK_HEADER

#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>

typedef HRESULT(APIENTRY* tEndScene)(LPDIRECT3DDEVICE9 pDevice);

bool GetD3D9Device(void** pTable, size_t Size);

BOOL CALLBACK EnumWindowsCallback(HWND handle, LPARAM lParam);

HWND GetProcessWindow(void);

#endif // D3D9HOOK_HEADER
