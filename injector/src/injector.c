#include "injector.h"

DWORD GetProcessIdByProcessName(const char* process_name_)
{
    PROCESSENTRY32 process_entry = {sizeof(PROCESSENTRY32)};
    HANDLE processes_snapshot    = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    if (Process32First(processes_snapshot, &process_entry))
    {
        do
        {
            if (strcmp((const char *)process_entry.szExeFile, process_name_) == 0)
            {
                CloseHandle(processes_snapshot);
                return process_entry.th32ProcessID;
            }
        } while (Process32Next(processes_snapshot, &process_entry));
    }

    CloseHandle(processes_snapshot);
    return 0;
}

int InjectDLL(DWORD _process_id, const char* _dll)
{
    // Last minute checks
    if (_process_id == 0)
        return PROCESS_NOT_RUNNING;

    // Get the full path of the dll file
    TCHAR full_dll_path[MAX_PATH];
    GetFullPathName(_dll, MAX_PATH, full_dll_path, NULL);

    // Simple check to see if the
    if (DllPathIsValid(_dll, full_dll_path) != 0)
        return DLL_DOES_NOT_EXIST;

    // Get the function LoadLibraryA
    LPVOID load_library = GetProcAddress(GetModuleHandle("kernel32.dll"), "LoadLibraryA");
    if (load_library == NULL)
        return INJECTION_FAILED;

    HANDLE process_handle = OpenProcess(PROCESS_ALL_ACCESS, INJECTION_FAILED, _process_id);
    if (process_handle == NULL)
        return INJECTION_FAILED;

    // Allocate space to write the dll function
    LPVOID dll_parameter_address = VirtualAllocEx(process_handle, 0, strlen(full_dll_path), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
    if (dll_parameter_address == NULL)
    {
        CloseHandle(process_handle);
        return INJECTION_FAILED;
    }

    // Write the dll location to the space previously allocated
    BOOL wrote_memory = WriteProcessMemory(process_handle, dll_parameter_address, full_dll_path, strlen(full_dll_path), NULL);
    if (wrote_memory == false)
    {
        CloseHandle(process_handle);
        return INJECTION_FAILED;
    }

    HANDLE dll_thread_handle = CreateRemoteThread(process_handle, 0, 0, (LPTHREAD_START_ROUTINE)load_library, dll_parameter_address, 0, 0);
    if (dll_thread_handle == NULL)
    {
        CloseHandle(process_handle);
        return INJECTION_FAILED;
    }

    CloseHandle(dll_thread_handle);
    CloseHandle(process_handle);
    
    return EXIT_SUCCESS;
}

bool DllPathIsValid(const char* _dll, TCHAR _full_path[260])
{
    FILE* fp;
    if (fopen_s(&fp, TEXT(_full_path), "r"))
    {
        fclose(fp);
    } else {
        return false;
    }

    return true;
}

void __handle_error(int inject_code)
{
    switch (inject_code)
    {
        case INCORRECT_PARAMETERS:
            fprintf(stdout, "Error code %d: Incorrect Paramters.", INCORRECT_PARAMETERS);
            break;
        case PROCESS_NOT_RUNNING:
            fprintf(stdout, "Error code %d: Process is not running", PROCESS_NOT_RUNNING);
            break;
        case DLL_DOES_NOT_EXIST:
            fprintf(stdout, "Error code %d: DLL does not exist.", DLL_DOES_NOT_EXIST);
            break;
        case INJECTION_FAILED:
            fprintf(stdout, "Error code %d: Injection Failed.", DLL_DOES_NOT_EXIST);
            break;
        default:
            break;
    }
}
