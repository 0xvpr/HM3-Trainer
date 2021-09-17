#include "mem.hpp"

// TODO: Add hook & detour functions

uintptr_t FindDMAddress(uintptr_t ptr, std::vector<unsigned> offsets)
{
  uintptr_t addr = ptr;
  for (uintptr_t i = 0; i < offsets.size(); i++)
  {
    addr = *(uintptr_t *)addr;
    if (addr == 0)
      return (uintptr_t)NULL;
    addr += offsets[i];
  }

  return addr;
}

void Patch(char* dst, char* src, size_t size)
{
  DWORD old_protect;

  VirtualProtect(dst, size, PAGE_EXECUTE_WRITECOPY, &old_protect);
  memcpy(dst, src, size);
  VirtualProtect(dst, size, old_protect, NULL);
}
