#ifndef D3D9HOOK_HEADER
#define D3D9HOOK_HEADER

#include <d3d9.h>
#include <d3dx9.h>

namespace d3d9 {

constexpr size_t render_function_index = 42;

typedef HRESULT(APIENTRY* endscene_t)(LPDIRECT3DDEVICE9 device_ptr);

[[nodiscard]] bool get_device(void** vtable, std::size_t size);

} // namespace d3d9

#endif // D3D9HOOK_HEADER
