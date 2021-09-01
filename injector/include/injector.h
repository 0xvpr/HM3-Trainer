#ifndef _INJECTOR_H
#define _INJECTOR_H

#ifndef WIN32_LEAN_AND_MEAN
    #define WIN32_LEAN_AND_MEAN
#endif

#define INCORRECT_PARAMETERS  0xFFFFFFFF
#define PROCESS_NOT_RUNNING   0x00000001
#define DLL_DOES_NOT_EXIST    0x00000002
#define INJECTION_FAILED      0x00000004

#include <windows.h>
#include <tlhelp32.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

DWORD GetProcessIdByProcessName(const char* _process_name);

bool DllPathIsValid(const char* _dll, TCHAR full_path[260]);

int InjectDLL(DWORD _process_id, const char* _dll);

void __handle_error(int error_code);

#endif /* _INJECTOR_H */
