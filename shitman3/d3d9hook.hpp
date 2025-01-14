#ifndef D3D9HOOK_HEADER
#define D3D9HOOK_HEADER

#include <d3d9.h>
#include <d3dx9.h>

[[nodiscard]]
bool GetD3D9Device(void** vtable, std::size_t size);

#endif // D3D9HOOK_HEADER
