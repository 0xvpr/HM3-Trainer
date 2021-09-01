#pragma once

#include <windows.h>
#include <tlhelp32.h>
#include <vector>

uintptr_t FindDMAddress(uintptr_t ptr, std::vector<unsigned int> offsets);

void Patch(char* dst, char* src, size_t size);